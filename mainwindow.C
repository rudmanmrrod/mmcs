/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file mainwindow.c
    @brief Cuerpo Principal de funciones del Sistema de Matrices de Contabilidad Social
    @author José Ruiz at 05/15, Rodrigo Boet
    @author <a href='http://www.cenditel.gob.ve'>Centro Nacional de Desarrollo e Investigación en Tecnologías Libres (CENDITEL) nodo Mérida - Venezuela</a>
    @copyright <a href='http://conocimientolibre.cenditel.gob.ve/licencia-de-software-v-1-3/>Licencia de Software Versión 1.2</a>
*/

#include "mainwindow.H"
#include <QDebug>


using namespace Eigen;

//  FA_001
/*                      A partir de aquí comienzan las operaciones del menu Archivo                   */
/**
    @brief Función que permite desplegar el formulario de carga de matriz
    @date 05/05/2015
    @author José Ruiz
*/
void MainWindow::slotLoadMatrix()
{
    formLoadMatrix = new  FormLoadMatrix(this);
    formLoadMatrix->show();
    connect(formLoadMatrix, SIGNAL(formAccepted(QString,int,int)),
            this, SLOT(slotFormLoadMatrixAccepted(QString,int,int)));
    connect(formLoadMatrix->ui->radioAccount,SIGNAL(clicked()),this,SLOT(slotOnlyaccount()));
    connect(formLoadMatrix->ui->radioComponent,SIGNAL(clicked()),this,SLOT(slotOnlycomponent()));
}

/**
    @brief Función que carga la matriz en el widget principal si pasó las validaciones del formulario
    @date 05/05/2015
    @author José Ruiz
    @param <filePath> Recibe la ruta del directorio
    @param <accountNumber> Recibe el número de cuentas
    @param <pre> Recibe el valor de la cantidad de décimales
*/
void MainWindow::slotFormLoadMatrixAccepted(const QString & filePath,
                                            int accountNumber, int pre)
{
    csvFilePath = filePath;
    csvSeparator = ';';
    numAccounts = accountNumber;
    precission = pre;
    formLoadMatrix->close();
    FormCargando *cargando = new FormCargando(this);
    cargando->show();


    createMatrixCentralWidget();
    QTimer::singleShot(1000,cargando,SLOT(hide()));
}

/**
    @brief Función que permite cerrar el formulario de carga de matriz
    @date 03/04/2015
    @author José Ruiz
*/
void MainWindow::slotFormLoadMatrixClosed()
{
    disconnect(formLoadMatrix, SIGNAL(formAccepted(QString,int)),
               this, SLOT(slotFormLoadMatrixAccepted(QString,int)));
    formLoadMatrix = 0;
}

/**
    @brief Función que permite agregar un mensaje en el label cuando se selecciona la opción de cuentas
    @date 29/07/2016
    @author Rodrigo Boet
*/
void MainWindow::slotOnlyaccount()
{
    formLoadMatrix->ui->label_info->setText("Info: Para esta opción debe agregar debe cargar un csv con cuentas y componentes");

}

/**
    @brief Función que permite agregar un mensaje en el label cuando se selecciona la opción de componentes
    @date 29/07/2016
    @author Rodrigo Boet
*/
void MainWindow::slotOnlycomponent()
{
    formLoadMatrix->ui->label_info->setText("Info: Para esta opción debe agregar debe cargar un csv con sólo los componentes");
}


/**
    @brief Función que permite crear un nuevo proyecto
    @date 10/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotNuevoProyecto()
{
    QMessageBox msBox(QMessageBox::Question,"Nuevo Proyecto","¿Desea crear un nuevo proyecto?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        MainWindow *mw = new MainWindow;
        mw->show();
    }
}

/**
    @brief Función que permite crear el formulario para exportar una matriz a csv
    @date 10/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotExportMatrix()
{

    if(opcionExportarMatriz == 0)
    {
        formExportMatriz = new FormExportMatrix(this);
        QHBoxLayout * layoutLateralWidget = new QHBoxLayout;
        QVBoxLayout * layoutCentralWidget = new QVBoxLayout;

        QLabel *label = new QLabel;
        label->setText("Exportará la siguiente matriz: ");
        label->setStyleSheet("font-size:14;font-weight:bold;");
        layoutLateralWidget->addWidget(label);

        int indice = tabWidget->currentIndex();
        QString text = tabWidget->tabText(indice);
        formExportMatriz->MatrixName = new QLineEdit;
        formExportMatriz->MatrixName->setFixedWidth(150);
        formExportMatriz->MatrixName->setText(text);
        formExportMatriz->MatrixName->setReadOnly(true);
        QVBoxLayout *cbLayout = new QVBoxLayout;
        cbLayout->addWidget(formExportMatriz->MatrixName);
        QWidget *cbWidget = new QWidget;
        cbWidget->setLayout(cbLayout);

        layoutLateralWidget->addWidget(cbWidget);

        QLabel *label2 = new QLabel;
        label2->setText("Archivo");
        formExportMatriz->ExportLine = new QLineEdit;
        formExportMatriz->ExportLine->setReadOnly(true);
        formExportMatriz->ExportLine->setFixedWidth(450);

        QPushButton * buttonExplorar = new QPushButton;
        buttonExplorar->setObjectName("Exportar-Explorar");
        buttonExplorar->setFlat(true);
        buttonExplorar->setIcon(QIcon(":/imgs/folder_blue.png"));

        QHBoxLayout *layoutMiddle = new QHBoxLayout;
        layoutMiddle->addWidget(label2);
        layoutMiddle->addWidget(formExportMatriz->ExportLine);
        layoutMiddle->addWidget(buttonExplorar);
        QWidget *middle = new QWidget;
        middle->setLayout(layoutMiddle);


        /***        Se crean y personalizan los bottones para exportar y cancelar    ***/
        QPushButton * buttonExportar = new QPushButton;
        buttonExportar->setObjectName("ExportarMatriz");//Se le asigna nombre al objeto
        buttonExportar->setText("Exportar");
        buttonExportar->setFixedWidth(130);

        QPushButton * buttonCancelar = new QPushButton;
        buttonCancelar->setObjectName("CancelarMatriz");//Se le asigna nombre al objeto
        buttonCancelar->setText("Cancelar");
        buttonCancelar->setFixedWidth(130);

        connect(buttonCancelar,SIGNAL(clicked()),this,SLOT(slotCloseExport()));
        connect(buttonExportar,SIGNAL(clicked()),this,SLOT(slotSaveExport()));
        connect(buttonExplorar,SIGNAL(clicked()),this,SLOT(slotSearchExport()));

        QHBoxLayout * layoutsButtons = new QHBoxLayout;
        layoutsButtons->addWidget(buttonExportar);
        layoutsButtons->addWidget(buttonCancelar);
        QWidget *buttonWidget = new QWidget;
        buttonWidget->setLayout(layoutsButtons);

        QWidget *widget = new QWidget;
        widget->setLayout(layoutLateralWidget);
        layoutCentralWidget->addWidget(widget);
        layoutCentralWidget->addWidget(middle);
        layoutCentralWidget->addWidget(buttonWidget);
        formExportMatriz->setLayout(layoutCentralWidget);
        formExportMatriz->show();
        opcionExportarMatriz = 1;

    }
    else
    {
        int indice = tabWidget->currentIndex();
        QString text = tabWidget->tabText(indice);
        formExportMatriz->MatrixName->setText(text);
        formExportMatriz->show();
    }

}

/**
    @brief Función que permite cerrar el formulario para exportar la matriz
    @date 10/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCloseExport()
{
    formExportMatriz->ExportLine->setText("");
    formExportMatriz->close();
}

/**
    @brief Función que permite exportar una matriz a csv
    @date 10/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotSaveExport()
{

    if(formExportMatriz->ExportLine->text().isEmpty())
    {
        QMessageBox::critical(this,"Nombre del Archivo","Debe Colocar un nombre");
    }
    else
    {
        QString filename = formExportMatriz->ExportLine->text();
        QFile archivo(filename);
        int actual = tabWidget->currentIndex();
        if(actual!=0)
        {
            QTableWidget *tw = tabWidget->widget(actual)->findChild<QTableWidget *>();
            int fila = tw->rowCount();
            int col = tw->columnCount();
            archivo.open(QFile::WriteOnly | QFile::Text);
            QTextStream out(&archivo);
            for(int i=0;i<fila;i++)
            {
                for(int j=0;j<col;j++)
                {
                    QString item = tw->item(i,j)->text();
                    item.remove(".");
                    item.replace(",",".");
                    item.remove("\n");
                    if(item.isEmpty())
                    {
                        item = "-";
                    }
                    out << item;
                    if(j+1<col)
                    {
                        out << ";";
                    }
                }
                out<<"\n";
            }
            archivo.flush();
            archivo.close();
            QMessageBox::information(this,"Éxito",QString("Se exportó con éxito\nla matriz en\n"+formExportMatriz->ExportLine->text()));
            formExportMatriz->ExportLine->setText("");
            formExportMatriz->close();
        }
        else
        {
            QMessageBox::critical(this,"Alerta","No puede exportar la pestaña\n inicio");
        }
    }
}

/**
    @brief Función que permite seleccionar la ruta en la que se guardará la matriz en csv
    @date 10/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotSearchExport()
{
    QString format = ".csv";

    QString filename = QFileDialog::getSaveFileName(this,
            "Elija el nombre", QDir::homePath(),"*.csv");

    filename.remove(format);

    filename +=format;

    formExportMatriz->ExportLine->setText(filename);
}

/**
    @brief Función que permite cargar la matriz mostrada al inicio
    @date 10/04/2015
    @author José Ruiz
*/
void MainWindow::createCentralWidget()
{
    QVBoxLayout * layoutCentralWidget = new QVBoxLayout;

    QHBoxLayout * layoutTitle = new QHBoxLayout;
    QLabel * lblTitle = new QLabel("Estructura de la Matriz de " \
                                   "Contabilidad Social");
    lblTitle->setFont(QFont("Aero Matics", 25, 1));
    lblTitle->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
    layoutTitle->addWidget(lblTitle);
    layoutCentralWidget->addLayout(layoutTitle);

    QHBoxLayout * layoutMatrix = new QHBoxLayout;
    QLabel * lblMatrix = new QLabel;
    lblMatrix->setAlignment(Qt::AlignCenter);
    lblMatrix->setPixmap(QPixmap(":/imgs/Imagen-matriz.png"));
    layoutMatrix->addWidget(lblMatrix);
    layoutCentralWidget->addLayout(layoutMatrix);

    QHBoxLayout * layoutFoot = new QHBoxLayout;
    QLabel * lblFoot = new QLabel("Centro Nacional de Desarrollo e" \
                                  " Investigación en\nTecnologías Libres." \
                                  " Nodo Mérida.");
    lblFoot->setFont(QFont("Aero Matics", 19, 1));
    lblFoot->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    QLabel * lblLogo = new QLabel;
    lblLogo->setPixmap(QPixmap(":/imgs/logo_cenditel.jpg"));
    lblLogo->setFixedWidth(lblLogo->pixmap()->width());
    lblLogo->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    layoutFoot->addWidget(lblFoot);
    layoutFoot->addWidget(lblLogo);
    layoutCentralWidget->addLayout(layoutFoot);

    tabWidget->addTab(new QWidget,"Inicio");
    setCentralWidget(tabWidget);
    QWidget *widget=tabWidget->widget(0);
    widget->setLayout(layoutCentralWidget);

}

/**
    @brief Función que permite crear el apartado <b>Archivo</b> del menú principal de la aplicación
    @date 10/04/2015
    @author José Ruiz
*/
void MainWindow::createMenuBar()
{
    menuFile.setTitle("&Archivo");

    actionNewProject.setText("&Nuevo Proyecto");
    menuFile.addAction(&actionNewProject);

    actionLoadMatrix.setText("&Cargar Matriz");
    menuFile.addAction(&actionLoadMatrix);

    actionExportMatrix.setText("&Exportar Matriz");
    menuFile.addAction(&actionExportMatrix);
    actionExportMatrix.setDisabled(true);

    actionQuit.setText("&Salir");
    menuFile.addAction(&actionQuit);


    menuBar()->addMenu(&menuFile);
}

/**
    @brief Función que permite crear el apartado <b>Herramientas</b> del menú principal de la aplicación
    @date 10/06/2015
    @author Rodrigo Boet
*/
void MainWindow::matricesMenuBar()
{
    menuTools.setTitle("&Herramientas");
    menuTools.setDisabled(true);

    CoeficientesTecnicos.setTitle("&Coeficientes Técnicos");
    CoeficientesTecnicos.setDisabled(true);

    actionCH.setText("Coeficientes &Horizontales");
    actionCH.setDisabled(true);
    CoeficientesTecnicos.addAction(&actionCH);

    actionCV.setText("Coeficientes &Verticales");
    actionCV.setDisabled(true);
    CoeficientesTecnicos.addAction(&actionCV);

    actionEncadenamiento.setText("Clasificar cu&entas");
    actionEncadenamiento.setDisabled(true);
    CoeficientesTecnicos.addAction(&actionEncadenamiento);

    menuTools.addMenu(&CoeficientesTecnicos);

    actionVariableExogena.setText("Definir Variables &Exogenas");
    actionVariableExogena.setDisabled(true);

    menuTools.addAction(&actionVariableExogena);

    //Se agrega la acción de descomposición
    actionDescomposicion.setText("&Descomposicion");
    actionDescomposicion.setDisabled(true);

    menuTools.addAction(&actionDescomposicion);

    Modelos.setTitle("&Modelos");
    Modelos.setDisabled(true);

    actionModeloClasico.setText("Modelo &Clásico");
    actionModeloClasico.setDisabled(true);
    Modelos.addAction(&actionModeloClasico);

    actionCompararResultados.setText("(&1) Comparar Resultados(Modelo Clásico)");
    actionCompararResultados.setDisabled(true);
    Modelos.addAction(&actionCompararResultados);

    actionModeloNoClasico.setText("Modelo &No Clásico");
    actionModeloNoClasico.setDisabled(true);
    Modelos.addAction(&actionModeloNoClasico);

    actionCompararResultadosMNC.setText("(&2) Comparar Resultados(Modelo No Clásico)");
    actionCompararResultadosMNC.setDisabled(true);
    Modelos.addAction(&actionCompararResultadosMNC);

    PHClasico.setTitle("Precios Homogéneos Clásico");
    PHClasico.setDisabled(true);

    actionPHClasicoIncidencia100.setText("(&1) Incidencia 100%");
    actionPHClasicoIncidencia100.setDisabled(true);
    PHClasico.addAction(&actionPHClasicoIncidencia100);

    PHClasicoIncidencia.setTitle("(&2) Incidencia i%");
    PHClasicoIncidencia.setDisabled(true);

    actionPHCIncidenciaCuenta.setText("Por cue&nta");
    actionPHCIncidenciaCuenta.setDisabled(true);
    PHClasicoIncidencia.addAction(&actionPHCIncidenciaCuenta);

    actionPHCIncidenciaComponente.setText("Por co&mponente");
    actionPHCIncidenciaComponente.setDisabled(true);
    PHClasicoIncidencia.addAction(&actionPHCIncidenciaComponente);

    PHClasico.addMenu(&PHClasicoIncidencia);

    Modelos.addMenu(&PHClasico);

    PHNoClasico.setTitle("Precios Homogéneos No Clásico");
    PHNoClasico.setDisabled(true);

    actionPHNoClasicoIncidencia100.setText("(&1) Incidencia 100%");
    actionPHNoClasicoIncidencia100.setDisabled(true);
    PHNoClasico.addAction(&actionPHNoClasicoIncidencia100);

    PHNoClasicoIncidencia.setTitle("(&2) Incidencia i%");
    PHNoClasicoIncidencia.setDisabled(true);

    actionPHNCIncidenciaCuenta.setText("Por cue&nta");
    actionPHNCIncidenciaCuenta.setDisabled(true);
    PHNoClasicoIncidencia.addAction(&actionPHNCIncidenciaCuenta);

    actionPHNCIncidenciaComponente.setText("Por co&mponente");
    actionPHNCIncidenciaComponente.setDisabled(true);
    PHNoClasicoIncidencia.addAction(&actionPHNCIncidenciaComponente);

    PHNoClasico.addMenu(&PHNoClasicoIncidencia);
    Modelos.addMenu(&PHNoClasico);

    PreciosNH.setTitle("Precios No Homogéneos");
    PreciosNH.setDisabled(true);

    actionPNHIncidencia100.setText("(&1) Incidencia 100%");
    actionPNHIncidencia100.setDisabled(true);

    PreciosNH.addAction(&actionPNHIncidencia100);

    PreciosNHIncidencia.setTitle("(&2) Incidencia i%");
    PreciosNHIncidencia.setDisabled(true);

    actionPNHIncidenciaCuenta.setText("Por cue&nta");
    actionPNHIncidenciaCuenta.setDisabled(true);
    PreciosNHIncidencia.addAction(&actionPNHIncidenciaCuenta);

    actionPNHIncidenciaComponente.setText("Por co&mponente");
    actionPHNCIncidenciaComponente.setDisabled(true);
    PreciosNHIncidencia.addAction(&actionPNHIncidenciaComponente);

    PreciosNH.addMenu(&PreciosNHIncidencia);
    Modelos.addMenu(&PreciosNH);

    menuTools.addMenu(&Modelos);

    menuBar()->addMenu(&menuTools);

    //Menu Visualizacion
    menuViews.setTitle("&Visualización");
    menuViews.setDisabled(true);

    actionSeleccionarTabla.setText("&Seleccionar");
    actionSeleccionarTabla.setDisabled(true);
    menuViews.addAction(&actionSeleccionarTabla);

    menuBar()->addMenu(&menuViews);

    //Menu Ayuda
    menuHelp.setTitle("A&yuda");

    actionManual.setText("&Manual de Usuario");
    menuHelp.addAction(&actionManual);

    actionAcercaDe.setText("&Acerca De");
    menuHelp.addAction(&actionAcercaDe);

    menuBar()->addMenu(&menuHelp);

}

/**
    @brief Función que permite cerrar todo el programa
    @date 03/04/2015
    @author José Ruiz
*/
void MainWindow::closeEvent(QCloseEvent * event)
{
    QMessageBox msBox(QMessageBox::Question,"Alerta","¿Desea Salir?", QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    if(msBox.exec()==QMessageBox::No)
    {
        event->ignore();
    }
}

/**
    @brief Función que cargar crear la matriz en base al csv cargado
    @date 10/05/2015
    @author José Ruiz
    Modificado por:
    @author Rodrigo Boet
*/
void MainWindow::createMatrixCentralWidget()
{
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    QVBoxLayout * layoutLateralWidget = new QVBoxLayout;

    QTableWidget * tableWidget = new QTableWidget;
    tableWidget->setObjectName("TablaPrincipal");//Se le asigna nombre al objeto
    QGroupBox * groupBoxAccount = new QGroupBox;
    QPushButton * buttonEnd = new QPushButton;
    buttonEnd->setObjectName("AgregarCuentas");//Se le asigna nombre al objeto
    QPushButton * buttonRestaurar = new QPushButton;
    buttonRestaurar->setObjectName("RestaurarCuentas");//Se le asigna nombre al objeto
    QPushButton * buttonFinalizar = new QPushButton;
    buttonFinalizar->setObjectName("FinalizarCuentas");//Se le asigna nombre al objeto
    QPushButton * buttonModificar = new QPushButton;
    buttonModificar->setObjectName("ModificarCuentas");//Se le asigna nombre al objeto

    populateTable(tableWidget);
    tableWidget->setMaximumHeight(700);

    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tableWidget);

    //tableWidget->setFixedSize(750,750);
    layoutCentralWidget->addWidget(tableWidget);
    //layoutCentralWidget->addStretch();

    if(formLoadMatrix->ui->radioAccount->isChecked()){
        QStringList accounts = get_list(tableWidget,0,2,tableWidget->columnCount());
        numAccounts = diferent_elements(accounts);
    }

    QVBoxLayout * layoutAccounts = new QVBoxLayout;

    StackWidget *sw = new StackWidget(numAccounts, groupBoxAccount);
    layoutAccounts->addWidget(sw);

    groupBoxAccount->setFixedWidth(220);
    groupBoxAccount->setObjectName("GrupoCuentas");//Se le asigna nombre al objeto
    groupBoxAccount->setLayout(layoutAccounts);;
    groupBoxAccount->setTitle("Cuentas");
    groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                     "border-radius: 3px; margin-top: 0.5em;} "
                     "QGroupBox::title { subcontrol-origin: margin; "
                     "left: 10px; padding: 0 3px 0 3px; } ");


    layoutLateralWidget->addStretch(1);
    layoutLateralWidget->addWidget(groupBoxAccount);
    buttonEnd->setText("A&gregar");
    buttonEnd->setObjectName("AgregarCuentas");
    buttonEnd->setFixedWidth(100);
    buttonEnd->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");


    /***********          Nuevo boton para restaurar,editar y finalizar la tabla             *******/
    //buttonRestaurar->setText("&Restaurar");
    buttonRestaurar->setIcon(QIcon(":/imgs/undo-habilitado.png"));
    buttonRestaurar->setFlat(true);
    buttonRestaurar->setObjectName("Restaurar");
    buttonRestaurar->setFixedWidth(100);
    /*buttonRestaurar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");*/

    //buttonModificar->setText("&Editar ");
    buttonModificar->setIcon(QIcon(":/imgs/edit-deshabilitado.png"));
    buttonModificar->setDisabled(true);
    buttonModificar->setFlat(true);
    buttonModificar->setObjectName("Modificar");
    buttonModificar->setFixedWidth(100);
    /*buttonModificar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");*/


    buttonFinalizar->setText("&Finalizar");
    buttonFinalizar->setObjectName("Finalizar");
    buttonFinalizar->setFixedWidth(100);
    buttonFinalizar->setDisabled(true);
    buttonFinalizar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");

    QHBoxLayout *botonesSecundarios = new QHBoxLayout;
    botonesSecundarios->addWidget(buttonRestaurar);
    botonesSecundarios->addWidget(buttonModificar);
    QWidget *widgetBotonesSecundarios = new QWidget;
    widgetBotonesSecundarios->setLayout(botonesSecundarios);
    layoutLateralWidget->addWidget(widgetBotonesSecundarios);

    QHBoxLayout *botonesPrimarios = new QHBoxLayout;
    botonesPrimarios->addWidget(buttonEnd);
    botonesPrimarios->addWidget(buttonFinalizar);
    QWidget *widgetBotonesPrimarios = new QWidget;
    widgetBotonesPrimarios->setLayout(botonesPrimarios);
    layoutLateralWidget->addWidget(widgetBotonesPrimarios);

    layoutLateralWidget->addStretch(6);

    layoutCentralWidget->addLayout(layoutLateralWidget);

    connect(sw->comboAccount,SIGNAL(activated(int)),this,SLOT(slotAccChange()));

    connect(buttonEnd,SIGNAL(clicked()),this,SLOT(AgregarCuenta()));//**************Conexion del boton agregar**********************
    connect(buttonRestaurar,SIGNAL(clicked()),this,SLOT(RestaurarCeldas()));//Conexion del boton restaurar
    connect(buttonFinalizar,SIGNAL(clicked()),this,SLOT(FinalizarCuentas()));//Conexion del boton Finalizar
    connect(buttonModificar,SIGNAL(clicked()),this,SLOT(ModificarCuenta()));//Conexion del boton modificar


    layoutCentralWidget->sizeHint();

    tabWidget->addTab(new QWidget,"MCS");
    QWidget *widget= tabWidget->widget(1);
    widget->setLayout(layoutCentralWidget);


    /*  ***********         Se agrega la columna en la que se asignan los nombre            **************           */
    if(formLoadMatrix->ui->radioComponent->isChecked())
    {
        tableWidget->insertRow(0);
        tableWidget->insertColumn(0);
        noEditColZero(tableWidget);
        /*              Se agregan elementos a la recien creada fila/columna        */
        int contador=tableWidget->rowCount();
        for(int i=1;i<contador;i++)
        {
            QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
            ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
            tableWidget->setItem(0,i,ValoraInsertar);

            QTableWidgetItem *ValoraInsertar2 = new QTableWidgetItem;
            ValoraInsertar2->setFlags(ValoraInsertar2->flags() ^ Qt::ItemIsEditable);
            tableWidget->setItem(i,0,ValoraInsertar2);
        }
    }
    else if(formLoadMatrix->ui->radioAccount->isChecked()){
        loadsAccounts(tableWidget);
    }

    //Al terminar la carga de la tabla se activa el menu de Operaciones
    menuTools.setEnabled(true);
    menuViews.setEnabled(true);

    tabWidget->setCurrentIndex(1);//Se seleciona la pestaña MCS

    actionLoadMatrix.setDisabled(true);

    actionExportMatrix.setEnabled(true);

    /****          Se conectan las acciones para coeficientes tecnicos horizontales y verticales      ****/
    connect(&actionCH, SIGNAL(triggered()), this,SLOT(slotCoeficienteHorizontal()));
    connect(&actionCV, SIGNAL(triggered()), this,SLOT(slotCoeficienteVertical()));
    //Se conecta la accion para la variables exogenas
    connect(&actionVariableExogena,SIGNAL(triggered()),this,SLOT(slotVariableExogena()));
}

/**
    @brief Función que se encarga de cargar los datos de un csv en Widget de tabla
    @date 15/05/2015
    @author José Ruiz
    Modificado por
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::populateTable(QTableWidget * tableWidget)
{
    //Se abre el archivo en modo lectura
    QFile file(csvFilePath);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString linea = in.readLine();//Se lee la primera linea(con los nombres)
    QStringList lines = linea.split(";");//Se separan por ; y se guardan en una lista
    int column = lines.count();
    CrearTablaVacia(column+2,tableWidget);//Se crea una tabla vacia a modo de matriz cuadrada
    QStringList Accounts;
    if(formLoadMatrix->ui->radioAccount->isChecked())
    {
        Accounts = lines;
        linea = in.readLine();
        lines = linea.split(";");
    }
    //Se leen los componentes y se distribuyen en filas y columnas
    for(int i=1;i<=column;i++)
    {
        QTableWidgetItem *itemFila = new QTableWidgetItem(lines.at(i-1));
        CellStyleComponente(itemFila);
        itemFila->setFlags(itemFila->flags() ^ Qt::ItemIsEditable);
        tableWidget->setItem(0,i,itemFila);
        QTableWidgetItem *itemColumna = new QTableWidgetItem(lines.at(i-1));
        CellStyleComponente(itemColumna);
        itemColumna->setFlags(itemColumna->flags() ^ Qt::ItemIsEditable);
        tableWidget->setItem(i,0,itemColumna);
        QCoreApplication::processEvents();
    }
    int row = 1;
    while(!in.atEnd())//Se lee el archivo hasta el final
    {
        linea = in.readLine();
        lines = linea.split(";");
        //Se recorre el resto del archivo y se anexan los valores
        for(int i=1;i<=column;i++)
        {
            double value = 0;
            if(i<=lines.count())//En caso de que hallan mas componentes que columnas
            {
                value = lines.at(i-1).toDouble();
            }
            QTableWidgetItem *tw = new QTableWidgetItem(numberFormat(value));
            tw->setFlags(tw->flags() ^ Qt::ItemIsEditable);
            tableWidget->setItem(row,i,tw);
            QCoreApplication::processEvents();
        }
        QCoreApplication::processEvents();
        row++;
    }
    file.close();
    //Aqui se evalua el caso particular de que las falten filas con respecto a los componentes
    if(row-1<column)
    {
        for (int j=row-1;j<=column;j++)
        {
            for(int i=1;i<=column;i++)
            {
                double value = 0;
                QTableWidgetItem *tw = new QTableWidgetItem(numberFormat(value));
                tw->setFlags(tw->flags() ^ Qt::ItemIsEditable);
                tableWidget->setItem(row-1,i,tw);
            }
            QCoreApplication::processEvents();
            row++;
        }
        QCoreApplication::processEvents();
    }
    //Se agregan las cuentas si se selecciono la opción correspondiente
    if(formLoadMatrix->ui->radioAccount->isChecked())
    {
        noEditColZero(tableWidget);
        tableWidget->insertColumn(0);
        tableWidget->insertRow(0);
        int limit = tableWidget->rowCount();
        for(int i = 2;i<limit;i++)
        {
            QTableWidgetItem *itemFila = new QTableWidgetItem(Accounts.at(i-2));
            CellStyle(itemFila);
            itemFila->setFlags(itemFila->flags() ^ Qt::ItemIsEditable);
            itemFila->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(0,i,itemFila);
            QTableWidgetItem *itemColumna = new QTableWidgetItem(Accounts.at(i-2));
            CellStyle(itemColumna);
            itemColumna->setFlags(itemColumna->flags() ^ Qt::ItemIsEditable);
            itemColumna->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i,0,itemColumna);
            QCoreApplication::processEvents();
        }
        QCoreApplication::processEvents();
        ItemsNoEditable(tableWidget,1,2,0);
    }

}

/**
    @brief Función que permite cargar las cuentas
    @date 29/07/2016
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::loadsAccounts(QTableWidget *tw)
{
    int column = tw->rowCount();
    QStringList numberAccounts = get_list(tw,0,2,column);
    QVector<QString> vector;
    int init = 3;
    foreach (QString item,numberAccounts) {
        if(!vector.contains(item))
        {
            int inicio = init;
            int fin = (inicio+numberAccounts.count(item))-1;
            init = fin+1;
            vector.append(item);
            vector.append(QString::number(inicio));
            vector.append(QString::number(fin));
            if(numberAccounts.count(item)>1)
            {
                tw->setSpan(0,inicio-1,1,numberAccounts.count(item));
                tw->setSpan(inicio-1,0,numberAccounts.count(item),1);
            }
        }
    }
    //Se cargan los datos en la cuenta
    for(int i=0;i<numAccounts;i++)
    {
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
        QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(i+1));
        QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));
        le->setText(vector.at(i*3));
        SBStart->setValue(vector.at((i*3)+1).toInt());
        SBEnd->setValue(vector.at((i*3)+2).toInt());
    }
    TotalPrincipalTable(tw,PrincipalTable,2);
    bool iguales = true;
    CalcularTotales(tw,2,iguales);//Se llama a la funcion que agregue una nueva fila y columna con los totales respectivos
    if(!iguales)
    {
        QMessageBox::warning(this,"Alerta","El Total de una(s) fila(s)\n es distinto al Total de\nuna(s) columna(s)");
    }
    setAccountTitle(tw);

    //Se ocultan el StackedWidget con los datos de la cuenta
    hideStackedWidget();

    /*       Luego de calcular los totales se habilitan las opciones del menu herramientas       */
    CoeficientesTecnicos.setEnabled(true);
    actionCH.setEnabled(true);
    actionCV.setEnabled(true);
    actionVariableExogena.setEnabled(true);
    /*              Se habilitan las opciones del menú visualización            */
    actionSeleccionarTabla.setEnabled(true);
    connect(&actionSeleccionarTabla,SIGNAL(triggered()),this,SLOT(slotSeleccionarTabla()));
}

/**
    @brief Función que permite transformar un flotante en string y darle formato a los números con separador de miles
    @date 05/05/2015
    @author José Ruiz
    Modificado por
    @author Rodrigo Boet
    @param <d> Recibe el número al que se le dará formato
    @return <stringNumber> retorna el número con formato como un string
*/
QString MainWindow::numberFormat(double & d) {

    bool controlador = false;
    if(d<0)
    {
        controlador = true;
        d *=-1;
    }


    QString stringNumber = QString::number(d, 'f', precission);
    for(int point = 0, i = (stringNumber.lastIndexOf('.') == -1 ? stringNumber.length() : stringNumber.lastIndexOf('.')); i > 0; --i, ++point)
    {
        if(point != 0 && point % 3 == 0)
        {
            stringNumber.insert(i, '*');
        }
    }
    stringNumber.replace(".", ",");
    stringNumber.replace("*", ".");
    if(controlador)
    {
        stringNumber.insert(0,"-");
    }
    return stringNumber;
}

//  FA_002
/*                  Aquí se encuentra el menú de ayuda                */
/**
    @brief Función para abrir el manual
    @date 20/10/2015
    @author Rodrigo Boet
*/
void MainWindow::abrirManual()
{
    QDesktopServices::openUrl(QUrl("/usr/share/mmcs/Usuario/Entrada.html",QUrl::TolerantMode));
}

/**
    @brief Función para abrir la sección acerca de
    @date 20/10/2015
    @author Rodrigo Boet
*/
void MainWindow::acercaDe()//Funcion para el mensaje acerca de
{
    QString Mensaje = "Sistema de Manejo de Matrices de Contabilidad Social\n\n";
    Mensaje+="Centro Nacional de Desarrollo e Investigación en Tecnologías Libres, 2015.\n";
    Mensaje+="Distribuido bajo la Licencia de Software V 1.2\n\n";
    Mensaje+="https://mpv.cenditel.gob.ve/mmcs";
    QMessageBox::information(this,"Acerca de..",Mensaje);
}

//  Main_001
/*                      Aquí se encuentra el centro de la aplicación                   */
/**
    @brief Función núcleo de la aplicación
    @date 11/04/2015
    @author José Ruiz
    Modificada por
    @author Rodrigo Boet
*/
MainWindow::MainWindow()
    : actionNewProject(this),actionLoadMatrix(this), actionExportMatrix(this), actionQuit(this),actionCH(this), actionCV(this),
      actionVariableExogena(this),actionEncadenamiento(this),actionModeloClasico(this), actionDescomposicion(this),
      actionCompararResultados(this),actionModeloNoClasico(this),actionCompararResultadosMNC(this),actionPHClasicoIncidencia100(this),
      actionPHCIncidenciaCuenta(this),actionPHCIncidenciaComponente(this),actionPHNoClasicoIncidencia100(this),actionPHNCIncidenciaCuenta(this),
      actionPHNCIncidenciaComponente(this),actionPNHIncidencia100(this),actionPNHIncidenciaCuenta(this),actionPNHIncidenciaComponente(this),
      actionSeleccionarTabla(this),actionManual(this),actionAcercaDe(this),formLoadMatrix(0)
{
    tabWidget = new QTabWidget;

    /*    Opcion de la cuenta exogena, 0 para decir que nos se selecciono ninguna, 1 que se seleccionaron algunas
                                    y 2 para decir que se seleccionaron todas*/
    opcionCuentaExogena = 0;
    opcionVentanaExogena = 0;
    /*  Estas opciones se utilizan para no crear multiples ventanas de las requeridas durante la ejecucacion de programa,
     se crea una sola y luego solo se abre*/

    opcionExportarMatriz = 0;
    opcionEncadenamientos = 0;
    opcionMa = 0;
    opcionMb = 0;
    opcionFormCompararResultados = 0;
    opcionFormCompararResultadosMNC = 0;
    opcionMAT = 0;
    opcionMBT = 0;
    opcionPNHT = 1;
    opcionFormPNH = 0;
    /*      Estas variables permiten tener el control de los procedimientos que se pueden generar multiples ventanas */
    cantidadSelecciones = 1;
    cantidadEncadenamientos = 1;
    cantidadEscenarios = 1;
    cantidadResultados = 1;
    cantidadMNC = 1;
    cantidadResultadosMNC = 1;
    cantidadPHCindidenciaiCuenta = 1;
    cantidadPHCindidenciaiComponente = 1;
    cantidadPHNCindidenciaiCuenta = 1;
    cantidadPHNCindidenciaiComponente = 1;
    cantidadPNHincidencia100 = 1;
    cantidadPNHincidenciaiCuenta = 1;
    cantidadPNHincidenciaiComponente = 1;

    initGUI();

    connect(&actionNewProject,SIGNAL(triggered()),this,SLOT(slotNuevoProyecto()));
    connect(&actionLoadMatrix, SIGNAL(triggered()), this,
            SLOT(slotLoadMatrix()));
    connect(&actionExportMatrix, SIGNAL(triggered()), this,
            SLOT(slotExportMatrix()));
    connect(&actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    
    showMaximized();
}

/**
    @brief Función que inicializar la interfaz gráfica de la aplicación
    @date 01/04/2015
    @author José Ruiz
*/
void MainWindow::initGUI()
{
    createMenuBar();
    createCentralWidget();
    matricesMenuBar();
    connect(&actionManual,SIGNAL(triggered()),this,SLOT(abrirManual()));
    connect(&actionAcercaDe,SIGNAL(triggered()),this,SLOT(acercaDe()));
}

//Main_002
/*              Aqui comienzan las funciones luego de cargar la matriz        */
/**
    @brief Función para cambiar los iconos de habilitado/deshabilitado en el widget derecho
    @date 10/06/2015
    @author Rodrigo Boet
*/
void MainWindow::slotAccChange()
{
    StackWidget *sw = findChild<StackWidget *>();
    int indice = sw->comboAccount->currentIndex();
    QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(indice + 1));
    QPushButton *Modificar = findChild<QPushButton *>("Modificar");
    if(!le->isEnabled())
    {
        Modificar->setEnabled(true);
        Modificar->setIcon(QIcon(":/imgs/edit-habilitado"));
    }
    else
    {
        Modificar->setDisabled(true);
        Modificar->setIcon(QIcon(":/imgs/edit-deshabilitado"));
    }
}

/**
    @brief Función para esconder el StackWidget que tiene los datos de las cuentas
    @date 29/07/2016
    @author Rodrigo Boet
*/
void MainWindow::hideStackedWidget()
{
    QPushButton *Agregar = findChild<QPushButton *>("AgregarCuentas");
    QPushButton *Restaurar = findChild<QPushButton *>("Restaurar");
    Agregar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    Agregar->setEnabled(false);
    Agregar->setVisible(false);
    Restaurar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    Restaurar->setEnabled(false);
    Restaurar->setVisible(false);
    QPushButton *Modificar = findChild<QPushButton *>("Modificar");
    Modificar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    Modificar->setEnabled(false);
    Modificar->setVisible(false);

    QPushButton *Finalizar = findChild<QPushButton *>("Finalizar");
    Finalizar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    Finalizar->setEnabled(false);
    Finalizar->setVisible(false);

    QGroupBox *groupbox = findChild<QGroupBox *>("GrupoCuentas");
    groupbox->setVisible(false);
}

/**
    @brief Función que permite agregar una cuenta siempre y cuando cumpla con la validación
    @date 10/06/2015
    @author Rodrigo Boet
*/
void MainWindow::AgregarCuenta()
{
    QMessageBox msBox(QMessageBox::Question,"Agregar cuenta","¿Está seguro que agregar la cuenta?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");//Se busca la tabla que se creo
        StackWidget *sw = findChild<StackWidget *>();//Se buscan las cuentas creadas

        /* ******   Se leen los campos del widget izquierdo   ******* */;

        int index=sw->comboAccount->currentIndex();

        /*****       Se cargan la linea y las spin box correpondientes a la cuenta seleccionada       *****/

        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(index + 1));
        QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(index+1));
        QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(index+1));

        int inicio=SBStart->value();
        int fin=SBEnd->value();
        QString nombreCuenta=le->text();

        bool cuenta = comprobarNombreCuenta(nombreCuenta,index);

        if(nombreCuenta.isEmpty() or nombreCuenta.isNull())
        {
            QMessageBox::warning(this,"Alerta","El nombre de la cuenta esta vacio");
        }
        else if(!le->isEnabled())
        {
            QMessageBox::warning(this,"Alerta","Esta cuenta ya fue\nagregada");
        }
        else if(cuenta)
        {
            QMessageBox::warning(this,"Alerta","Este nombre de cuenta\nya existe");
        }
        else
        {
            int cantidad_filas=tw->rowCount();

            if(inicio>cantidad_filas or fin>cantidad_filas)//Se verifica que los valores no excedan el tamaño de la tabla
            {
                QMessageBox::warning(this,"Alerta","Valores mayores al tamaño\n de la tabla");
            }
            else if(inicio>fin)
            {
                QMessageBox::warning(this,"Alerta","El inicio es mayor\nque el fin");
            }
            else
            {
                /***  Se comprueba si la celda de la tabla esta ocupada por otra cuenta  ***/
                bool centinela=true;
                if(inicio>2 and fin>2){
                    for(int i=0;i<numAccounts;i++)
                    {
                        if(i!=index)
                        {
                            QSpinBox *oI = findChild<QSpinBox *>(QString("accountstart %1").arg(i+1));
                            QSpinBox *oF = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));
                            int otroInicio = oI->text().toInt();
                            int otroFin = oF->text().toInt();
                            for(int k=inicio;k<=fin;k++)
                            {
                                for(int j=otroInicio;j<=otroFin;j++)
                                {
                                    if(k==j)
                                    {
                                        centinela=false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

                /*  *****    Se asigna el nombre de la cuenta a las cabecereas de la tabla en el rango(inicio,fin)     *****    */
                if((inicio>2 && fin>2) and (centinela))
                {
                    for(int i=inicio-1;i<fin;i++)
                    {
                        QTableWidgetItem *ValoraInsertarFila = new QTableWidgetItem(nombreCuenta);
                        ValoraInsertarFila->setTextAlignment(Qt::AlignCenter);
                        ValoraInsertarFila->setFlags(ValoraInsertarFila->flags() ^ Qt::ItemIsEditable);
                        ValoraInsertarFila->setTextAlignment(Qt::AlignCenter);
                        CellStyle(ValoraInsertarFila);
                        tw->setItem(0,i,ValoraInsertarFila);
                        QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem(nombreCuenta);
                        ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
                        ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
                        ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
                        CellStyle(ValoraInsertarColumna);
                        tw->setItem(i,0,ValoraInsertarColumna);
                    }
                    int espacio=(fin-inicio)+1;
                    if(espacio>1)
                    {
                        tw->setSpan(inicio-1,0,espacio,1);
                        tw->setSpan(0,inicio-1,1,espacio);
                    }
                    /*****              Se inhabilita el boton de la linea  y los spinbox  *******/
                    le->setEnabled(false);
                    SBStart->setEnabled(false);
                    SBEnd->setEnabled(false);
                    QPushButton *Modificar = findChild<QPushButton *>("Modificar");
                    Modificar->setEnabled(true);
                    Modificar->setIcon(QIcon(":/imgs/edit-habilitado"));
                }
                else if(!centinela)
                {
                    QMessageBox::warning(this,"Alerta","Valores en el espacio de otra cuenta");
                }
                else
                {
                    QMessageBox::warning(this,"Alerta","Valores invalidos");
                }

            }
        }
    }
    bool Centinela=ComprobarCuentas();
    if(Centinela)
    {
        QPushButton *Finalizar = findChild<QPushButton *>("Finalizar");
        Finalizar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        Finalizar->setEnabled(true);
    }
}

/**
    @brief Función que permite finalizar las cuentas y calcular totales is se llenaron todas las cuentas
    @date 10/06/2015
    @author Rodrigo Boet
*/
void MainWindow::FinalizarCuentas()
{
    QMessageBox msBox(QMessageBox::Question,"Finalizar Carga","¿Está seguro que desea finalizar?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        FormCargando *cargando = new FormCargando(this);
        cargando->show();
        bool Centinela=ComprobarCuentas();//Se llama a la funcion que comprueba si todos los campos de las cuentas estan llenos
        if(Centinela)
        {
            //Se oculta el widget con los datos de las cuentas
            hideStackedWidget();

            QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
            TotalPrincipalTable(tw,PrincipalTable,2);
            bool iguales = true;
            CalcularTotales(tw,2,iguales);//Se llama a la funcion que agregue una nueva fila y columna con los totales respectivos
            if(!iguales)
            {
                QMessageBox::warning(this,"Alerta","El Total de una(s) fila(s)\n es distinto al Total de\nuna(s) columna(s)");
            }
            setAccountTitle(tw);

            /*       Luego de calcular los totales se habilitan las opciones del menu herramientas       */
            CoeficientesTecnicos.setEnabled(true);
            actionCH.setEnabled(true);
            actionCV.setEnabled(true);
            actionVariableExogena.setEnabled(true);
            /*              Se habilitan las opciones del menú visualización            */
            actionSeleccionarTabla.setEnabled(true);
            connect(&actionSeleccionarTabla,SIGNAL(triggered()),this,SLOT(slotSeleccionarTabla()));
         }
        else
        {
            QMessageBox::warning(this,"Alerta","Debe llenar correctamente y agregar todas las cuentas");
        }
        QTimer::singleShot(1000,cargando,SLOT(hide()));
        delete cargando;
    }
}

/**
    @brief Función que almacena los valores de la tabla principal en una matriz
    @date 21/06/2016
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <Matriz> Recibe la matriz donde se almacenaran los resultados
    @param <init> Recibe el inicio de donde comenzarán las iteraciones
*/
void MainWindow::TotalPrincipalTable(QTableWidget *tw,MatrixXd &Matriz,int init)
{
    int cantidad=tw->rowCount();
    Matriz.resize(cantidad-1,cantidad-1);
    for(int i=init;i<cantidad;i++)
    {
        double totalFila = 0;
        double totalColumna = 0;
        for(int j=init;j<cantidad;j++)
        {
            QString itemf=Separador(tw->item(i,j),true);
            double thisFila=itemf.toDouble();
            QString itemc=Separador(tw->item(j,i),true);
            double thisCol=itemc.toDouble();
            Matriz(i-init,j-init) = thisFila;
            Matriz(j-init,i-init) = thisCol;
            totalFila += Matriz(i-init,j-init);
            totalColumna += Matriz(j-init,i-init);
        }
        Matriz(i-init,cantidad-init) = totalFila;
        Matriz(cantidad-init,i-init) = totalColumna;

    }
}

/**
    @brief Función que calcula los totales por fila/columna
    @date 12/06/2015
    @author Rodrigo Boet
    @param <tableWidget> Recibe el widget de la tabla
    @param <inicio> Recibe el párametro por donde iniciaran las iteraciones
    @param <iguales> Recibe el parametro que verifica si el total la columna i es igual al total de la columna j
*/
void MainWindow::CalcularTotales(QTableWidget *tableWidget,int inicio,bool &iguales)//Se calculan los totales por fila/columna
{
    int filas=tableWidget->rowCount();
    int columnas=tableWidget->columnCount();
    /*******       Se inserta la nueva fila y columna para los totales, asi como es texto corespondiente             *****/
    tableWidget->insertRow(filas);
    tableWidget->insertColumn(columnas);
    QTableWidgetItem *ColumnaTotal = new QTableWidgetItem;
    ColumnaTotal->setText("Total en Columna");
    CellStyle(ColumnaTotal);//Estilo de la Celda
    ColumnaTotal->setFlags(ColumnaTotal->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *FilaTotal = new QTableWidgetItem;
    FilaTotal->setText("Total en Fila");
    CellStyle(FilaTotal);//Estilo de la Celda
    FilaTotal->setFlags(FilaTotal->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(columnas,inicio-1,ColumnaTotal);
    tableWidget->setItem(inicio-1,filas,FilaTotal);
    for(int i=inicio;i<filas;i++)
    {
        double SumaFila=0;
        double SumaColumna=0;
        for(int j=inicio;j<filas;j++)
        {
            QString fila=Separador(tableWidget->item(j,i),true);
            double thisFila=fila.toDouble();
            QString columna=Separador(tableWidget->item(i,j),true);
            double thisColumna=columna.toDouble();
            SumaFila+=thisFila;
            SumaColumna+=thisColumna;
        }
        QTableWidgetItem *Valor1 = new QTableWidgetItem;
        Valor1->setText(QString::number(SumaFila,'f',precission));
        QString value1 = Separador(Valor1,false);
        Valor1->setText(value1);
        Valor1->setFlags(Valor1->flags() ^ Qt::ItemIsEditable);
        Valor1->setTextAlignment(Qt::AlignCenter);
        CellStyle(Valor1);//Estilo de la Celda
        QTableWidgetItem *Valor2 = new QTableWidgetItem;
        Valor2->setText(QString::number(SumaColumna,'f',precission));
        QString value2 = Separador(Valor2,false);
        Valor2->setText(value2);
        Valor2->setFlags(Valor2->flags() ^ Qt::ItemIsEditable);
        Valor2->setTextAlignment(Qt::AlignCenter);
        CellStyle(Valor2);//Estilo de la Celda
        tableWidget->setItem(filas,i,Valor1);//Inserta en Filas
        tableWidget->setItem(i,filas,Valor2);//Inserta en Columnas
        if(!(qAbs(SumaFila-SumaColumna)<0.1))
        {
            iguales = false;
        }
    }
    /*          Se coloca como no editable la última celda      */
    QTableWidgetItem *Valor = new QTableWidgetItem;
    Valor->setFlags(Valor->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(filas,columnas,Valor);
    int cantidad = tableWidget->rowCount();
    ItemsNoEditable(tableWidget,0,inicio-1,cantidad-1);
}

/**
    @brief Función que permite restaurar el titulo de las cuentas en las celdas
    @date 15/06/2015
    @author Rodrigo Boet
*/
void MainWindow::RestaurarCeldas()
{
    QMessageBox msBox(QMessageBox::Question,"Restaurar Celdas","¿Desea Restaurar el titulo de todas las celdas?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
        insertremoveRowCol(tw,0,false);
        insertremoveRowCol(tw,0,true);
        int cantidad = tw->rowCount();
        for(int i = 0; i<cantidad;i++)
        {
            QTableWidgetItem *fila = new QTableWidgetItem;
            fila->setFlags(fila->flags() ^ Qt::ItemIsEditable);
            tw->setItem(0,i,fila);
            QTableWidgetItem *columna = new QTableWidgetItem;
            columna->setFlags(columna->flags() ^ Qt::ItemIsEditable);
            tw->setItem(i,0,columna);
        }
    }
}

/**
    @brief Función ue permite habilitar la edicion de una cuenta una vez agregada
    @date 16/06/2015
    @author Rodrigo Boet
*/
void MainWindow::ModificarCuenta()
{
    QMessageBox msBox(QMessageBox::Question,"Modificar Cuenta","¿Desea Modificar la Cuenta Actual?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        StackWidget *sw = findChild<StackWidget *>();//Se buscan las cuentas creadas
        int index=sw->comboAccount->currentIndex();
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(index + 1));
        QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(index+1));
        QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(index+1));
        le->setEnabled(true);
        SBStart->setEnabled(true);
        SBEnd->setEnabled(true);
    }
}

/**
    @brief Función que verifica que las lineas de texto y spin box de todas las cuentas no esten vacíos
    @date 18/06/2015
    @author Rodrigo Boet
    @return <centinela> retorna si se cumple o no con la condición
*/
bool MainWindow::ComprobarCuentas()
{
    bool centinela=true;
    StackWidget *sw = findChild<StackWidget *>();
    int count=sw->comboAccount->count();
    for(int i=0;i<count;i++)
    {
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
        QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(i+1));
        QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));
        if((le->text().isEmpty()) || (SBStart->text().toInt()==0) || (SBEnd->text().toInt()==0) || (le->isEnabled()))
        {
            centinela=false;
        }
    }
    //Se compureba si las celdas donde va el nombre de las cuentas esta vacia
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
    count = tw->rowCount();
    for(int i=2;i<count;i++)
    {
        if(tw->item(0,i)->text().isEmpty() or tw->item(i,0)->text().isEmpty())
        {
            centinela = false;
        }
    }
    return centinela;
}

/**
    @brief Función que comprueba que no existan nombre de cuentas iguales
    @date 20/06/2015
    @author Rodrigo Boet
    @param <nombre> Recibe el nombre que se comprobará
    @param <indice> Recibe el indice de la cuenta que se comprueba
    @return <cuenta> retorna verdadero si el nombre se repite y falso en caso contrario
*/
bool MainWindow::comprobarNombreCuenta(QString nombre,int indice)
{
    bool cuenta = false;
    for(int i=0;i<numAccounts;i++)
    {
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
        if(le->text()==nombre and indice+1!=i+1)
        {
            cuenta = true;
        }
    }
    return cuenta;
}

/**
    @brief Función que obtiene el nombre las cuentas a traves de los lineeidt y los retorna en una lista de string
    @date 10/06/2015
    @author Rodrigo Boet
    @param <contador> Recibe el número de cuentas
    @return <MiLista> retorna una lista de los nombres de las cuentas
*/
QStringList MainWindow::ObtenerNombreCuenta(int contador)
{
    QStringList MiLista;
    for(int i = 0;i<contador;i++)
    {
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
        MiLista.append(le->text());
    }
    return MiLista;
}

/**
    @brief Función que obtiene los inicios/fin de las cuentas y las retorna como entero en una lista si la opción es cero crea la lista por el inicio, de lo contrario la crea por el fin
    @date 01/07/2015
    @author Rodrigo Boet
    @param <contador> Recibe el limite de la iteración
    @param <opcion> Recibe la opción (0 para inicio de la cuenta y 1 para fin de la cuenta)
    @return <Lista> retorna una lista con los elementos
*/
QList<int> MainWindow::ObtenerLimitesCuenta(int contador,int opccion)
{
    QList<int> Lista;
    for(int i=0;i<contador;i++)
    {
        if(opccion==0)
        {
            QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(i+1));
            Lista.append(SBStart->text().toInt());

        }
        else
        {
            QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));
            Lista.append(SBEnd->text().toInt());
        }
    }
    return Lista;
}

//FG_001

/**
    @brief Función que permite calcular el Coeficiente Tecnico Horizontal (An)
    @date 05/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <nuevaTabla> Recibe el widget de la tabla en la que agregaran los valores
    @param <tablaOriginal> Recibe el widget de la tabla original
    @param <count> Recibe el limite para las iteraciones
    @param <endogena> Recibe si se calculará el An para una tabla endogeno o no
*/
void MainWindow::CalcularAn(QTableWidget *tw,QTableWidget *nuevaTabla,QTableWidget *tablaOriginal,int count,bool endogena)//Funcion para calcular el Coeficiente Tecnico Horizontal (An)
{
    if(endogena)
    {
        An.resize(count-3,count-3);
    }
    for(int i=0;i<count-1;i++)
    {
        double total;
        QString value;
        for(int j=0;j<count-1;j++)
        {
            if(i>=2 and j>=2)
            {
                if(endogena)
                {
                    int contador = tablaOriginal->rowCount()-1;
                    value = Separador(tablaOriginal->item(contador,i),true);
                    value = QString::number(value.toDouble(),'f',precission);
                    total=value.toDouble();
                }
                else
                {
                    total = PrincipalTable(count-3,i-2);
                }
                double valor=PrincipalTable(j-2,i-2);
                if(total==0)//Se comprueba en caso de que el total sea zero
                {
                    valor=0;
                }
                else
                {
                    valor/=total;//Se divide el valor de la celda entre el total correspondiente

                }
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',precission));
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                QString value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                nuevaTabla->setItem(j,i,ValoraInsertar);
                if(endogena)
                {
                    An(j-2,i-2) = valor;
                }
            }
            /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
            else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=tw->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                if((i==0 && j>1)||(j==0 && i>1))
                {
                    CellStyle(ValoraInsertar);
                }
                else if((i==1 && j>1)||(j==1 && i>1))
                {
                    CellStyleComponente(ValoraInsertar);
                }
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
            /*      Se colocan no editables algunas de las celdas que estan vacias*/
            else
            {
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
       }
    }
}

/**
    @brief Función que permite obtener el indice de una pestaña buscada por un nombre dado
    @date 10/07/2015
    @author Rodrigo Boet
    @param <text> Recibe el nombre que se desea buscar
    @return <indice> retorna el número de la pestaña
*/
int MainWindow::ObtenerIndice(QString text)
{
    int cantidad=tabWidget->count();
    int indice=0;
    for(int i=0;i<cantidad;i++)
    {
        if(tabWidget->tabText(i)==text)
        {
            indice=i;
            break;
        }
    }
    return indice;
}

/**
    @brief Función que agregar los componentes y cuentas a partir de la matriz endogena-endogena
    @date 10/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::titleEndogena(QTableWidget *tw)
{
    QTableWidget *endogena = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int cantidad = endogena->columnCount()-1;
    tw->insertRow(0);
    tw->insertRow(0);
    tw->insertColumn(0);
    tw->insertColumn(0);
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<cantidad;j++)
        {
            if(j>1)
            {
                QString item=endogena->item(i,j)->text();
                QTableWidgetItem *fila = new QTableWidgetItem(item);
                fila->setFlags(fila->flags() ^ Qt::ItemIsEditable);
                QTableWidgetItem *columna = new QTableWidgetItem(item);
                columna->setFlags(columna->flags() ^ Qt::ItemIsEditable);
                if(i==0)
                {
                    CellStyle(fila);
                    CellStyle(columna);
                }
                else
                {
                    CellStyleComponente(fila);
                    CellStyleComponente(columna);
                }
                tw->setItem(i,j,fila);
                tw->setItem(j,i,columna);
            }
            else
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                tw->setItem(i,j,item);
            }

        }
    }
}

/**
    @brief Función que permite colocar los titulos de las cuentas
    @date 10/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::setAccountTitle(QTableWidget *tw)
{
    int myinicio=999;
    for(int i=0;i<numAccounts;i++)
    {
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
        QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(i+1));
        QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));

        int inicio=SBStart->value();
        int fin=SBEnd->value();
        QString nombreCuenta=le->text();

        if(myinicio>inicio)
        {
            myinicio=inicio;
        }

        for(int i=inicio-1;i<fin;i++)
        {
            QTableWidgetItem *ValoraInsertarFila = new QTableWidgetItem(nombreCuenta);
            ValoraInsertarFila->setTextAlignment(Qt::AlignCenter);
            ValoraInsertarFila->setFlags(ValoraInsertarFila->flags() ^ Qt::ItemIsEditable);
            CellStyle(ValoraInsertarFila);
            tw->setItem(0,i,ValoraInsertarFila);
            QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem(nombreCuenta);
            ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
            ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
            CellStyle(ValoraInsertarColumna);
            tw->setItem(i,0,ValoraInsertarColumna);
        }

        int espacio=(fin-inicio)+1;
        if(espacio>1)
        {
            tw->setSpan(inicio-1,0,espacio,1);
            tw->setSpan(0,inicio-1,1,espacio);
        }
    }
    ItemsNoEditable(tw,1,myinicio-1);
}

/*                  Funcion para agregar/quitar columnas y filas                    */
/**
    @brief Función que permite agregar/quitar columnas y filas
    @date 10/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <rowcol> Recibe el sitio donde se agregarán las columnas y filas
    @param <opcion> Recibe la opción (Verdadero para agregar y Falso para quitar)
    @return <elements> retorna una lista con los elementos
*/
void MainWindow::insertremoveRowCol(QTableWidget *tw, int rowcol, bool opcion)
{
    if(opcion)//Si la opcion es verdadero se agrega
    {
        tw->insertRow(rowcol);
        tw->insertColumn(rowcol);
        int count = tw->rowCount();
        ItemsNoEditable(tw,count-1,count);
    }
    else//de lo contrario se remueve
    {
        tw->removeColumn(rowcol);
        tw->removeRow(rowcol);
    }
}

/**
    @brief Función que permite agregar/quitar el separador de miles y la coma en las tablas
    @date 25/09/2015
    @author Rodrigo Boet
    @param <ti> Recibe el item que se modificará
    @param <quitar> Recibe la un booleano (Verdadero para quitar y Falso para colocar)
    @return <elements> retorna el elemento con/sin separador
*/
QString MainWindow::Separador(QTableWidgetItem *ti,bool quitar)
{
    QString value=ti->text();
    if(quitar)
    {
        value.remove(QChar('.'));
        value.replace(",",".");
    }
    else
    {
        double val =value.toDouble();
        value = numberFormat(val);
    }
    return value;
}

/**
    @brief Función que permite clonar una tabla y todo su contenido
    @date 10/09/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla de la que se copiarán los datos
    @param <nuevaTabla> Recibe el widget de la tabla en la que se copiarán los datos
    @param <cantidad> Recibe el tamaño de la tabla
*/
void MainWindow::clonarTabla(QTableWidget *tw,QTableWidget *nuevaTabla,int cantidad)
{
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            if(i>=2 && j>=2)
            {
                QString value = Separador(tw->item(i,j),true);
                double valor= value.toDouble();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',precission));
                value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
            else if(((i==0 && j>1)||(j==0 && i>1)) or ((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=tw->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                if((i==0 && j>1)||(j==0 && i>1))
                {
                    CellStyle(ValoraInsertar);
                }
                else if((i==1 && j>1)||(j==1 && i>1))
                {
                    CellStyleComponente(ValoraInsertar);
                }
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
            else
            {
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }

         }
    }
}

/**
    @brief Función que permite obtener las cuentas de la parte endogena
    @date 10/09/2015
    @author Rodrigo Boet
*/
QStringList MainWindow::obtenerCuentas()
{
    QStringList cuenta;
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int count = tw->rowCount();
    for(int i=2;i<count-1;i++)
    {
        QString valor = tw->item(0,i)->text();
        if(!cuenta.contains(valor))
        {
            cuenta.append(valor);
        }
    }
    return cuenta;
}

//FH_001
/*          Aqui empiezan las funciones de la barra herramientas*/

/**
    @brief Función que permite calcular el coeficiente técnico vertical
    @date 10/05/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCoeficienteVertical()
{
    FormCargando *cargando = new FormCargando(this);
    cargando->show();
    actionCV.setDisabled(true);
    tabWidget->addTab(new QWidget,"CT_Vertical");
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");

    QTableWidget *CT_VerticalTW = new QTableWidget;
    int count=tw->rowCount();
    CrearTablaVacia(count,CT_VerticalTW);//Se crea una tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(CT_VerticalTW);
    /*****      Se llena la tabla vacia con los valores de la tabla principal ****/
    CalcularAn(tw,CT_VerticalTW,new QTableWidget,count);//Funcion para calcular el Coeficiente Tecnico Horizontal (An)


    insertremoveRowCol(CT_VerticalTW,0,true);
    insertremoveRowCol(CT_VerticalTW,0,false);
    setAccountTitle(CT_VerticalTW);
    int indice=ObtenerIndice("CT_Vertical");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(CT_VerticalTW);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
    tabWidget->setCurrentIndex(indice);
    QTimer::singleShot(1000,cargando,SLOT(hide()));
}

/**
    @brief Función que permite calcular el coeficiente técnico horizontal
    @date 11/05/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCoeficienteHorizontal()
{
    FormCargando *cargando = new FormCargando(this);
    cargando->show();
    actionCH.setDisabled(true);
    tabWidget->addTab(new QWidget,"CT_Horizontal");
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");

    /*      Se eliminan la fila y columna (0,0) para los calculos*/
    insertremoveRowCol(tw,0,false);

    int count=tw->rowCount();
    QTableWidget *CT_HorizontalTW = new QTableWidget;
    CrearTablaVacia(count,CT_HorizontalTW); //Se Crea la tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(CT_HorizontalTW);
    /*****      Se llena la tabla vacia con los valores de la tabla principal ****/
    for(int i=0;i<count-1;i++)
    {
        //Se obtiene el total de esa columna
        double total = PrincipalTable(i,count-3);
        for(int j=0;j<count-1;j++)
        {
            if(i!=0 && j!=0)
            {
                double valor = PrincipalTable(i-1,j-1);
                if(total==0)//Se comprueba en caso de que el total sea zero
                {
                    valor=0;
                }
                else
                {
                    valor/=total;//Se divide el valor de la celda entre el total correspondiente
                }
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',precission));
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                QString value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                CT_HorizontalTW->setItem(i,j,ValoraInsertar);
            }
            /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
            else if((i==0 && j>0)||(j==0 && i>0))
            {
                QString value=tw->item(j,i)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                CellStyleComponente(ValoraInsertar);
                CT_HorizontalTW->setItem(j,i,ValoraInsertar);
            }

         }
    }
    /*      Se agrega la columna y fila (0,0) y se insertan los titulos de las cuentas      */
    insertremoveRowCol(tw,0,true);
    insertremoveRowCol(CT_HorizontalTW,0,true);
    setAccountTitle(tw);
    setAccountTitle(CT_HorizontalTW);

    int indice=ObtenerIndice("CT_Horizontal");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(CT_HorizontalTW);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
    tabWidget->setCurrentIndex(indice);
    QTimer::singleShot(1000,cargando,SLOT(hide()));
}

//FH_002
/**
    @brief Función que permite mostrar el formulario para seleccionar las cuentas exógenas
    @date 10/09/2015
    @author Rodrigo Boet
*/
void MainWindow::slotVariableExogena()
{
    if(opcionVentanaExogena==0)
    {
        formVariablesExogenas = new FormVariablesExogenas(this);
        QHBoxLayout * layoutLateralWidget = new QHBoxLayout;
        QVBoxLayout * layoutCentralWidget = new QVBoxLayout;
        QHBoxLayout * layoutAccounts = new QHBoxLayout;
        QHBoxLayout * labels = new QHBoxLayout;
        QLabel *label1 = new QLabel;
        QLabel *label2 = new QLabel;
        label1->setText("Cuentas");
        label2->setText("Componentes");
        labels->addWidget(label1);
        labels->addWidget(label2);
        QWidget *nw = new QWidget;
        nw->setLayout(labels);
        QGroupBox * groupBoxAccount = new QGroupBox;
        layoutCentralWidget->addWidget(nw);
        /***        Se obtiene la cantidad de cuentas       ***/
        StackWidget *sw = findChild<StackWidget *>("");
        int cantidad=sw->comboAccount->count();
        QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
        /***        Se obtiene el nombre de las cuentas,sus componentes, su inicio y su fin en varias listas        ***/
        insertremoveRowCol(tw,0,false);
        QStringList Lista = ObtenerNombreCuenta(cantidad);
        QStringList Componentes = ObtenerComponentes(tw);
        QList <int> inicio = ObtenerLimitesCuenta(cantidad,0);
        QList <int> fin = ObtenerLimitesCuenta(cantidad,1);
        layoutAccounts->addWidget(stackVE=new stackVariablesExogenas(Lista,Componentes,inicio,fin,groupBoxAccount,cantidad));
        insertremoveRowCol(tw,0,true);
        setAccountTitle(tw);

        groupBoxAccount->setObjectName("exogenasBoxAccount");//Se le asigna nombre al objeto
        groupBoxAccount->setLayout(layoutAccounts);;
        groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                         "border-radius: 3px; margin-top: 0.5em;} "
                         "QGroupBox::title { subcontrol-origin: margin; "
                         "left: 10px; padding: 0 3px 0 3px; } ");


        layoutLateralWidget->addWidget(groupBoxAccount);

        /***        Se crean y personalizan los bottones para agregar, finalizar, deshacer y cancelar    ***/
        QPushButton * buttonAgregar = new QPushButton;
        buttonAgregar->setObjectName("AgregarExogena");//Se le asigna nombre al objeto
        buttonAgregar->setText("A&gregar");
        buttonAgregar->setFixedWidth(130);
        buttonAgregar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonCancelar = new QPushButton;
        buttonCancelar->setObjectName("CancelarExogena");//Se le asigna nombre al objeto
        buttonCancelar->setText("&Cancelar");
        buttonCancelar->setFixedWidth(130);
        buttonCancelar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonFinalizar = new QPushButton;
        buttonFinalizar->setObjectName("FinalizarExogena");//Se le asigna nombre al objeto
        buttonFinalizar->setText("&Finalizar");
        buttonFinalizar->setFixedWidth(130);
        buttonFinalizar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonDeshacer = new QPushButton;
        buttonDeshacer->setObjectName("DeshacerExogena");//Se le asigna nombre al objeto
        buttonDeshacer->setText("&Deshacer");
        buttonDeshacer->setFixedWidth(130);
        buttonDeshacer->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");

        connect(buttonCancelar,SIGNAL(clicked()),this,SLOT(slotCloseExogena()));
        connect(buttonAgregar,SIGNAL(clicked()),this,SLOT(slotAgregarExogena()));
        connect(buttonFinalizar,SIGNAL(clicked()),this,SLOT(slotFinalizarExogena()));
        connect(buttonDeshacer,SIGNAL(clicked()),this,SLOT(slotDeshacerExogena()));


        QHBoxLayout * layoutsButtons = new QHBoxLayout;
        layoutsButtons->addWidget(buttonFinalizar);
        layoutsButtons->addWidget(buttonAgregar);
        layoutsButtons->addWidget(buttonDeshacer);
        layoutsButtons->addWidget(buttonCancelar);
        QWidget *buttonWidget = new QWidget;
        buttonWidget->setLayout(layoutsButtons);

        QWidget *widget = new QWidget;
        widget->setLayout(layoutLateralWidget);
        layoutCentralWidget->addWidget(widget);
        layoutCentralWidget->addWidget(buttonWidget);//Se agregan los botones
        formVariablesExogenas->setLayout(layoutCentralWidget);
        formVariablesExogenas->show();
        opcionVentanaExogena=1;
    }
    else
    {
        formVariablesExogenas->show();
    }
}

/**
    @brief Función que permite cerrar el formulario de selección de cuentas exógenas
    @date 10/07/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCloseExogena()
{
    formVariablesExogenas->close();
}


/**
    @brief Función que permite deshacer la selección de cuentas el formulario de selección de cuentas exógenas
    @date 14/07/2015
    @author Rodrigo Boet
*/
void MainWindow::slotDeshacerExogena()
{
    QMessageBox msBox(QMessageBox::Question,"Deshacer","¿Desea deshacer todos los cambios?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        int cantidad=stackVE->comboAccount->count();
        /*   Se habilitan todas cuentas   */
        for(int i=0;i<cantidad;i++)
        {
            QListWidget *lw=new QListWidget;
            lw= stackVE->veWidget->accounListWidget;
            lw = findChild<QListWidget *>(QString("accountlist %1").arg(i + 1));
            lw->setEnabled(true);
        }
        diccCuentasExogenas.clear();//Se limpia el diccionario
    }
}

/**
    @brief Función que permite agregar la selección de cuentas el formulario de selección de cuentas exógenas
    @date 18/07/2015
    @author Rodrigo Boet
*/
void MainWindow::slotAgregarExogena()
{
    actionVariableExogena.setDisabled(true);//Se deshabilita la opcion de agregar variables exogenas
    QString nombre_cuenta=stackVE->comboAccount->currentText();//Se obtiene el nombre de la cuenta seleccionado
    QListWidget *lw=new QListWidget;
    int index=stackVE->comboAccount->currentIndex();//Se obtiene el indice selecionado
    lw = findChild<QListWidget *>(QString("accountlist %1").arg(index + 1));//Se obtiene la lista seleccionada
    QStringList componentes_cuenta;
    if(!lw->isEnabled())
    {
        QMessageBox::warning(this,"Alerta","La Cuenta Actual ya fue Agregada");
    }
    else if(lw->selectedItems().count()==0)
    {
        QMessageBox::warning(this,"Alerta",
                             "Para Agregar la Cuenta debe seleccionar \n al menos un valor");
    }
    else
    {
        int contar=lw->selectedItems().count();
        for(int i=0;i<contar;i++)
        {
            componentes_cuenta.append(lw->selectedItems().value(i)->text());
        }
        lw->setDisabled(true);
        diccCuentasExogenas.insert(nombre_cuenta,componentes_cuenta);
        if(opcionCuentaExogena == 0)
        {
            opcionCuentaExogena=1;
        }
    }
}

/**
    @brief Función que permite finalizar la selección de cuentas el formulario de selección de cuentas exógenas
    @date 20/07/2015
    @author Rodrigo Boet
*/
void MainWindow::slotFinalizarExogena()
{
    formVariablesExogenas->close();
    FormCargando *cargando = new FormCargando(this);
    cargando->show();
    QTableWidget *tablaEE = new QTableWidget;
    tablaEE->setObjectName("MatrizExogenaEndogena");
    QTableWidget *tablaPPAL = findChild<QTableWidget *>("TablaPrincipal");//Se carga la tabla principal
    int count=tablaPPAL->rowCount();
    CrearTablaVacia(count,tablaEE);//Se crea la tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tablaEE);
    if(opcionCuentaExogena==1)//Si seleccionaron componentes
    {
        int elementos = contarElementosMap(diccCuentasExogenas);
        /*****      Se llena la tabla vacia con los valores de la tabla principal ****/
        for(int i=0;i<count-1;i++)
        {
            for(int j=0;j<count-1;j++)
            {
                if(i>=2 && j>=2)
                {
                    QString value;
                    double valor=PrincipalTable(i-2,j-2);
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',precission));
                    value = Separador(ValoraInsertar,false);
                    ValoraInsertar->setText(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }
                /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
                else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
                {
                    QString value=tablaPPAL->item(i,j)->text();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    if((i==0 && j>1)||(j==0 && i>1))
                    {
                        CellStyle(ValoraInsertar);
                    }
                    else if((i==1 && j>1)||(j==1 && i>1))
                    {
                        CellStyleComponente(ValoraInsertar);
                    }
                    tablaEE->setItem(i,j,ValoraInsertar);
                }
                else
                {
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }

             }
        }
        /***                    Se acomodan los componentes de las cuentas exogenas                 ***/
        int cantidad = tablaEE->rowCount()-elementos;
        foreach(QString key,diccCuentasExogenas.keys())
        {
            foreach(QString key2,diccCuentasExogenas[key])
            {
                for(int i=2;i<=cantidad;i++)
                {
                    QString cuenta=tablaEE->item(0,i)->text();
                    QString componente =tablaEE->item(1,i)->text();
                    if(key==cuenta and key2==componente)
                    {
                        int position = cantidad+elementos-1;
                        QList<QString> fila;
                        fila=llenarLista(fila,tablaEE,i,1);
                        tablaEE->removeRow(i);
                        tablaEE->insertRow(tablaEE->rowCount());
                        insertRowExogena(fila,tablaEE,1);
                        fila.clear();
                        //Se agregan los estilos correspondientes a las cuentas y componentes de las filas
                        QString nombre_cuenta = tablaEE->item(position,0)->text();
                        QTableWidgetItem *ValoraInsertarCuentaF = new QTableWidgetItem(nombre_cuenta);
                        CellStyle(ValoraInsertarCuentaF);
                        tablaEE->setItem(position,0,ValoraInsertarCuentaF);
                        QString nombre_componente = tablaEE->item(position,1)->text();
                        QTableWidgetItem *ValoraInsertarComponenteF = new QTableWidgetItem(nombre_componente);
                        CellStyleComponente(ValoraInsertarComponenteF);
                        tablaEE->setItem(position,1,ValoraInsertarComponenteF);


                        QList<QString> columna;
                        columna=llenarLista(columna,tablaEE,i,0);
                        tablaEE->removeColumn(i);
                        tablaEE->insertColumn(tablaEE->columnCount());
                        insertRowExogena(columna,tablaEE,0);
                        columna.clear();
                        //Se agregan los estilos correspondientes a las cuentas y componentes de las columnas
                        QTableWidgetItem *ValoraInsertarCuentaC = new QTableWidgetItem(nombre_cuenta);
                        CellStyle(ValoraInsertarCuentaC);
                        tablaEE->setItem(0,position,ValoraInsertarCuentaC);
                        QTableWidgetItem *ValoraInsertarComponenteC = new QTableWidgetItem(nombre_componente);
                        CellStyleComponente(ValoraInsertarComponenteC);
                        tablaEE->setItem(1,position,ValoraInsertarComponenteC);
                    }
                }
            }
        }

        int inicioExogena=count-elementos;

        QTableWidget *matrizEndogena = new QTableWidget;
        matrizEndogena->setObjectName("MatrizEndogenaEndogena");
        CrearTablaVacia(inicioExogena,matrizEndogena);
        noEditColZero(matrizEndogena);

        //Se crean los vectores para los subtotales endógeno/exógeno
        calcularSubtotal(tablaEE,2,count-1,inicioExogena-1);

        bool var = false;
        clonarTabla(tablaEE,matrizEndogena,inicioExogena);
        CalcularTotales(matrizEndogena,2,var);

        TotalPrincipalTable(tablaEE,EndogenasyExogenas,2);
        CalcularTotales(tablaEE,2,var);
        setEndogenaExogenaCell(tablaEE,inicioExogena,elementos,true);

        //Se crea la nueva pestaña
        createTab("Tipo de Variable",tablaEE);
        int indice=ObtenerIndice("Tipo de Variable");

        /*                  Se crea la pestaña endogena-endogena            */
        createTab("Endogena-Endogena",matrizEndogena);

        calcularTotalCuentas(tablaEE);

        crearDiccionario(tablaEE);
        crearDiccionario(tablaEE,false);
        //Se juntan y alinean las cuentas
        spanEndogenaCell(tablaEE,3,1);
        spanExogenaCell(tablaEE,1);
        spanEndogenaCell(matrizEndogena,2,0,false);

        obtenerCuentaComponentes();//Se guardan las cuentas/componentes

        //Encadenamientos
        EndogenaAn();
        slotMa();
        connect(&actionEncadenamiento,SIGNAL(triggered()),this,SLOT(slotEncadenamientos()));
        actionEncadenamiento.setEnabled(true);

        //Se activa la descomposicion
        connect(&actionDescomposicion,SIGNAL(triggered()),this,SLOT(slotDescomposicion()));
        actionDescomposicion.setEnabled(true);

        //Se activa la opción de modelo clásico
        Modelos.setEnabled(true);
        actionModeloClasico.setEnabled(true);
        connect(&actionModeloClasico,SIGNAL(triggered()),this,SLOT(slotModeloClasico()));
        //Se activa la opción para el modelo no clásico
        actionModeloNoClasico.setEnabled(true);
        connect(&actionModeloNoClasico,SIGNAL(triggered()),this,SLOT(slotModeloNoClasico()));
        //Se activa la opcion para los modelos de precios homogeneos clásico
        PHClasico.setEnabled(true);
        actionPHClasicoIncidencia100.setEnabled(true);
        connect(&actionPHClasicoIncidencia100,SIGNAL(triggered()),this,SLOT(slotPHCIncidencia100()));
        PHClasicoIncidencia.setEnabled(true);
        actionPHCIncidenciaCuenta.setEnabled(true);
        connect(&actionPHCIncidenciaCuenta,SIGNAL(triggered()),this,SLOT(slotPHCIncidenciaiCuenta()));
        actionPHCIncidenciaComponente.setEnabled(true);
        connect(&actionPHCIncidenciaComponente,SIGNAL(triggered()),this,SLOT(slotPHCIncidenciaiComponente()));
        //Se activa la opcion para los modelos de precios homogeneos no clásico
        PHNoClasico.setEnabled(true);
        actionPHNoClasicoIncidencia100.setEnabled(true);
        connect(&actionPHNoClasicoIncidencia100,SIGNAL(triggered()),this,SLOT(slotPHNCIncidencia100()));
        PHNoClasicoIncidencia.setEnabled(true);
        actionPHNCIncidenciaCuenta.setEnabled(true);
        connect(&actionPHNCIncidenciaCuenta,SIGNAL(triggered()),this,SLOT(slotPHNCIncidenciaiCuenta()));
        actionPHNCIncidenciaComponente.setEnabled(true);
        connect(&actionPHNCIncidenciaComponente,SIGNAL(triggered()),this,SLOT(slotPHNCIncidenciaiComponente()));
        //Se activa la opcion para los modelos de precios no homogéneos
        PreciosNH.setEnabled(true);
        actionPNHIncidencia100.setEnabled(true);
        connect(&actionPNHIncidencia100,SIGNAL(triggered()),this,SLOT(slotPNHIncudencia100()));
        PreciosNHIncidencia.setEnabled(true);
        actionPNHIncidenciaCuenta.setEnabled(true);
        connect(&actionPNHIncidenciaCuenta,SIGNAL(triggered()),this,SLOT(slotPNHIncidenciaiCuenta()));
        actionPNHIncidenciaComponente.setEnabled(true);
        connect(&actionPNHIncidenciaComponente,SIGNAL(triggered()),this,SLOT(slotPNHIncidenciaiComponente()));

        tabWidget->setCurrentIndex(indice);
        QTimer::singleShot(1000,cargando,SLOT(hide()));
    }
    else
    {
        QMessageBox::warning(this,"Alerta","No Agregó ninguna cuenta");
    }
}

//FH_003
/**
    @brief Función que permite calcular el coeficiente tecnico vertical de la matriz endogena/exogena
    @date 05/07/2015
    @author Rodrigo Boet
*/
void MainWindow::EndogenaAn()
{
    tabWidget->addTab(new QWidget,"An");
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    QTableWidget *to = findChild<QTableWidget *>("MatrizExogenaEndogena");
    QTableWidget *tablaAn = new QTableWidget;
    tablaAn->setObjectName("MatrizAn");
    int count=tw->rowCount();
    CrearTablaVacia(count,tablaAn);//Se crea una tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tablaAn);

    insertremoveRowCol(to,0, false);
    CalcularAn(tw,tablaAn,to,count,true);//Funcion para calcular el Coeficiente Tecnico Horizontal (An)
    //Función para calcular los totales de matriz An
    estimarVIFVC();
    /*          Se colocan los titulos de cuenta endogena/exogena en la tabla endogena-exogena(Tipo de Variable)*/
    count=to->rowCount()-1;
    int elementos = contarElementosMap(diccCuentasExogenas);
    int inicioExogena=count-elementos;
    setEndogenaExogenaCell(to,inicioExogena+1,elementos,true);
    int indice=ObtenerIndice("An");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tablaAn);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
    spanEndogenaCell(tablaAn,2,0,false);//Se juntan los espacios de las cuentas
    //tabWidget->removeTab(indice);
}

/**
    @brief Función que permite habilitar la función de restar la matriz indentidad menos la matriz de coeficientes técnicos
    @date 05/07/2015
    @author Rodrigo Boet
*/
void MainWindow::slotMa()
{
    QTableWidget *tw = findChild<QTableWidget *>("MatrizAn");
    restarIdentidadAn(tw);
}

/**
    @brief Función que permite insertar, alinear y combinar las celdas con los titulos endogena/exogena
    @date 07/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la Tabla
    @param <inicioExogena> Recibe el inicio de las wxógenas
    @param <inicioExogena> Recibe la cantidad de elementos
    @param <condicion> Recibe la condicion (Verdadero si tiene cuentas endgenas y Falso en caso contrario)
*/
void MainWindow::setEndogenaExogenaCell(QTableWidget *tw,int inicioExogena,int elementos,bool condicion)
{
    tw->insertRow(0);
    tw->insertColumn(0);
    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
    tw->setItem(0,0,ValoraInsertar);
    /*      Titulos para las Cuentas exogenas   */
    QTableWidgetItem *CuentaExogenafila = new QTableWidgetItem("Cuentas Exógenas");
    CuentaExogenafila->setFlags(CuentaExogenafila->flags() ^ Qt::ItemIsEditable);
    CuentaExogenafila->setTextAlignment(Qt::AlignCenter);
    CellStyleExEn(CuentaExogenafila);
    tw->setItem(0,inicioExogena,CuentaExogenafila);
    if(elementos>1)
    {
        tw->setSpan(0,inicioExogena,1,elementos);
    }
    QTableWidgetItem *CuentaExogenaColumna = new QTableWidgetItem;
    if(elementos<12)
    {
        CuentaExogenaColumna->setText("Cuentas \nExógenas");
    }
    else
    {
        CuentaExogenaColumna->setText("C\nu\ne\nn\nt\na\ns\n\nE\nx\nó\ng\ne\nn\na\ns");
    }
    CuentaExogenaColumna->setFlags(CuentaExogenaColumna->flags() ^ Qt::ItemIsEditable);
    CellStyleExEn(CuentaExogenaColumna);
    tw->setItem(inicioExogena,0,CuentaExogenaColumna);
    if(elementos>1)
    {
        tw->setSpan(inicioExogena,0,elementos,1);
    }
    int count = tw->rowCount();
    ItemsNoEditable(tw,count-1,count);
    tableItem(tw,inicioExogena+1,count-1,"Cuentas Exógenas");

    if(condicion)//Si tiene cuentas endogenas
    {
        /*      Titulos para las Cuentas endogenas   */
        QTableWidgetItem *CuentaEndogenafila = new QTableWidgetItem("Cuentas Endógenas");
        CuentaEndogenafila->setFlags(CuentaEndogenafila->flags() ^ Qt::ItemIsEditable);
        CuentaEndogenafila->setTextAlignment(Qt::AlignCenter);
        CellStyleExEn(CuentaEndogenafila);
        tw->setItem(0,1,CuentaEndogenafila);
        tw->setSpan(0,1,1,inicioExogena-1);
        QTableWidgetItem *CuentaEndogenaColumna = new QTableWidgetItem;
        if(elementos<12)
        {
            CuentaEndogenaColumna->setText("Cuentas \nEndógenas");
        }
        else
        {
            CuentaEndogenaColumna->setText("C\nu\ne\nn\nt\na\ns\n\nE\nn\nd\nó\ng\ne\nn\na\ns");
        }
        CuentaEndogenaColumna->setFlags(CuentaEndogenaColumna->flags() ^ Qt::ItemIsEditable);
        CellStyleExEn(CuentaEndogenaColumna);
        tw->setItem(1,0,CuentaEndogenaColumna);
        if((inicioExogena-1)>1)
        {
            tw->setSpan(1,0,inicioExogena-1,1);
        }
        tableItem(tw,2,inicioExogena,"Cuentas Endógenas");
    }
    else
    {
        ItemsNoEditable(tw,1,2);
    }
}

/**
    @brief Función que permite determinar los Multiplicadores de Leontief
    @date 08/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::restarIdentidadAn(QTableWidget *tw)
{
    int cantidad=tw->rowCount()-1;
    MatrixXd A(cantidad-1,cantidad-1);
    MatrixXd ident = MatrixXd::Identity(cantidad-1,cantidad-1);
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            A(i,j) = ident(i,j)-An(i,j);
        }
    }

    double determinant = A.determinant();
    MatrixMa = A.inverse();
    if(determinant==0)
    {
        QMessageBox::critical(this,"Alerta","El determinante es Nulo");
        actionModeloClasico.setDisabled(true);
    }
    else
    {
        total_ma = MatrixMa.sum();
        QTableWidget *tablaMa = new QTableWidget;
        tablaMa->setObjectName("MatrizMa");
        CrearTablaVacia(cantidad,tablaMa);
        for(int i=0;i<cantidad-1;i++)
        {
            for(int j=0;j<cantidad-1;j++)
            {
                double value = MatrixMa(i,j);
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(value,'f',precission));
                QString valor = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(valor);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                tablaMa->setItem(i,j,ValoraInsertar);

             }
        }
        titleEndogena(tablaMa);
        spanEndogenaCell(tablaMa,2,0,false);
        createTab("Ma",tablaMa,true);

        opcionMa = 1;
    }
}

/**
    @brief Función que permite crear un diccionario con cuenta/cantidad de veces que se repiten para el espacio de las celdas
    @date 10/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <endogena> Recibe un booleando (Verdadero si es endogena, Falso de lo contrario)
*/
void MainWindow::crearDiccionario(QTableWidget *tw, bool endogena)
{
    QStringList CuentasE;
    if(endogena)
    {
        CuentasE=obtenerCuentasEndogenas(tw,CuentasE);
    }
    else
    {
        CuentasE=obtenerCuentasExogenas(tw,CuentasE);
    }
    QMap <int,QVector<QString> > map;
    QVector <QString> vector;
    int cantidad = CuentasE.count();
    for(int i=0;i<cantidad;i++)
    {
        if(!vector.contains(CuentasE[i]))
        {
            vector.append(CuentasE[i]);
            int count = CuentasE.count(CuentasE[i]);
            vector.append(QString::number(count));
            map.insert(i,vector);
        }
    }
    int longVector = vector.count();
    for(int j=0;j<longVector;j+=2)
    {
        QVector <QString> vec;
        vec.append(vector[j]);
        vec.append(vector[j+1]);
        if(endogena)
        {
            diccCuentasEndogenas.insert(j,vec);
        }
        else
        {
            espacioCuentasExogenas.insert(j,vec);
        }
        vec.clear();
    }
    map.clear();
}

/**
    @brief Función que permite crear una lista de las cuentas endógenas
    @date 10/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <list> Recibe la lista en la que se agregan los elementos
    @return <list> retorna la lista con los elementos
*/
QStringList MainWindow::obtenerCuentasEndogenas(QTableWidget *tw,QStringList list)
{
    int elementos = contarElementosMap(diccCuentasExogenas);
    int count=tw->rowCount()-2;
    int inicioExogena=count-elementos;

    for(int i=3;i<inicioExogena+1;i++)
    {
        list.append(tw->item(1,i)->text());
    }
    return list;
}

/**
    @brief Función que permite crear una lista de las cuentas exógenas
    @date 10/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <list> Recibe la lista en la que se agregan los elementos
    @return <list> retorna la lista con los elementos
*/
QStringList MainWindow::obtenerCuentasExogenas(QTableWidget *tw,QStringList list)
{
    int elementos = contarElementosMap(diccCuentasExogenas);
    int count=tw->rowCount()-2;
    int inicioExogena=count-elementos;

    int cantidad = tw->rowCount();
    for(int i=inicioExogena+1;i<cantidad-1;i++)
    {
        list.append(tw->item(1,i)->text());
    }
    return list;
}

/**
    @brief Función que permite crear los espacios en las celdas de las cuentas en la matriz endogena
    @date 15/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <inicio> Recibe el inicio de la tabla
    @param <celda> Recibe el número de la celda
    @param <endex> Recibe un booleano (Verdadero si la matriz es endógena/exógena, Falso en caso contrario)
*/
void MainWindow::spanEndogenaCell(QTableWidget *tw,int inicio,int celda,bool endex)
{
    int elementos = contarElementosMap(diccCuentasExogenas);
    int count=tw->rowCount()-2;
    int inicioExogena;
    if(opcionCuentaExogena==1 and endex)
    {
        inicioExogena=(count-elementos)+1;
    }
    else if(opcionCuentaExogena==1 and !endex)
    {
        inicioExogena = tw->rowCount();
    }
    foreach(int key,diccCuentasEndogenas.keys())
    {
        for(int i=inicio;i<inicioExogena;i++)
        {
            QString item=tw->item(celda,i)->text();
            if(item==diccCuentasEndogenas[key][0])
            {
                //Se centran los elementos
                QTableWidgetItem *fila = tw->item(celda,i);
                fila->setTextAlignment(Qt::AlignCenter);
                QTableWidgetItem *columna = tw->item(i,celda);
                columna->setTextAlignment(Qt::AlignCenter);
                //Se obtiene el valor del espacio
                int espacio = diccCuentasEndogenas[key][1].toInt();
                if(espacio>1)
                {
                    //Se crea el espacio de las cuentas
                    tw->setSpan(celda,i,1,espacio);//Span fila
                    tw->setSpan(i,celda,espacio,1);//Span columna
                }
                break;
            }
        }
    }
}

/**
    @brief Función que permite crear los espacios en las celdas de las cuentas en la matriz exógena
    @date 11/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <contador> Recibe el limite de la iteración
*/
void MainWindow::spanExogenaCell(QTableWidget *tw,int celda)
{
    int elementos = contarElementosMap(diccCuentasExogenas);
    int count=tw->rowCount()-1;
    int inicioExogena=count-elementos;

    foreach(int key,espacioCuentasExogenas.keys())
    {
        for(int i=inicioExogena;i<count;i++)
        {
            QString item=tw->item(celda,i)->text();
            if(item==espacioCuentasExogenas[key][0])
            {
                //Se centran los elementos
                QTableWidgetItem *fila = tw->item(celda,i);
                fila->setTextAlignment(Qt::AlignCenter);
                QTableWidgetItem *columna = tw->item(i,celda);
                columna->setTextAlignment(Qt::AlignCenter);
                //Se obtiene el valor del espacio
                int espacio = espacioCuentasExogenas[key][1].toInt();
                if(espacio>1)
                {
                    //Se crea el espacio de las cuentas
                    tw->setSpan(celda,i,1,espacio);//Span fila
                    tw->setSpan(i,celda,espacio,1);//Span columna
                }
                break;
            }
        }
    }
}

/**
    @brief Función que permite obtener un diccionario de cuentas/componentes de la matriz endógena/endógena
    @date 20/07/2015
    @author Rodrigo Boet
*/
void MainWindow::obtenerCuentaComponentes()
{
    foreach(int key,diccCuentasEndogenas.keys())
    {
        QStringList list;
        QMap<QString,QStringList>  a;
        a.insert(diccCuentasEndogenas[key][0],list);
        int clave = diccCuentasComponentes.count();
        diccCuentasComponentes.insert(clave,a);
    }
    QStringList lista;
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int count = tw->rowCount();
    foreach(int key,diccCuentasComponentes.keys())
    {
        foreach (QString name, diccCuentasComponentes[key].keys())
        {
            for(int i=2;i<count-1;i++)
            {
                QString accTitle = tw->item(i,0)->text();
                if(accTitle==name)
                {
                    lista.append(tw->item(i,1)->text());
                }
            }
            diccCuentasComponentes[key][name].append(lista);
            lista.clear();

        }
    }
    for(int i=2;i<count-1;i++)
    {
        ComponentesEndogenos.append(tw->item(i,1)->text());
    }
}


/**
    @brief Función que permite determinar los totales de la matriz end-end y end-exog
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <inicio> Recibe el inicio de la tabla
    @param <fin> Recibe el fin de la tabla
    @param <exogena> Recibe el comienzo de las cuentas exógenas
*/
void MainWindow::calcularSubtotal(QTableWidget *tw, int inicio, int fin,int exogena)
{
    for(int i=inicio;i<exogena;i++)
    {
        double valEnd = 0;
        double valEx = 0;
        for(int j=inicio;j<fin;j++)
        {
            QString item = Separador(tw->item(i,j),true);
            if(j<exogena)
            {
                valEnd += item.toDouble();
            }
            else
            {
                valEx += item.toDouble();
            }
        }
        subtotalEnd.append(valEnd);
        subtotalExog.append(valEx);
    }
}

/**
    @brief Función que permite crear un vector con el total de las cuentas
    @date 25/07/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::calcularTotalCuentas(QTableWidget *tw)
{
    int cantidad = tw->rowCount();
    for(int i = 3;i<cantidad-1;i++)
    {
        QString cuenta = tw->item(i,1)->text();
        QString value = Separador(tw->item(i,cantidad-1),true);
        if(totalCuentas.contains(cuenta))
        {
            totalCuentas[cuenta] += EndogenasyExogenas(i-3,cantidad-4);
        }
        else
        {
            totalCuentas.insert(cuenta,EndogenasyExogenas(i-3,cantidad-4));
        }
    }
    estimarVectorPonderacion();
}

/**
    @brief Función que permite calcular el vector ponderación
    @date 10/08/2015
    @author Rodrigo Boet
*/
void MainWindow::estimarVectorPonderacion()
{
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int cantidad = tw->rowCount();
    for(int i = 2;i<cantidad-1;i++)
    {
        QString cuenta = tw->item(i,0)->text();
        QString value = Separador(tw->item(i,cantidad-1),true);
        double total = value.toDouble();
        if(totalCuentas.contains(cuenta))
        {
            Vpond.append(total/totalCuentas[cuenta]);
        }
    }
}


//FH_004
/**
    @brief Función que permite crear la ventana de los encadenamientos
    @date 01/08/2015
    @author Rodrigo Boet
*/
void MainWindow::slotEncadenamientos()
{
    if(opcionEncadenamientos == 0)
    {
        formEncadenamientos = new FormEncadenamientos(this);
        QHBoxLayout * layoutLateralWidget = new QHBoxLayout;
        QVBoxLayout * layoutCentralWidget = new QVBoxLayout;
        QHBoxLayout * layoutAccounts = new QHBoxLayout;
        QHBoxLayout * labels = new QHBoxLayout;
        QLabel *label = new QLabel;
        label->setText("Encadenamiento por: ");
        labels->addWidget(label);
        QWidget *nw = new QWidget;
        nw->setLayout(labels);
        QGroupBox * groupBoxAccount = new QGroupBox;
        layoutCentralWidget->addWidget(nw);
        /***        Se obtiene el nombre de las cuentas,sus componentes, su inicio y su fin en varias listas        ***/
        layoutAccounts->addWidget(stackEncadenamiento=new stackEncadenamientos(diccCuentasComponentes,groupBoxAccount));


        groupBoxAccount->setObjectName("encadenamientoBoxAcc");//Se le asigna nombre al objeto
        groupBoxAccount->setLayout(layoutAccounts);;
        groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                         "border-radius: 3px; margin-top: 0.5em;} "
                         "QGroupBox::title { subcontrol-origin: margin; "
                         "left: 10px; padding: 0 3px 0 3px; } ");


        layoutLateralWidget->addWidget(groupBoxAccount);

        /*          Se crea el layout necesario para las etiqueta y radio button            */

        QVBoxLayout *labelBox = new QVBoxLayout;
        //Etiqueta
        QLabel *label2 = new QLabel;
        label2->setText("Ver Encadenamiento por medio de: ");
        labelBox->addWidget(label2);
        QWidget *label2Widget = new QWidget;
        label2Widget->setLayout(labelBox);

        QHBoxLayout *radioBox = new QHBoxLayout;
        //Radio Button
        QRadioButton *ct = new QRadioButton;
        ct->setObjectName("CTButton");
        QRadioButton *ma = new QRadioButton;
        ma->setObjectName("MaButton");
        ct->setText("Coeficientes Técnicos");
        ma->setText("Multiplicadores Leontief");
        radioBox->addWidget(ct);
        radioBox->addWidget(ma);
        QGroupBox * groupRadio = new QGroupBox;
        groupRadio->setLayout(radioBox);
        groupRadio->setStyleSheet("QGroupBox {border: 1px solid gray; "
                                  "border-radius: 3px; margin-top: 0.5em;} "
                                  "QGroupBox::title { subcontrol-origin: margin; "
                                  "left: 10px; padding: 0 3px 0 3px; } ");

        /***        Se crean y personalizan los bottones para agregar, finalizar, deshacer y cancelar    ***/
        QPushButton * buttonAgregar = new QPushButton;
        buttonAgregar->setObjectName("AgregarEncadenamiento");//Se le asigna nombre al objeto
        buttonAgregar->setText("A&gregar");
        buttonAgregar->setFixedWidth(130);
        buttonAgregar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonCancelar = new QPushButton;
        buttonCancelar->setObjectName("CancelarEncadenamiento");//Se le asigna nombre al objeto
        buttonCancelar->setText("&Cancelar");
        buttonCancelar->setFixedWidth(130);
        buttonCancelar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonVer = new QPushButton;
        buttonVer->setObjectName("VerEncadenamiento");//Se le asigna nombre al objeto
        buttonVer->setText("V&er");
        buttonVer->setFixedWidth(130);
        buttonVer->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");

        connect(buttonCancelar,SIGNAL(clicked()),this,SLOT(slotCloseEncadenamiento()));
        connect(buttonAgregar,SIGNAL(clicked()),this,SLOT(slotAgregarEncadenamiento()));
        connect(buttonVer,SIGNAL(clicked()),this,SLOT(slotVerEncadenamiento()));

        QHBoxLayout * layoutsButtons = new QHBoxLayout;
        layoutsButtons->addWidget(buttonVer);
        layoutsButtons->addWidget(buttonAgregar);
        layoutsButtons->addWidget(buttonCancelar);
        QWidget *buttonWidget = new QWidget;
        buttonWidget->setLayout(layoutsButtons);

        QWidget *widget = new QWidget;
        widget->setLayout(layoutLateralWidget);
        layoutCentralWidget->addWidget(widget);
        layoutCentralWidget->addWidget(label2Widget);
        layoutCentralWidget->addWidget(groupRadio);
        layoutCentralWidget->addWidget(buttonWidget);//Se agregan los botones
        formEncadenamientos->setLayout(layoutCentralWidget);
        formEncadenamientos->show();
        opcionEncadenamientos = 1;
    }
    else
    {
        formEncadenamientos->show();
    }
}

/**
    @brief Función que permite cerrar la ventana de los encadenamientos
    @date 01/08/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCloseEncadenamiento()
{
    formEncadenamientos->close();
}

/**
    @brief Función que permite agregar elementos en la ventana de los encadenamientos
    @date 01/08/2015
    @author Rodrigo Boet
*/
void MainWindow::slotAgregarEncadenamiento()
{
    QString nombre_cuenta=stackEncadenamiento->comboAccount->currentText();//Se obtiene el nombre de la cuenta seleccionado
    QListWidget *lw=new QListWidget;
    int index=stackEncadenamiento->comboAccount->currentIndex();//Se obtiene el indice selecionado
    lw = findChild<QListWidget *>(QString("encadenamientosAccList %1").arg(index + 1));//Se obtiene la lista seleccionada
    QStringList componentes_cuenta;

    if(nombre_cuenta!="Sub-Matriz Endógena-Endógena")
    {
        if(!lw->isEnabled())
        {
            QMessageBox::warning(this,"Alerta","La Cuenta Actual ya fue Agregada");
        }
        else if(lw->selectedItems().count()==0)
        {
            QMessageBox::warning(this,"Alerta",
                                 "Para Agregar la Cuenta debe seleccionar \n al menos un valor");
        }
        else
        {
            int contar=lw->selectedItems().count();
            for(int i=0;i<contar;i++)
            {
                componentes_cuenta.append(lw->selectedItems().value(i)->text());
            }
            lw->setDisabled(true);
            opcionCuentaEncadenamientos=1;//Se establece un valor para la variable de la opcion
            QMap<QString,QStringList> a;
            a.insert(nombre_cuenta,componentes_cuenta);
            int diccCount = diccCuentasEncadenamientos.count();
            diccCuentasEncadenamientos.insert(diccCount,a);
        }
    }
    else
    {
        int cantidad=stackEncadenamiento->comboAccount->count();
        for(int i=0;i<cantidad;i++)
        {
            QListWidget *lw=new QListWidget;
            lw = findChild<QListWidget *>(QString("encadenamientosAccList %1").arg(i + 1));//Se obtiene la lista seleccionada
            lw->setDisabled(true);
            opcionCuentaEncadenamientos=2;//Se establece un valor para la variable de la opcion
        }

    }

}

/**
    @brief Función que permite ver los encadenamientos
    @date 01/08/2015
    @author Rodrigo Boet
*/
void MainWindow::slotVerEncadenamiento()
{
    QRadioButton *rbCT = findChild<QRadioButton *>("CTButton");
    QRadioButton *rbMa = findChild<QRadioButton *>("MaButton");
    if(rbCT->isChecked() or rbMa->isChecked())
    {
        int opcion;
        if(rbCT->isChecked())
        {
            opcion=0;
        }
        else
        {
            opcion=1;
        }
        if(opcionCuentaEncadenamientos==1)//Opcion para encadenar por coeficientes tecnicos/multiplicadores de leontief
        {
            QTableWidget *tw;
            if(opcion==0)
            {
                 tw= findChild<QTableWidget *>("MatrizAn");
            }
            else
            {
                tw = findChild<QTableWidget *>("MatrizMa");
            }
            QTableWidget *enTable = new QTableWidget;
            crearMatrizEncadenamiento(tw,enTable);//Se llama a la funcion que realiza todo el procedimiento
            tabWidget->addTab(new QWidget,QString("Encadenamiento %1").arg(cantidadEncadenamientos));
            int indice=ObtenerIndice(QString("Encadenamiento %1").arg(cantidadEncadenamientos));//Se obtiene el indice de la pestaña
            cantidadEncadenamientos++;
            QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
            layoutCentralWidget->addWidget(enTable);
            //Se genera el panel lateral para los botones
            QVBoxLayout * layoutLateralWidget = new QVBoxLayout;
            //Se genera el boton de reporte
            QPushButton * buttonReport = new QPushButton;
            buttonReport->setText("&Reporte");
            buttonReport->setObjectName("ReportButton");
            buttonReport->setFixedWidth(100);
            buttonReport->setStyleSheet("background-color: #358ccb; color: #fff;"
                                     "font-weight: bold; height: 30px; border: none;"
                                     "border-radius: 5px; margin-top: 40px;");
            //Se genera el boton de gráfico
            QPushButton * buttonGraphic = new QPushButton;
            buttonGraphic->setText("&Gráfico");
            buttonGraphic->setObjectName("ReportButton");
            buttonGraphic->setFixedWidth(100);
            buttonGraphic->setStyleSheet("background-color: #358ccb; color: #fff;"
                                     "font-weight: bold; height: 30px; border: none;"
                                     "border-radius: 5px; margin-top: 40px;");

            //Se genera la caja de grupo que contendrá el botón
            QGroupBox * groupBoxAccount = new QGroupBox;
            groupBoxAccount->setFixedWidth(220);
            groupBoxAccount->setTitle("Operaciones");
            groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                             "border-radius: 3px; margin-top: 0.5em;} "
                             "QGroupBox::title { subcontrol-origin: margin; "
                             "left: 10px; padding: 0 3px 0 3px; } ");

            QHBoxLayout * layoutButtons = new QHBoxLayout;
            layoutButtons->addWidget(buttonReport);
            layoutButtons->addWidget(buttonGraphic);
            groupBoxAccount->setLayout(layoutButtons);
            //Se conecta el boton de reporte
            connect(buttonReport,SIGNAL(clicked()),this,SLOT(slotEncadenamientoReport()));
            connect(buttonGraphic,SIGNAL(clicked()),this,SLOT(slotEncadenamientoGraphic()));

            layoutLateralWidget->addWidget(groupBoxAccount);
            layoutCentralWidget->addLayout(layoutLateralWidget);

            QWidget *widget = tabWidget->widget(indice);
            widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
            formEncadenamientos->close();
            tabWidget->setCurrentIndex(indice);
            diccCuentasEncadenamientos.clear();

        }
        else if (opcionCuentaEncadenamientos==2)//opcion para encadenar por la matriz endogena-endogena
        {
            QTableWidget *tw;
            QTableWidget *enTable = new QTableWidget;
            if(opcion==0)
            {
                 tw= findChild<QTableWidget *>("MatrizAn");
                 crearMatrizEncadenamientoEndogena(tw,enTable,An);
            }
            else
            {
                tw = findChild<QTableWidget *>("MatrizMa");
                crearMatrizEncadenamientoEndogena(tw,enTable,MatrixMa);
            }
            tabWidget->addTab(new QWidget,QString("Encadenamiento %1").arg(cantidadEncadenamientos));
            int indice=ObtenerIndice(QString("Encadenamiento %1").arg(cantidadEncadenamientos));//Se obtiene el indice de la pestaña
            cantidadEncadenamientos++;
            QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
            layoutCentralWidget->addWidget(enTable);
            //Se genera el panel lateral para los botones
            QVBoxLayout * layoutLateralWidget = new QVBoxLayout;
            //Se genera el boton de reporte
            QPushButton * buttonReport = new QPushButton;
            buttonReport->setText("&Reporte");
            buttonReport->setObjectName("ReportButton");
            buttonReport->setFixedWidth(100);
            buttonReport->setStyleSheet("background-color: #358ccb; color: #fff;"
                                     "font-weight: bold; height: 30px; border: none;"
                                     "border-radius: 5px; margin-top: 40px;");
            //Se genera el boton de gráfico
            QPushButton * buttonGraphic = new QPushButton;
            buttonGraphic->setText("&Gráfico");
            buttonGraphic->setObjectName("ReportButton");
            buttonGraphic->setFixedWidth(100);
            buttonGraphic->setStyleSheet("background-color: #358ccb; color: #fff;"
                                     "font-weight: bold; height: 30px; border: none;"
                                     "border-radius: 5px; margin-top: 40px;");

            //Se genera la caja de grupo que contendrá el botón
            QGroupBox * groupBoxAccount = new QGroupBox;
            groupBoxAccount->setFixedWidth(220);
            groupBoxAccount->setTitle("Operaciones");
            groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                             "border-radius: 3px; margin-top: 0.5em;} "
                             "QGroupBox::title { subcontrol-origin: margin; "
                             "left: 10px; padding: 0 3px 0 3px; } ");

            QHBoxLayout * layoutButtons = new QHBoxLayout;
            layoutButtons->addWidget(buttonReport);
            layoutButtons->addWidget(buttonGraphic);
            groupBoxAccount->setLayout(layoutButtons);
            //Se conecta el boton de reporte
            connect(buttonReport,SIGNAL(clicked()),this,SLOT(slotEncadenamientoReport()));
            connect(buttonGraphic,SIGNAL(clicked()),this,SLOT(slotEncadenamientoGraphic()));

            layoutLateralWidget->addWidget(groupBoxAccount);
            layoutCentralWidget->addLayout(layoutLateralWidget);

            QWidget *widget = tabWidget->widget(indice);
            widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
            formEncadenamientos->close();
            tabWidget->setCurrentIndex(indice);
            diccCuentasEncadenamientos.clear();
        }
        else
        {
            QMessageBox::warning(this,"Alerta","No Agregó ninguna cuenta");
        }
    }
    else
    {
        QMessageBox::warning(this,"Alerta","No seleccionó ninguna matriz \npara visualizar el encadenamiento");
    }
}

/**
    @brief Función que permite crear la tabla con los encadenamientos
    @date 18/08/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <enTable> Recibe el widget de la tabla donde se colocarán los encadenamientos
*/
void MainWindow::crearMatrizEncadenamiento(QTableWidget *tw,QTableWidget *enTable)
{
    int countEndogena = tw->rowCount();
    int elementos = 0;
    foreach(int key,diccCuentasEncadenamientos.keys())
    {
        foreach(QString name,diccCuentasEncadenamientos[key].keys())
        {
            QStringList prueba = diccCuentasEncadenamientos[key][name];
            elementos += prueba.count();
        }
    }
    crearTablaVaciaEncadenamiento(elementos,enTable,7);
    int columna=0;
    foreach(int key,diccCuentasEncadenamientos.keys())
    {
        foreach(QString name,diccCuentasEncadenamientos[key].keys())
        {
            for(int j=2;j<countEndogena;j++)
            {
                QString titulo =tw->item(0,j)->text();
                QString componente = tw->item(1,j)->text();
                double sumaColumna = 0;
                double sumaFila = 0;
                if(titulo==name)
                {
                    foreach(QString valor,diccCuentasEncadenamientos[key][name])
                    {
                        if(componente==valor)
                        {
                            for(int k=2;k<countEndogena;k++)
                            {
                                double EncadenamientoAtras;
                                double EncadenamientoAdelante;
                                if(tw->objectName()=="MatrizMa")
                                {
                                    EncadenamientoAtras = MatrixMa(k-2,j-2);
                                    EncadenamientoAdelante = MatrixMa(j-2,k-2);
                                }
                                else
                                {
                                    EncadenamientoAtras = An(k-2,j-2);//Suma Columna(Encadenamiento hacia atras)
                                    EncadenamientoAdelante = An(j-2,k-2);//Suma Fila(Encadenamiento hacia adelante)
                                }
                                sumaColumna+=EncadenamientoAtras;
                                sumaFila+=EncadenamientoAdelante;
                            }
                            //Elementos del encadenamiento hacia atras
                            QTableWidgetItem *valorAtras = new QTableWidgetItem(QString::number(sumaColumna,'f',precission));
                            QString value = Separador(valorAtras,false);
                            valorAtras->setText(value);
                            valorAtras->setFlags(valorAtras->flags() ^ Qt::ItemIsEditable);
                            valorAtras->setTextAlignment(Qt::AlignCenter);
                            enTable->setItem(columna,2,valorAtras);
                            //Elementos del encadenamiento hacia adelante
                            QTableWidgetItem *valorAdelante = new QTableWidgetItem(QString::number(sumaFila,'f',precission));
                            value = Separador(valorAdelante,false);
                            valorAdelante->setText(value);
                            valorAdelante->setFlags(valorAdelante->flags() ^ Qt::ItemIsEditable);
                            valorAdelante->setTextAlignment(Qt::AlignCenter);
                            enTable->setItem(columna,3,valorAdelante);
                            //Se estiman los clasificadores
                            determinarClasificador(enTable,columna,j-2,total_ma);
                            columna++;
                        }
                    }
                }
            }
        }
    }
    //Se agregan los titulos
    enTable->insertRow(0);
    QTableWidgetItem *encAtras = new QTableWidgetItem("Encadenamiento Parcial\nhacia atrás");
    encadenamientosStyle(encAtras);
    QTableWidgetItem *encAdelante = new QTableWidgetItem("Encadenamiento Parcial\nhacia adelante");
    encadenamientosStyle(encAdelante);
    enTable->setItem(0,2,encAtras);
    enTable->setItem(0,3,encAdelante);
    //Se agregan los titulos para la clasificación de las cuentas
    QTableWidgetItem *indAdelante = new QTableWidgetItem("Indicador de Encadenamiento Parcial\nhacia adelante");
    encadenamientosStyle(indAdelante);
    QTableWidgetItem *indAtras = new QTableWidgetItem("Indicador de  Encadenamiento Parcial\nhacia atrás");
    encadenamientosStyle(indAtras);
    QTableWidgetItem *clasificacion = new QTableWidgetItem("Clasificación");
    encadenamientosStyle(clasificacion);
    enTable->setItem(0,4,indAdelante);
    enTable->setItem(0,5,indAtras);
    enTable->setItem(0,6,clasificacion);
    noEditColZero(enTable);
    //Se agregan las cuentas y sus componentes
    cuentacomponentesEncadenamiento(enTable,elementos);
    //Se agregan los totales
    calcularTotalesEncadenamientos(enTable);
    //Se colocan como no editables las celdas debajo de los clasificadores
    RowColNoEditable(enTable,4,6,enTable->rowCount()-1,true);
    //Se auto ajustan las tablas al contenido
    enTable->resizeRowsToContents();
    enTable->resizeColumnsToContents();
    //Se desbloquean las listas para proximos encadenamientos
    int count = diccCuentasComponentes.count();
    for(int i=0;i<count;i++)
    {
        QListWidget *lw=new QListWidget;
        lw = findChild<QListWidget *>(QString("encadenamientosAccList %1").arg(i + 1));
        lw->setEnabled(true);
    }
}

/**
    @brief Función que permite estimar los valores del clasificador
    @date 08/09/2016
    @author Rodrigo Boet
    @param <fila> Recibe la variable donde se almacenará la fila
    @param <columna> Recibe la variable donde se almacenará la columna
    @param <index> Recibe la ubicación del vector de donde se extraerá el valor
*/
void MainWindow::estimarClasificador(double &fila, double &columna, int index, double total)
{
    //Se buscan los botones para saber si se estimó por coeficientes técnicos o Ma
    QRadioButton *rbCT = findChild<QRadioButton *>("CTButton");
    QRadioButton *rbMa = findChild<QRadioButton *>("MaButton");
    if(rbCT->isChecked())
    {
        double total_col = sumElements(vFila);
        double total_row = sumElements(vColumna);
        if(total_col!=0)
        {
            columna = vFila.at(index)/(total_col/vFila.count());
        }
        else
        {
            columna = 0;
        }
        if(total_row!=0)
        {
            fila = vColumna.at(index)/(total_row/vColumna.count());
        }
        else
        {
            fila = 0;
        }
    }
    else if(rbMa->isChecked())
    {
        columna = (vFila.at(index)*vFila.count())/total;
        fila = (vColumna.at(index)*vColumna.count())/total;
    }
}


/**
    @brief Función que hace el trabajo de calcular y determinar los clasificadores
    @date 08/09/2016
    @author Rodrigo Boet
    @param <to> Recibe el widget de la tabla de encadenamientos
    @param <index_table> Recibe el indice de la tabla de encadenamientos
    @param <element> Recibe el indice de donde se extraerá el valor para calcular el clasificador
*/
void MainWindow::determinarClasificador(QTableWidget *tw, int index_table, int element, double total)
{
    QString value;
    //Se estima la clasificación
    double elementColumna;
    double elementFila;
    estimarClasificador(elementFila,elementColumna,element,total);
    //Elementos de la clasificación columna
    QTableWidgetItem *clasificacionColumna = new QTableWidgetItem(QString::number(elementColumna,'f',precission));
    value = Separador(clasificacionColumna,false);
    clasificacionColumna->setText(value);
    clasificacionColumna->setFlags(clasificacionColumna->flags() ^ Qt::ItemIsEditable);
    clasificacionColumna->setTextAlignment(Qt::AlignCenter);
    tw->setItem(index_table,4,clasificacionColumna);
    //Elementos de la clasificación fila
    QTableWidgetItem *clasificacionFila = new QTableWidgetItem(QString::number(elementFila,'f',precission));
    value = Separador(clasificacionFila,false);
    clasificacionFila->setText(value);
    clasificacionFila->setFlags(clasificacionFila->flags() ^ Qt::ItemIsEditable);
    clasificacionFila->setTextAlignment(Qt::AlignCenter);
    tw->setItem(index_table,5,clasificacionFila);
    QTableWidgetItem *tipo = new QTableWidgetItem;
    tipo->setFlags(tipo->flags() ^ Qt::ItemIsEditable);
    //Se determina que tipo de cuenta es
    if(elementColumna<1 and elementFila<1)
    {
        tipo->setText("Independiente");
    }
    else if(elementColumna>1 and elementFila<1)
    {
        tipo->setText("Impulsor de Economía");
    }
    else if(elementColumna<1 and elementFila>1)
    {
        tipo->setText("Base");
    }
    else if(elementColumna>1 and elementFila>1)
    {
        tipo->setText("Clave");
    }
    tw->setItem(index_table,6,tipo);
}

/**
    @brief Función que permite agregar las cuentas y componentes en la tabla de encadenamientos
    @date 19/08/2015
    @author Rodrigo Boet
    @param <to> Recibe el widget de la tabla de encadenamientos
    @param <count> Recibe el limite de la tabla
*/
void MainWindow::cuentacomponentesEncadenamiento(QTableWidget *to,int count)
{
    QStringList cuentaTitulos;
    noEditColZero(to);
    QTableWidgetItem *zero = new QTableWidgetItem;
    zero->setFlags(zero->flags() ^ Qt::ItemIsEditable);
    to->setItem(0,1,zero);
    int i=1;
    foreach(int key,diccCuentasEncadenamientos.keys())
    {
        foreach (QString name, diccCuentasEncadenamientos[key].keys())
        {
            foreach (QString Item, diccCuentasEncadenamientos[key][name])
            {
                //Se agregan cuentas y componentes
                QString accName=name;
                QTableWidgetItem *cuenta = new QTableWidgetItem(accName);
                cuenta->setFlags(cuenta->flags() ^ Qt::ItemIsEditable);
                CellStyle(cuenta);
                QTableWidgetItem *componente = new QTableWidgetItem(Item);
                componente->setFlags(componente->flags() ^ Qt::ItemIsEditable);
                CellStyleComponente(componente);
                to->setItem(i,0,cuenta);
                to->setItem(i,1,componente);
                cuentaTitulos.append(accName);
                i++;
            }
        }
    }
    for(int i=0;i<count-1;i++)
    {
        QString accName=to->item(i+1,0)->text();
        if(cuentaTitulos.contains(accName))
        {
            int contar = cuentaTitulos.count(accName);
            to->setSpan(i+1,0,contar,1);
            cuentaTitulos.removeAll(accName);
        }
        if(cuentaTitulos.isEmpty())
        {
            break;
        }
    }
}

/**
    @brief Función que crear los encadenamientos de toda la matrix endógena-endógena
    @date 28/08/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <enTable> Recibe el widget de la tabla de los encadenamientos
    @param <Matrix> Recibe la matriz de donde se sacarán los valores númericos
*/
void MainWindow::crearMatrizEncadenamientoEndogena(QTableWidget *tw,QTableWidget *enTable, Eigen::MatrixXd Matrix)
{
    int countEndogena = tw->rowCount();
    crearTablaVaciaEncadenamiento(countEndogena-2,enTable,7);
    int columna=0;
    for(int i=2;i<countEndogena;i++)
    {
        double sumaColumna = 0;
        double sumaFila = 0;
        for(int j=2;j<countEndogena;j++)
        {
            double EncadenamientoAtras = Matrix(j-2,i-2);
            sumaColumna+=EncadenamientoAtras;
            double EncadenamientoAdelante = Matrix(i-2,j-2);
            sumaFila+=EncadenamientoAdelante;
        }
        //Elementos del encadenamiento hacia atras
        QTableWidgetItem *valorAtras = new QTableWidgetItem(QString::number(sumaColumna,'f',precission));
        QString value = Separador(valorAtras,false);
        valorAtras->setText(value);
        valorAtras->setFlags(valorAtras->flags() ^ Qt::ItemIsEditable);
        valorAtras->setTextAlignment(Qt::AlignCenter);
        enTable->setItem(columna,2,valorAtras);
        //Elementos del encadenamiento hacia adelante
        QTableWidgetItem *valorAdelante = new QTableWidgetItem(QString::number(sumaFila,'f',precission));
        value = Separador(valorAdelante,false);
        valorAdelante->setText(value);
        valorAdelante->setFlags(valorAdelante->flags() ^ Qt::ItemIsEditable);
        valorAdelante->setTextAlignment(Qt::AlignCenter);
        enTable->setItem(columna,3,valorAdelante);
        //Se estiman los clasificadores
        determinarClasificador(enTable,columna,i-2,total_ma);
        columna++;
    }
    //Se agregan los titulos
    enTable->insertRow(0);
    QTableWidgetItem *encAtras = new QTableWidgetItem("Encadenamiento Parcial\nhacia atrás");
    encadenamientosStyle(encAtras);
    QTableWidgetItem *encAdelante = new QTableWidgetItem("Encadenamiento Parcial\nhacia adelante");
    encadenamientosStyle(encAdelante);
    enTable->setItem(0,2,encAtras);
    enTable->setItem(0,3,encAdelante);
    noEditColZero(enTable);
    //Se agregan los titulos para la clasificación de las cuentas
    QTableWidgetItem *indAdelante = new QTableWidgetItem("Indicador de Encadenamiento Parcial\nhacia adelante");
    encadenamientosStyle(indAdelante);
    QTableWidgetItem *indAtras = new QTableWidgetItem("Indicador de  Encadenamiento Parcial\nhacia atrás");
    encadenamientosStyle(indAtras);
    QTableWidgetItem *clasificacion = new QTableWidgetItem("Clasificación");
    encadenamientosStyle(clasificacion);
    enTable->setItem(0,4,indAdelante);
    enTable->setItem(0,5,indAtras);
    enTable->setItem(0,6,clasificacion);
    //Se agregan las cuentas y sus componentes
    cuentacomponentesResultado(enTable,countEndogena-1);
    //Se agregan los totales
    calcularTotalesEncadenamientos(enTable);
    //Se colocan como no editables las celdas debajo de los clasificadores
    RowColNoEditable(enTable,4,6,enTable->rowCount()-1,true);
    //Se auto ajustan las tablas al contenido
    enTable->resizeRowsToContents();
    enTable->resizeColumnsToContents();
    int count = diccCuentasComponentes.count();
    for(int i=0;i<count;i++)
    {
        QListWidget *lw=new QListWidget;
        lw = findChild<QListWidget *>(QString("encadenamientosAccList %1").arg(i + 1));
        lw->setEnabled(true);
    }
}

/**
    @brief Función que permite agregar y calcular los totales en la matriz de encadenamientos
    @date 28/08/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::calcularTotalesEncadenamientos(QTableWidget *tw)
{
    int count = tw->rowCount();
    QStringList accName;
    for(int i=0;i<count-1;i++)
    {
        QString cuenta = tw->item(i+1,0)->text();
        if(!accName.contains(cuenta))
        {
            accName.append(cuenta);
        }
    }
    int cantidad = accName.count();
    for(int k=0;k<cantidad;k++)
    {
        count = tw->rowCount();
        double sumaAdelante=0;
        double sumaAtras=0;
        //Se realizan los calculos
        for(int i=1;i<count;i++)
        {
            if(tw->item(i,0)->text()==accName.at(k))
            {
                QString stringAtras = Separador(tw->item(i,2),true);
                double itemAtras = stringAtras.toDouble();
                sumaAtras+=itemAtras;
                QString stringAdelante = Separador(tw->item(i,3),true);
                double itemAdelante = stringAdelante.toDouble();
                sumaAdelante+=itemAdelante;
            }
        }
        //Se inserta la fila donde iran los totales
        tw->insertRow(count);
        //Se insertan las celdas con los respectivos valores totales
        QTableWidgetItem *titulo = new QTableWidgetItem(QString("Encadenamiento Parcial %1").arg(accName.at(k)));
        encadenamientosStyle(titulo);
        tw->setItem(count,1,titulo);
        QTableWidgetItem *totalAtras = new QTableWidgetItem(QString::number(sumaAtras,'f',precission));
        QString value = Separador(totalAtras,false);
        totalAtras->setText(value);
        encadenamientosStyle(totalAtras);
        QTableWidgetItem *totalAdelante = new QTableWidgetItem(QString::number(sumaAdelante,'f',precission));
        value = Separador(totalAdelante,false);
        totalAdelante->setText(value);
        encadenamientosStyle(totalAdelante);
        tw->setItem(count,2,totalAtras);
        tw->setItem(count,3,totalAdelante);
        //Se insertan los items de la tabla
        QTableWidgetItem *zero = new QTableWidgetItem;
        zero->setFlags(zero->flags() ^ Qt::ItemIsEditable);
        tw->setItem(count,0,zero);
        QTableWidgetItem *one = new QTableWidgetItem;
        one->setFlags(one->flags() ^ Qt::ItemIsEditable);
        tw->setItem(count,4,one);
        QTableWidgetItem *two = new QTableWidgetItem;
        two->setFlags(two->flags() ^ Qt::ItemIsEditable);
        tw->setItem(count,5,two);
        QTableWidgetItem *three = new QTableWidgetItem;
        three->setFlags(three->flags() ^ Qt::ItemIsEditable);
        tw->setItem(count,6,three);
    }
}

/**
    @brief Función que calcular los vectores fila/columna usados para la clasificación de cuentas
    @date 07/09/2016
    @author Rodrigo Boet
*/
void MainWindow::estimarVIFVC()
{
    int count = An.cols();
    for(int i=0;i<count;i++)
    {
        double fila = 0;
        double columna = 0;
        for(int j=0;j<count;j++)
        {
            fila+= An(i,j);
            columna += An(j,i);
        }
        vFila.append(fila);
        vColumna.append(columna);
    }
}

/**
    @brief Función que permite abir el formulario de creación del reporte de los encadenamientos
    @date 31/08/2015
    @author Rodrigo Boet
*/
void MainWindow::slotEncadenamientoReport()
{
    FormExportReport *formularioReporte = new FormExportReport(this);
    connect(formularioReporte,SIGNAL(formAccepted(QString,bool)),this,SLOT(slotGenerarEncadenamientoReport(QString,bool)));
    formularioReporte->show();
}

/**
    @brief Función que permite abir el formulario de creación de gráficos de los encadenamientos
    @date 14/09/2016
    @author Rodrigo Boet
*/
void MainWindow::slotEncadenamientoGraphic()
{
    FormExportReport *formularioReporte = new FormExportReport(this);
    formularioReporte->setWindowTitle("Exportar Gráfico");
    formularioReporte->ui->label->setText("Guardar Gráifco");
    formularioReporte->ui->label_3->setText("Seleccione la ruta para guardar el gráfico");
    disconnect(formularioReporte->ui->ButtonCargar,SIGNAL(clicked()),formularioReporte,SLOT(slotLoad()));
    disconnect(formularioReporte->ui->ButtonGenerar,SIGNAL(clicked()),formularioReporte,SLOT(slotClicked()));
    connect(formularioReporte->ui->ButtonCargar,SIGNAL(clicked()),formularioReporte,SLOT(slotLoadGraphic()));
    connect(formularioReporte->ui->ButtonGenerar,SIGNAL(clicked()),formularioReporte,SLOT(slotClickedGraphic()));
    connect(formularioReporte,SIGNAL(formAccepted(QString,bool)),this,SLOT(slotGenerarEncadenamientoReport(QString,bool)));
    formularioReporte->show();
}

/**
    @brief Función que crear el reporte de los encadenamientos
    @date 31/08/2015
    @author Rodrigo Boet
    @param <filename> Recibe el nombre del archivo
    @param <report> recibe un booleano (true si es reporte, falso en caso contrario)
*/
void MainWindow::slotGenerarEncadenamientoReport(QString filename, bool report)
{
    int indice = tabWidget->currentIndex();
    QWidget *widget = tabWidget->widget(indice);
    QTableWidget *tw = widget->findChild<QTableWidget *>();
    int row = tw->rowCount();
    int col = tw->columnCount();
    QVector<double> x, y;
    QStringList myHtml;
    myHtml.append("<table>");
    for(int i=0;i<row;i++)
    {
        myHtml.append("<tr>");
        for(int j=0;j<col;j++)
        {
            QString item = tw->item(i,j)->text();
            QString limit = tw->item(i,0)->text();
            //Comprende las filas superiores
            if(i==0 and j>1)
            {
                myHtml.append("<td align='center' style='font-weight:bold;background-color:LightGrey;'>"+item+"</td>");
            }
            //Comprende las cuentas en la parte izquierda
            else if((i>0 and !limit.isEmpty()) and j==0)
            {
                myHtml.append("<td style='background-color:steelblue;color:white'>"+item+"</td>");
            }
            //Comprende las subcuentas en la parte izquierda
            else if((i>0 and !limit.isEmpty())and j==1)
            {
                myHtml.append("<td align='center' style='background-color:LightGrey'>"+item+"</td>");
            }
            //Comprende la última fila
            else if(i>0 and limit.isEmpty())
            {
                myHtml.append("<td align='center' style='font-weight:bold'>"+item+"</td>");
            }
            //Comprende el resto de los elementos
            else
            {
                myHtml.append("<td align='center'>"+item+"</td>");
            }
            if((i>0 and i<row-1) and (j>3 and j<col-1))
            {
                QString titem = Separador(tw->item(i,j),true);
                double valor = titem.toDouble();
                if(j==4)
                {
                    x.append(valor);
                }
                else
                {
                    y.append(valor);
                }
            }
        }
        myHtml.append("</tr>");
    }
    myHtml.append("</table>");
    //Máximos y Mínimos
    double max = 3;
    double min = -1;
    //Gráfico
    QCustomPlot *customPlot = new QCustomPlot;
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // set title of plot:
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, "Clasificación de Cuentas"));
    // give the axes some labels:
    customPlot->xAxis->setLabel("-y");
    customPlot->xAxis->setTickStep(1);
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setSubTickCount(5);
    customPlot->yAxis->setLabel("-x");
    customPlot->yAxis->setAutoTickStep(false);
    customPlot->yAxis->setTickStep(1);
    customPlot->yAxis->setSubTickCount(5);
    customPlot->xAxis2->setLabel("y");
    customPlot->xAxis2->setAutoTickStep(false);
    customPlot->xAxis2->setTickStep(1);
    customPlot->xAxis2->setSubTickCount(5);
    customPlot->yAxis2->setLabel("x");
    customPlot->yAxis2->setAutoTickStep(false);
    customPlot->yAxis2->setTickStep(1);
    customPlot->yAxis2->setSubTickCount(5);
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(min, max);
    customPlot->yAxis->setRange(min, max);
    customPlot->xAxis2->setRange(min, max);
    customPlot->yAxis2->setRange(min, max);
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    // flecha
    QCPItemStraightLine *newY = new QCPItemStraightLine(customPlot);
    customPlot->addItem(newY);
    newY->point1->setCoords(1,3);
    QCPItemStraightLine *newX = new QCPItemStraightLine(customPlot);
    customPlot->addItem(newX);
    newX->point1->setCoords(3,1);
    //Se crean los labels
    QCPItemText *claveText = new QCPItemText(customPlot);
    customPlot->addItem(claveText);
    claveText->position->setCoords(max-0.5, max-0.5);
    claveText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    claveText->setPen(QPen(Qt::black));
    claveText->setText("Clave");
    claveText->setFont(QFont(font().family(), 10));
    QCPItemText *baseText = new QCPItemText(customPlot);
    customPlot->addItem(baseText);
    baseText->position->setCoords(min+0.5, max-0.5);
    baseText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    baseText->setPen(QPen(Qt::black));
    baseText->setText("Base");
    baseText->setFont(QFont(font().family(), 10));
    QCPItemText *indepentientesText = new QCPItemText(customPlot);
    customPlot->addItem(indepentientesText);
    indepentientesText->position->setCoords(min+0.8, min+0.5);
    indepentientesText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    indepentientesText->setPen(QPen(Qt::black));
    indepentientesText->setText("Independiente");
    indepentientesText->setFont(QFont(font().family(), 10));
    QCPItemText *fuertearrastreText = new QCPItemText(customPlot);
    customPlot->addItem(fuertearrastreText);
    fuertearrastreText->position->setCoords(max-0.8, min+0.5);
    fuertearrastreText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    fuertearrastreText->setPen(QPen(Qt::black));
    fuertearrastreText->setText("Impulsor");
    fuertearrastreText->setFont(QFont(font().family(), 10));
    //Se generan los cambios en el grafico
    customPlot->replot();

    QString reportText;
    //Se evalua si es un reporte
    if(report){
        QTextDocument report;
        report.setHtml(myHtml.join(""));
        QTextCursor cursor(&report);
        QPixmap pm = customPlot->toPixmap();
        QImage img = pm.toImage();
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        cursor.insertImage(img);
        QPrinter printer( QPrinter::HighResolution );
        printer.setOutputFileName(filename);
        printer.setOutputFormat(QPrinter::PdfFormat);
        report.print(&printer);
        reportText = "Se generó con éxito el reporte\n en "+filename;
    }
    else
    {
        customPlot->savePng(filename);
        reportText = "Se generó con éxito el gráfico en "+filename;
    }
    //Mensaje de confimación
    QMessageBox::information(this,"Reporte",reportText);

    /*QPainter painter( &printer );
    int h = painter.window().height()*0.4;
    int w = h * 1.3;
    int x1 = (painter.window().width() / 2) - (w/2);
    int y1 = (painter.window().height() / 2) - (h/2);
    painter.drawPixmap(x1, y1, w, h, customPlot->toPixmap());*/

}


//FH_005
/**
    @brief Función que ejecuta la acción del botón de modelo clásico
    @date 15/09/2015
    @author Rodrigo Boet
*/
void MainWindow::slotModeloClasico()
{
    if(opcionMa == 0)
    {
        slotMa();
    }
    QHBoxLayout *layoutHorizontal = new QHBoxLayout;
    QVBoxLayout *stackLayout = new QVBoxLayout;
    QStackedWidget *Stack = new QStackedWidget;
    Stack->setObjectName(QString("StackEscenario %1").arg(cantidadEscenarios));
    Stack->setFixedWidth(150);

    QPushButton *buttonCalcular = new QPushButton;
    buttonCalcular->setText("&Calcular");
    buttonCalcular->setObjectName(QString("Calcular %1").arg(cantidadEscenarios));
    buttonCalcular->setFixedWidth(130);
    buttonCalcular->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    stackLayout->addWidget(buttonCalcular);

    QPushButton *buttonFinalizar = new QPushButton;
    buttonFinalizar->setText("&Finalizar");
    buttonFinalizar->setObjectName(QString("Finalizar %1").arg(cantidadEscenarios));
    buttonFinalizar->setDisabled(true);
    buttonFinalizar->setFixedWidth(130);
    buttonFinalizar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    stackLayout->addWidget(buttonFinalizar);
    stackLayout->addStretch(50);
    QWidget *nw = new QWidget;
    nw->setLayout(stackLayout);
    Stack->addWidget(nw);

    //Se conectan los botones
    connect(buttonCalcular,SIGNAL(clicked()),this,SLOT(calcularEscenario()));
    connect(buttonFinalizar,SIGNAL(clicked()),this,SLOT(finalizarEscenario()));

    //Se crea y se llena la tabla del modelo clásico
    QTableWidget *modeloClasico = new QTableWidget;
    modeloClasico->setObjectName(QString("TablaModeloClasico %1").arg(cantidadEscenarios));
    llenarEscenario(modeloClasico);

    tabWidget->addTab(new QWidget,QString("Escenario C %1").arg(cantidadEscenarios));
    int indice=ObtenerIndice(QString("Escenario C %1").arg(cantidadEscenarios));//Se obtiene el indice de la pestaña

    layoutHorizontal->addWidget(modeloClasico);
    layoutHorizontal->addWidget(Stack);
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addLayout(layoutHorizontal);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
    actionModeloClasico.setDisabled(true);
    tabWidget->setCurrentIndex(indice);

}


/**
    @brief Función que permite realizar las operaciones en el escenario
    @date 15/09/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <clasico> Recibe un booleano (Verdadero si para el modelo clásico, Falso en caso contrario)
*/
void MainWindow::llenarEscenario(QTableWidget *tw,bool clasico)
{
    QTableWidget *tablaEndogena = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int contador = tablaEndogena->rowCount()-2;

    crearTablaVaciaEncadenamiento(contador,tw,6);
    QFont font;
    font.setBold(true);
    QTableWidgetItem *title1 = new QTableWidgetItem("Porcentaje de\nAjuste de Políticas");
    title1->setFlags(title1->flags() ^ Qt::ItemIsEditable);
    title1->setTextAlignment(Qt::AlignCenter);
    title1->setFont(font);
    QTableWidgetItem *title2 = new QTableWidgetItem("Sub-Total\nM-Exg");
    title2->setFlags(title2->flags() ^ Qt::ItemIsEditable);
    title2->setTextAlignment(Qt::AlignCenter);
    title2->setFont(font);
    QTableWidgetItem *title3 = new QTableWidgetItem("Inyección");
    title3->setFlags(title3->flags() ^ Qt::ItemIsEditable);
    title3->setTextAlignment(Qt::AlignCenter);
    title3->setFont(font);
    QTableWidgetItem *title4 ;
    if(clasico)
    {
        title4 = new QTableWidgetItem(QString("Sub-Total\nEscenario %1").arg(cantidadEscenarios));
    }
    else
    {
        title4 = new QTableWidgetItem(QString("Sub-Total\nEscenario %1").arg(cantidadMNC));
    }
    title4->setFlags(title4->flags() ^ Qt::ItemIsEditable);
    title4->setTextAlignment(Qt::AlignCenter);
    title4->setFont(font);
    tw->setItem(0,2,title1);
    tw->setItem(0,3,title2);
    tw->setItem(0,4,title3);
    tw->setItem(0,5,title4);
    cuentacomponentesResultado(tw,contador);
    for(int i=0;i<contador;i++)
    {
        //Se colocan no editables la tercera, cuarta y quinta columna, y se llena de 0 el porcentaje
        QTableWidgetItem *porcentaje = new QTableWidgetItem(QString::number(0,'f',precission));
        porcentaje->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *mExg = new QTableWidgetItem(QString::number(subtotalExog[i],'f',precission));
        QString number = Separador (mExg,false);
        mExg->setText(number);
        mExg->setFlags(mExg->flags() ^ Qt::ItemIsEditable);
        mExg->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *inyeccion = new QTableWidgetItem;
        inyeccion->setFlags(inyeccion->flags() ^ Qt::ItemIsEditable);
        inyeccion->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *subtotal = new QTableWidgetItem;
        subtotal->setFlags(subtotal->flags() ^ Qt::ItemIsEditable);
        subtotal->setTextAlignment(Qt::AlignCenter);
        tw->setItem(i+1,2,porcentaje);
        tw->setItem(i+1,3,mExg);
        tw->setItem(i+1,4,inyeccion);
        tw->setItem(i+1,5,subtotal);
    }
    //Se auto ajustan las tablas al contenido
    tw->resizeRowsToContents();
    tw->resizeColumnsToContents();
}

/**
    @brief Función que permite calcular un escenario
    @date 18/09/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <clasico> Recibe un booleano (Verdadero si para el modelo clásico, Falso en caso contrario)
*/
void MainWindow::calcularEscenario(bool clasico)
{
    QMessageBox msBox(QMessageBox::Question,"Calcular Escenario","¿Está seguro que desea calcular?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        QTableWidget *tw = new QTableWidget;
        int count;
        if(clasico)
        {
            tw = findChild<QTableWidget *>(QString("TablaModeloClasico %1").arg(cantidadEscenarios));
            count = tw->rowCount();
        }
        else
        {
            tw = findChild<QTableWidget *>(QString("TablaModeloNoClasico %1").arg(cantidadMNC));
            count = tw->rowCount();
        }
        for(int i=1;i<count;i++)
        {
            double value = tw->item(i,2)->text().toDouble();
            value = (value*subtotalExog[i-1])/100;
            QString item;
            QTableWidgetItem *inyeccion = new QTableWidgetItem(QString::number(value,'f',precission));
            item = Separador(inyeccion,false);
            inyeccion->setText(item);
            inyeccion->setFlags(inyeccion->flags() ^ Qt::ItemIsEditable);
            inyeccion->setTextAlignment(Qt::AlignCenter);
            tw->setItem(i,4,inyeccion);
        }
        for(int i=1;i<count;i++)
        {
            QString item = Separador(tw->item(i,4),true);
            double value = item.toDouble();
            value += subtotalExog[i-1];
            QTableWidgetItem *subtotal = new QTableWidgetItem(QString::number(value,'f',precission));
            item = Separador(subtotal,false);
            subtotal->setText(item);
            subtotal->setFlags(subtotal->flags() ^ Qt::ItemIsEditable);
            subtotal->setTextAlignment(Qt::AlignCenter);
            tw->setItem(i,5,subtotal);
        }
        tw->resizeColumnsToContents();
        tw->resizeRowsToContents();
        QPushButton *buttonFinalizar;
        if(clasico)
        {
            buttonFinalizar = findChild<QPushButton *>(QString("Finalizar %1").arg(cantidadEscenarios));
        }
        else
        {
            buttonFinalizar = findChild<QPushButton *>(QString("FinalizarMNC %1").arg(cantidadMNC));
        }
        buttonFinalizar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        buttonFinalizar->setEnabled(true);
    }
}

/**
    @brief Función que permite finalizar un escenario
    @date 18/09/2015
    @author Rodrigo Boet
*/
void MainWindow::finalizarEscenario()
{
    QMessageBox msBox(QMessageBox::Question,"Finalizar Escenario","¿Está seguro que desea finalizar\ este escenario?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        QTableWidget *tw = findChild<QTableWidget *>(QString("TablaModeloClasico %1").arg(cantidadEscenarios));
        QTableWidget *resultadoEscenario = new QTableWidget;
        resultadoEscenario->setObjectName(QString("TablaResultadoEscenario %1").arg(cantidadEscenarios));
        int contador = tw->rowCount();
        crearTablaVaciaEncadenamiento(contador,resultadoEscenario);
        calcularFinEscenario(resultadoEscenario);
        //Se ajustan las columnas/filas al contenido
        resultadoEscenario->resizeColumnsToContents();
        resultadoEscenario->resizeRowsToContents();
        //Se oculta el stack
        QStackedWidget *sw = findChild<QStackedWidget *>(QString("StackEscenario %1").arg(cantidadEscenarios));
        sw->hide();

        createTab(QString("Resultado C %1").arg(cantidadEscenarios),resultadoEscenario,true);

        cantidadEscenarios++;
        actionModeloClasico.setEnabled(true);
        if(cantidadEscenarios>2)
        {
            actionCompararResultados.setEnabled(true);
            connect(&actionCompararResultados,SIGNAL(triggered()),this,SLOT(slotCompararResultados()));
        }
    }
}

/**
    @brief Función que permite realizar el cálculo al finalizar un escenario
    @date 18/09/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularFinEscenario(QTableWidget *tw)
{
    QVector<double> resultado;
    resultado= obtenerResultadoEscenario(resultado);//Llama a la funcion que retorna el resultado en un Qvector
    QFont font;
    font.setBold(true);
    //Se crean los titulos
    QTableWidgetItem *resultados = new QTableWidgetItem("Resultados");
    resultados->setFlags(resultados->flags() ^ Qt::ItemIsEditable);
    resultados->setTextAlignment(Qt::AlignCenter);
    resultados->setFont(font);
    QTableWidgetItem *variacion = new QTableWidgetItem("Variación");
    variacion->setFlags(variacion->flags() ^ Qt::ItemIsEditable);
    variacion->setTextAlignment(Qt::AlignCenter);
    variacion->setFont(font);
    tw->setItem(0,2,resultados);
    tw->setItem(0,3,variacion);
    int count = tw->rowCount();
    cuentacomponentesResultado(tw,count);
    for(int i=0;i<count;i++)
    {
        //Se agregan los valores del Ma*SubTotal
        double valor = resultado[i];
        QTableWidgetItem *res = new QTableWidgetItem(QString::number(valor,'f',precission));
        QString item = Separador(res,false);
        res->setText(item);
        res->setTextAlignment(Qt::AlignCenter);
        res->setFlags(res->flags() ^ Qt::ItemIsEditable);
        tw->setItem(i+1,2,res);
        //Se agregan los valores de variacion
        double var;
        if(subtotalEnd[i]==0)
        {
            var = 0;
        }
        else
        {
            var = ((valor/(subtotalEnd[i]+subtotalExog[i]))-1)*100;
        }
        QTableWidgetItem *vari = new QTableWidgetItem(QString::number(var,'f',precission));
        QString variItem = Separador(vari,false);
        vari->setText(QString(variItem+"%"));
        vari->setTextAlignment(Qt::AlignCenter);
        vari->setFlags(vari->flags() ^ Qt::ItemIsEditable);
        tw->setItem(i+1,3,vari);
    }
}

/**
    @brief Función que calcular el resultado de multiplicar Ma por el subtotal del escenario y lo retorna en un vector
    @date 25/09/2015
    @author Rodrigo Boet
    @param <res> Recibe el vector donde se almacenarán los resultados
    @return <res> retorna el vector con los elementos
*/
QVector<double> MainWindow::obtenerResultadoEscenario(QVector<double> res)
{
    QTableWidget *Ma = findChild<QTableWidget *>("MatrizMa");
    int cantidad = Ma->rowCount()-2;
    QTableWidget *tw = findChild<QTableWidget *>(QString("TablaModeloClasico %1").arg(cantidadEscenarios));
    VectorXd vector(cantidad);
    for(int i=0;i<cantidad;i++)
    {
        QString value = Separador(tw->item(i+1,5),true);
        vector(i)=value.toDouble();
    }
    VectorXd resultado = MatrixMa*vector;
    for(int i=0;i<cantidad;i++)
    {
        double val = resultado(i);
        res.append(val);
    }
    return res;
}

/**
    @brief Función que permite abrir el formulario de comparación de resultados
    @date 01/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCompararResultados()
{
    if(opcionFormCompararResultados == 0)
    {
        formCompararResultados = new FormCompararResultados(this);
        QStringList nombres = obtenerNombreResultadoEscenario();
        formCompararResultados->ui->resultadosListWidget->addItems(nombres);
        connect(formCompararResultados->ui->buttonVerResultados,SIGNAL(clicked()),this,SLOT(slotVerResultado()));
        opcionFormCompararResultados ++;
    }
    else
    {
        formCompararResultados->ui->resultadosListWidget->clear();
        QStringList nombres = obtenerNombreResultadoEscenario();
        formCompararResultados->ui->resultadosListWidget->addItems(nombres);
    }
    formCompararResultados->show();
}

/**
    @brief Función que permite obtener los nombres de los resultados de un escenario
    @date 02/10/2015
    @author Rodrigo Boet
    @return <nombres> retorna los nombres de los resultados del escenario
*/
QStringList MainWindow::obtenerNombreResultadoEscenario()
{
    QStringList nombres;
    for(int i=1;i<cantidadEscenarios;i++)
    {
        int indice = ObtenerIndice(QString("Resultado C %1").arg(i));
        nombres.append(tabWidget->tabText(indice));
    }
    return nombres;
}

/**
    @brief Función que permite generar el resultado de la comparación de los escenarios
    @date 05/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotVerResultado()
{
    QTableWidget *tablaComparar = new QTableWidget;
    tablaComparar->setObjectName(QString("TablaCompararResultado %1").arg(cantidadResultados));
    QTableWidget *endogena = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int contador = endogena->rowCount()-2;
    crearTablaVaciaEncadenamiento(contador,tablaComparar,2);
    cuentacomponentesResultado(tablaComparar,contador);
    int contar=formCompararResultados->ui->resultadosListWidget->selectedItems().count();
    for(int i=0;i<contar;i++)
    {
        QString text = formCompararResultados->ui->resultadosListWidget->selectedItems().value(i)->text();
        QStringList number = text.split(" ");
        text = number.at(2);
        QTableWidget *tw = findChild<QTableWidget *>(QString("TablaResultadoEscenario %1").arg(text));
        crearTablaComparar(tablaComparar,tw);
    }
    //Se agrega el nombre de los resultados
    tablaComparar->insertRow(0);
    QFont font;
    font.setBold(true);
    int j = 0;
    for(int i=0;i<contar;i++)
    {
        QString text = formCompararResultados->ui->resultadosListWidget->selectedItems().value(i)->text();
        QTableWidgetItem *item1 = new QTableWidgetItem(text);
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        item1->setFont(font);
        item1->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item2 = new QTableWidgetItem(text);
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        item2->setFont(font);
        item2->setTextAlignment(Qt::AlignCenter);
        tablaComparar->setItem(0,2+j,item1);
        j++;
        tablaComparar->setItem(0,2+j,item2);
        tablaComparar->setSpan(0,(2+j)-1,1,2);
        j++;
    }
    ItemsNoEditable(tablaComparar,0,2);

    createTab(QString("Comparacion %1").arg(cantidadResultados),tablaComparar,true);

    formCompararResultados->close();
    cantidadResultados++;
}

/**
    @brief Función que permite colocar cuenta/componentes en las tablas de modelo clasico, resultados y comparar resultados
    @date 08/10/2015
    @author Rodrigo Boet
    @param <to> Recibe el widget de la tabla
    @param <count> Recibe el limite de la tabla
    @param <clasico> Recibe un booleano (Verdadero si es para el módelo clásico, Falso en caso contrario)
*/
void MainWindow::cuentacomponentesResultado(QTableWidget *to, int count,bool clasico)
{
    QStringList cuentaTitulos;
    noEditColZero(to);
    QTableWidgetItem *zero = new QTableWidgetItem;
    zero->setFlags(zero->flags() ^ Qt::ItemIsEditable);
    to->setItem(0,1,zero);
    QTableWidget *tw = new QTableWidget;
    if(clasico)
    {
        tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    }
    else
    {
        tw = findChild<QTableWidget *>("Bn");
        count = tw->rowCount()-2;
    }
    for(int i=0;i<count;i++)
    {
        //Se agregan cuentas y componentes
        QString accName=tw->item(i+2,0)->text();
        QTableWidgetItem *cuenta = new QTableWidgetItem;
        cuenta->setFlags(cuenta->flags() ^ Qt::ItemIsEditable);
        cuenta->setText(accName);
        CellStyle(cuenta);
        QTableWidgetItem *componente = new QTableWidgetItem;
        componente->setText(tw->item(i+2,1)->text());
        componente->setFlags(componente->flags() ^ Qt::ItemIsEditable);
        CellStyleComponente(componente);
        to->setItem(i+1,0,cuenta);
        to->setItem(i+1,1,componente);
        cuentaTitulos.append(accName);
    }
    for(int i=0;i<count-1;i++)
    {
        QString accName=to->item(i+1,0)->text();
        if(cuentaTitulos.contains(accName))
        {
            int contar = cuentaTitulos.count(accName);
            to->setSpan(i+1,0,contar,1);
            cuentaTitulos.removeAll(accName);
        }
        if(cuentaTitulos.isEmpty())
        {
            break;
        }
    }
}

//FH_006
/**
    @brief Función que permite ejecutar la acción del botón del modelo no clásico
    @date 10/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotModeloNoClasico()
{
    if(opcionMa == 0)
    {
        slotMa();
    }
    obtenerMatrizExgEnd();
    actionModeloNoClasico.setDisabled(true);
}

/**
    @brief Función que permite obtener las Matriz Exógena/Endógena
    @date 12/10/2015
    @author Rodrigo Boet
*/
void MainWindow::obtenerMatrizExgEnd()
{
    if(cantidadMNC==1 or opcionMb == 0)
    {
        calcularMb();
    }

    QHBoxLayout *layoutHorizontal = new QHBoxLayout;
    QVBoxLayout *stackLayout = new QVBoxLayout;
    QStackedWidget *Stack = new QStackedWidget;
    Stack->setObjectName(QString("StackEscenarioMNC %1").arg(cantidadMNC));
    Stack->setFixedWidth(150);

    QPushButton *buttonCalcular = new QPushButton;
    buttonCalcular->setText("&Calcular");
    buttonCalcular->setObjectName(QString("CalcularMNC %1").arg(cantidadMNC));
    buttonCalcular->setFixedWidth(130);
    buttonCalcular->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    stackLayout->addWidget(buttonCalcular);

    QPushButton *buttonFinalizar = new QPushButton;
    buttonFinalizar->setText("&Finalizar");
    buttonFinalizar->setObjectName(QString("FinalizarMNC %1").arg(cantidadMNC));
    buttonFinalizar->setDisabled(true);
    buttonFinalizar->setFixedWidth(130);
    buttonFinalizar->setStyleSheet("background-color: gray; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    stackLayout->addWidget(buttonFinalizar);
    stackLayout->addStretch(50);
    QWidget *nw = new QWidget;
    nw->setLayout(stackLayout);
    Stack->addWidget(nw);

    //Se conectan los botones
    connect(buttonCalcular,SIGNAL(clicked()),this,SLOT(calcularEscenarioNC()));
    connect(buttonFinalizar,SIGNAL(clicked()),this,SLOT(finalizarEscenarioNC()));

    //Se crea y se llena la tabla del modelo clásico
    QTableWidget *modeloNoClasico = new QTableWidget;
    modeloNoClasico->setObjectName(QString("TablaModeloNoClasico %1").arg(cantidadMNC));
    llenarEscenario(modeloNoClasico,false);

    tabWidget->addTab(new QWidget,QString("Escenario NC %1").arg(cantidadMNC));
    int indice2=ObtenerIndice(QString("Escenario NC %1").arg(cantidadMNC));//Se obtiene el indice de la pestaña

    layoutHorizontal->addWidget(modeloNoClasico);
    layoutHorizontal->addWidget(Stack);
    QHBoxLayout * layoutCentralWidget2 = new QHBoxLayout;
    layoutCentralWidget2->addLayout(layoutHorizontal);
    QWidget *widget2 = tabWidget->widget(indice2);
    widget2->setLayout(layoutCentralWidget2);//Se añade el widget y layout a la pestaña creada
    tabWidget->setCurrentIndex(indice2);

}

/**
    @brief Función que permite calcular los multiplicadores de Leontief en la matriz Exógena/Endógena
    @date 14/10/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularMb()
{
    QTableWidget *MatrizEndogenaExogena = findChild<QTableWidget *>("MatrizExogenaEndogena");
    MatrizExgEnd = new QTableWidget;
    QTableWidget *Bn = new QTableWidget;
    Bn->setObjectName("Bn");
    QTableWidget *Mb = new QTableWidget;
    Mb->setObjectName("MatrizMb");
    int count=MatrizEndogenaExogena->rowCount()-1;
    int elementos = contarElementosMap(diccCuentasExogenas);
    int inicioExogena=count-elementos;
    crearTablaVaciaEncadenamiento(elementos+2,MatrizExgEnd,inicioExogena-1);
    crearTablaVaciaEncadenamiento(elementos+2,Bn,inicioExogena-1);
    crearTablaVaciaEncadenamiento(elementos+2,Mb,inicioExogena-1);

    crearMatrizExgEnd(MatrizEndogenaExogena,MatrizExgEnd,elementos,inicioExogena);
    TotalEndoExoTable(elementos,inicioExogena);
    calcularMatrizExgEnd(MatrizExgEnd);
    ctvMatrizExgEnd(MatrizExgEnd,Bn);
    titlespanMatrizExgEnd(Bn);

    createTab("Bn",Bn);
    int indice=ObtenerIndice("Bn");
    tabWidget->removeTab(indice);

    estimarMb(Bn,Mb);
    calcularSubtotalEndExg();
    opcionMb++;
}

/**
    @brief Función que permite crear la Matriz Exógena Endógena
    @date 10/10/2015
    @author Rodrigo Boet
*/
void MainWindow::crearMatrizExgEnd(QTableWidget *MatrizEndogenaExogena,QTableWidget *MatrizExgEnd,int elementos,int inicioExogena)
{
    //Crear Matriz ExgEnd
    for(int i = 0;i<elementos+2;i++)
    {
        for(int j=1;j<inicioExogena;j++)
        {
            if(i<2)
            {
                QString value = MatrizEndogenaExogena->item(i+1,j)->text();
                QTableWidgetItem *item = new QTableWidgetItem(value);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                MatrizExgEnd->setItem(i,j-1,item);
            }
            else
            {
                QString value = MatrizEndogenaExogena->item(inicioExogena+(i-2),j)->text();
                QTableWidgetItem *item = new QTableWidgetItem(value);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                MatrizExgEnd->setItem(i,j-1,item);
            }
        }
    }
}

/**
    @brief Función que almacena los valores del fragmento exogeno/endogeno la tabla Tipo de variables
    @date 22/06/2016
    @author Rodrigo Boet
    @param <elementos> Recibe como párametro la cantidad de elemntos que tiene esa sección
    @param <cantidad> Recibe como parametro el inicio de del fragmento exogeno/endogeno
*/
void MainWindow::TotalEndoExoTable(int elementos, int cantidad)
{
    ExoEndo.resize(elementos,cantidad-3);
    for(int i = 0;i<elementos;i++)
    {
        for(int j=0;j<cantidad-3;j++)
        {
            int value = (cantidad-3)+i;
            ExoEndo(i,j) = EndogenasyExogenas(value,j);
        }
    }
}

/**
    @brief Función que permite calcular los totales de la matriz Exógena-Endógena
    @date 22/06/2016
    @author Rodrigo Boet
    @param <MatrizExgEnd> Recibe como párametro el widget de la matriz Exógena-Endógena
*/
void MainWindow::calcularMatrizExgEnd(QTableWidget *MatrizExgEnd)
{
    //Calcular resultados
    int fila= MatrizExgEnd->rowCount();
    int columna = MatrizExgEnd->columnCount();
    MatrizExgEnd->insertRow(fila);
    for(int i = 2; i<columna; i++)
    {
        double total = 0;
        for(int j = 2;j<fila;j++)
        {
            QString value = Separador(MatrizExgEnd->item(j,i),true);
            double valor = value.toDouble();
            total+=valor;
        }
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(total,'f',precission));
        QString value = Separador(item,false);
        item->setText(value);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        MatrizExgEnd->setItem(fila,i,item);
    }
}

/**
    @brief Función que permite calcular los coeficientes técnicos verticales de la matriz Exógena-Endógena
    @date 18/10/2015
    @author Rodrigo Boet
    @param <MatrizExgEnd> Recibe como párametro el widget de la matriz Exógena-Endógena
    @param <Bn> Recibe como párametro el widget de la matriz Bn
*/
void MainWindow::ctvMatrizExgEnd(QTableWidget *MatrizExgEnd,QTableWidget *Bn)
{
    //Calcular CTV
    int fila = MatrizExgEnd->rowCount()-1;
    int columna = MatrizExgEnd->columnCount();
    MBn.resize(fila-2,columna-2);
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
    int totalLocal = tw->rowCount()-1;
    for(int i = 0; i<columna; i++)
    {
        double total;
        for(int j = 0;j<fila;j++)
        {
            if(i>=2 and j>=2)
            {
                total = PrincipalTable(totalLocal-2,i-2);
                double valoraInsertar;
                if(total==0)
                {
                    valoraInsertar=0;
                }
                else
                {
                    valoraInsertar = ExoEndo(j-2,i-2);
                    valoraInsertar /= total;
                }
                MBn(j-2,i-2) = valoraInsertar;
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(valoraInsertar,'f',precission));
                QString value = Separador(item,false);
                item->setText(value);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setTextAlignment(Qt::AlignCenter);
                Bn->setItem(j,i,item);
            }
            else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=MatrizExgEnd->item(j,i)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                if((i==0 && j>1)||(j==0 && i>1))
                {
                    CellStyle(ValoraInsertar);
                    ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                }
                else if((i==1 && j>1)||(j==1 && i>1))
                {
                    CellStyleComponente(ValoraInsertar);
                }
                Bn->setItem(j,i,ValoraInsertar);
            }
            /*      Se colocan no editables algunas de las celdas que estan vacias*/
            else
            {
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                Bn->setItem(j,i,ValoraInsertar);
            }
        }
    }
}

/**
    @brief Función que permite colocar los espacios de los títulos de las cuenta
    @date 15/10/2015
    @author Rodrigo Boet
    @param <Bn> Recibe el widget de la tabla
*/
void MainWindow::titlespanMatrizExgEnd(QTableWidget *Bn)
{
    int fila = Bn->rowCount();
    int columna = Bn->columnCount();
    //Span Title No Clasico
    QStringList valoresColumna;
    QStringList valoresFila;
    //Se obtienen los valores
    for(int i = 2; i<columna; i++)
    {
        QString value = Bn->item(0,i)->text();
        valoresColumna.append(value);
    }
    for(int j = 2;j<fila;j++)
    {
        QString value = Bn->item(j,0)->text();
        valoresFila.append(value);

    }

    //Se agrega el espaciado
    for(int i = 2; i<columna; i++)
    {
        QString name = Bn->item(0,i)->text();
        if(valoresColumna.contains(name))
        {
            int contar = valoresColumna.count(name);
            Bn->setSpan(0,i,1,contar);
            valoresColumna.removeAll(name);
        }
        if(valoresColumna.isEmpty())
        {
            break;
        }
    }

    for(int j = 2; j<fila; j++)
    {
        QString name = Bn->item(j,0)->text();
        if(valoresFila.contains(name))
        {
            int contar = valoresFila.count(name);
            Bn->setSpan(j,0,contar,1);
            valoresFila.removeAll(name);
        }
        if(valoresFila.isEmpty())
        {
            break;
        }
    }
}

/**
    @brief Función que permite calcular los multiplicadores de leontief para Bn
    @date 25/10/2015
    @author Rodrigo Boet
    @param <Bn> Recibe el widget de la tabla Bn
    @param <Mb> Recibe el widget de la tabla Mb
*/
void MainWindow::estimarMb(QTableWidget *Bn,QTableWidget *Mb)
{
    int fila = Bn->rowCount();
    int columna = Bn->columnCount();
    MatrixMb = MBn*MatrixMa;
    for(int i=0;i<columna;i++)
    {
        for(int j=0;j<fila;j++)
        {
            if(i>=2 and j>=2)
            {
                QString valor = QString::number(MatrixMb(j-2,i-2),'f',precission);
                QTableWidgetItem *item = new QTableWidgetItem(valor);
                QString value = Separador(item,false);
                item->setText(value);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setTextAlignment(Qt::AlignCenter);
                Mb->setItem(j,i,item);
            }
            else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=Bn->item(j,i)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                if((i==0 && j>1)||(j==0 && i>1))
                {
                    CellStyle(ValoraInsertar);
                    ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                }
                else if((i==1 && j>1)||(j==1 && i>1))
                {
                    CellStyleComponente(ValoraInsertar);
                }
                Mb->setItem(j,i,ValoraInsertar);
            }
            /*      Se colocan no editables algunas de las celdas que estan vacias*/
            else
            {
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                Mb->setItem(j,i,ValoraInsertar);
            }
        }
    }
    titlespanMatrizExgEnd(Mb);
    createTab("Mb",Mb);
}

/**
    @brief Función que permite calcular un escenario no clásico
    @date 25/10/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularEscenarioNC()
{
    calcularEscenario(false);
}

/**
    @brief Función que permite finalizar un escenario no clásico
    @date 25/10/2015
    @author Rodrigo Boet
*/
void MainWindow::finalizarEscenarioNC()
{
    QMessageBox msBox(QMessageBox::Question,"Finalizar Escenario","¿Está seguro que desea finalizar\ este escenario?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        QTableWidget *tw = findChild<QTableWidget *>("Bn");
        QTableWidget *resultadoEscenario = new QTableWidget;
        resultadoEscenario->setObjectName(QString("TablaResultadoEscenarioMNC %1").arg(cantidadMNC));
        int contador = tw->rowCount()-1;
        crearTablaVaciaEncadenamiento(contador,resultadoEscenario);
        calcularFinEscenarioMNC(resultadoEscenario);
        //Se ajustan las columnas/filas al contenido
        resultadoEscenario->resizeColumnsToContents();
        resultadoEscenario->resizeRowsToContents();
        //Se oculta el stack
        QStackedWidget *sw = findChild<QStackedWidget *>(QString("StackEscenarioMNC %1").arg(cantidadMNC));
        sw->hide();

        createTab(QString("Resultado NC %1").arg(cantidadMNC),resultadoEscenario,true);

        cantidadMNC++;
        actionModeloNoClasico.setEnabled(true);
        if(cantidadMNC>2)
        {
            actionCompararResultadosMNC.setEnabled(true);
            connect(&actionCompararResultadosMNC,SIGNAL(triggered()),this,SLOT(slotCompararResultadosMNC()));
        }
    }
}

/**
    @brief Función que calcular el resultado de multiplicar Ma por el subtotal del escenario y lo retorna en un vector
    @date 25/10/2015
    @author Rodrigo Boet
    @param <res> Recibe el vector donde se almacenarán los resultados
    @return <res> retorna el vector con los elementos
*/
QVector<double> MainWindow::obtenerResultadoEscenarioMNC(QVector<double> res)
{
    QTableWidget *Ma = findChild<QTableWidget *>("MatrizMa");
    int cantidad = Ma->rowCount()-2;
    QTableWidget *tw = findChild<QTableWidget *>(QString("TablaModeloNoClasico %1").arg(cantidadMNC));
    VectorXd vector(cantidad);
    for(int i=0;i<cantidad;i++)
    {
        QString value = Separador(tw->item(i+1,5),true);
        vector(i)=value.toDouble();
    }
    VectorXd resultado = MatrixMb*vector;
    cantidad = MatrixMb.rows();
    for(int i=0;i<cantidad;i++)
    {
        double val = resultado(i);
        res.append(val);
    }
    return res;
}

/**
    @brief Función que permite realizar el cálculo al finalizar un escenario no clásico
    @date 18/09/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularFinEscenarioMNC(QTableWidget *tw)
{
    QVector<double> resultado;
    resultado= obtenerResultadoEscenarioMNC(resultado);//Llama a la funcion que retorna el resultado en un Qvector
    QFont font;
    font.setBold(true);
    //Se crean los titulos
    QTableWidgetItem *resultados = new QTableWidgetItem("Resultados");
    resultados->setFlags(resultados->flags() ^ Qt::ItemIsEditable);
    resultados->setTextAlignment(Qt::AlignCenter);
    resultados->setFont(font);
    QTableWidgetItem *variacion = new QTableWidgetItem("Variación");
    variacion->setFlags(variacion->flags() ^ Qt::ItemIsEditable);
    variacion->setTextAlignment(Qt::AlignCenter);
    variacion->setFont(font);
    tw->setItem(0,2,resultados);
    tw->setItem(0,3,variacion);
    int count = tw->rowCount();
    cuentacomponentesResultado(tw,count,false);
    for(int i=0;i<count-1;i++)
    {
        //Se agregan los valores del Ma*SubTotal
        double valor = resultado[i];
        QTableWidgetItem *res = new QTableWidgetItem(QString::number(valor,'f',precission));
        QString item = Separador(res,false);
        res->setText(item);
        res->setTextAlignment(Qt::AlignCenter);
        res->setFlags(res->flags() ^ Qt::ItemIsEditable);
        tw->setItem(i+1,2,res);
        //Se agregan los valores de variacion
        double var;
        if(subtotalExogEnd[i]==0)
        {
            var = 0;
        }
        else
        {
            var = ((valor/subtotalExogEnd[i])-1)*100;
        }
        QTableWidgetItem *vari = new QTableWidgetItem(QString::number(var,'f',precission));
        QString variItem = Separador(vari,false);
        vari->setText(QString(variItem+"%"));
        vari->setTextAlignment(Qt::AlignCenter);
        vari->setFlags(vari->flags() ^ Qt::ItemIsEditable);
        tw->setItem(i+1,3,vari);
    }
}

/**
    @brief Función que permite calcular el subtotal de la matriz Exógena/Endógena
    @date 28/10/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularSubtotalEndExg()
{
    int fila = MatrizExgEnd->rowCount()-1;
    int columna = MatrizExgEnd->columnCount();
    for(int i=2;i<fila;i++)
    {
        double total = 0;
        for(int j=2;j<columna;j++)
        {
            QString item = Separador(MatrizExgEnd->item(i,j),true);
            total+=item.toDouble();
        }
        subtotalExogEnd.append(total);
    }
}

/**
    @brief Función que permite abrir el formulario de comparación de resultados del modelo no clásico
    @date 28/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCompararResultadosMNC()
{
    if(opcionFormCompararResultadosMNC == 0)
    {
        formCompararMNC = new FormCompararMNC(this);
        QStringList nombres = obtenerNombreResultadoEscenarioMNC();
        formCompararMNC->ui->listMNC->addItems(nombres);
        connect(formCompararMNC->ui->verMNC,SIGNAL(clicked()),this,SLOT(slotVerResultadoMNC()));
        opcionFormCompararResultadosMNC ++;
    }
    else
    {
        formCompararMNC->ui->listMNC->clear();
        QStringList nombres = obtenerNombreResultadoEscenarioMNC();
        formCompararMNC->ui->listMNC->addItems(nombres);
    }
    formCompararMNC->show();
}

/**
    @brief Función que permite obtener los nombres de los resultados de un escenario no clásico
    @date 29/10/2015
    @author Rodrigo Boet
    @return <nombres> retorna los nombres de los resultados del escenario
*/
QStringList MainWindow::obtenerNombreResultadoEscenarioMNC()
{
    QStringList nombres;
    for(int i=1;i<cantidadMNC;i++)
    {
        int indice = ObtenerIndice(QString("Resultado NC %1").arg(i));
        nombres.append(tabWidget->tabText(indice));
    }
    return nombres;
}

/**
    @brief Función que permite generar el resultado de la comparación de los escenarios no clásicos
    @date 05/10/2015
    @author Rodrigo Boet
*/
void MainWindow::slotVerResultadoMNC()
{
    QTableWidget *tablaComparar = new QTableWidget;
    tablaComparar->setObjectName(QString("TablaCompararResultadoMNC %1").arg(cantidadResultadosMNC));
    QTableWidget *Bn = findChild<QTableWidget *>("Bn");
    int contador = Bn->rowCount()-2;
    crearTablaVaciaEncadenamiento(contador,tablaComparar,2);
    cuentacomponentesResultado(tablaComparar,contador,false);
    int contar=formCompararMNC->ui->listMNC->selectedItems().count();
    for(int i=0;i<contar;i++)
    {
        QString text = formCompararMNC->ui->listMNC->selectedItems().value(i)->text();
        QStringList number = text.split(" ");
        text = number.at(2);
        QTableWidget *tw = findChild<QTableWidget *>(QString("TablaResultadoEscenarioMNC %1").arg(text));
        crearTablaComparar(tablaComparar,tw);
    }
    //Se agrega el nombre de los resultados
    tablaComparar->insertRow(0);
    QFont font;
    font.setBold(true);
    int j = 0;
    for(int i=0;i<contar;i++)
    {
        QString text = formCompararMNC->ui->listMNC->selectedItems().value(i)->text();
        QTableWidgetItem *item1 = new QTableWidgetItem(text);
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        item1->setFont(font);
        item1->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item2 = new QTableWidgetItem(text);
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        item2->setFont(font);
        item2->setTextAlignment(Qt::AlignCenter);
        tablaComparar->setItem(0,2+j,item1);
        j++;
        tablaComparar->setItem(0,2+j,item2);
        tablaComparar->setSpan(0,(2+j)-1,1,2);
        j++;
    }
    ItemsNoEditable(tablaComparar,0,2);

    createTab(QString("Comparacion MNC %1").arg(cantidadResultadosMNC),tablaComparar,true);

    formCompararMNC->close();
    cantidadResultadosMNC++;
}


//FH_007
/**
    @brief Función que permite calcular la incidencia según el modelo clásico
    @date 01/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPHCIncidencia100()
{
    if(opcionMAT == 0)
    {
        calcularMaT();
    }
    QTableWidget *MatrizMi = new QTableWidget;
    MatrizMi->setObjectName("PIHc100");
    calcularPHCIncidencia100(MatrizMi);

    createTab("PIHc100",MatrizMi,true);
    actionPHClasicoIncidencia100.setDisabled(true);
}

/**
    @brief Función que permite determinar Ma Transpuesta o Ma^T
    @date 01/11/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularMaT()
{
    if(opcionMa == 0)
    {
        slotMa();
    }
    QTableWidget *MaT = new QTableWidget;
    MaT->setObjectName("MatrizMaT");
    QTableWidget *Ma = findChild<QTableWidget *>("MatrizMa");
    int cantidad = Ma->rowCount()-2;
    CrearTablaVacia(cantidad+1,MaT);
    MatrizMat = MatrixMa.transpose();
    for(int i=0;i<cantidad;i++)
    {
        for(int j=0;j<cantidad;j++)
        {
            double value = MatrizMat(i,j);
            QString valor = QString::number(value,'f',precission);
            QTableWidgetItem *item = new QTableWidgetItem(valor);
            valor = Separador(item,false);
            item->setText(valor);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            MaT->setItem(i,j,item);
        }
    }
    titleEndogena(MaT);
    spanEndogenaCell(MaT,2,0,false);
    createTab("Pc",MaT);
    opcionMAT++;
}

/**
    @brief Función que permite calcular la incidencia al 100%
    @date 01/11/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::calcularPHCIncidencia100(QTableWidget *tw)
{
    int count = Vpond.count();
    MatrixXd Res(count,count);
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
        {
            Res(i,j)=MatrizMat(i,j) * Vpond.at(i);
        }
    }
    CrearTablaVacia(count+1,tw);
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
        {
            double value = Res(i,j);
            QString valor = QString::number(value,'f',precission);
            QTableWidgetItem *item = new QTableWidgetItem(valor);
            valor = Separador(item,false);
            item->setText(valor);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            tw->setItem(i,j,item);
        }
    }
    titleEndogena(tw);
    spanEndogenaCell(tw,2,0,false);
}

/**
    @brief Función que permite generar una tabla con las incidencias "i" por cuenta
    @date 15/09/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPHCIncidenciaiCuenta()
{
    if(opcionMAT == 0)
    {
        calcularMaT();
    }
    FI = new FormIncidenciaI(this);
    QTableWidget *tw = FI->ui->TableIncidencia;
    QStringList nombreCuenta = obtenerCuentas();
    int cuentas = nombreCuenta.count();
    crearTablaVaciaEncadenamiento(2,tw,cuentas);
    for(int i=0;i<cuentas;i++)
    {
        QTableWidgetItem *titulo = new QTableWidgetItem(nombreCuenta.at(i));
        titulo->setFlags(titulo->flags() ^ Qt::ItemIsEditable);
        titulo->setTextAlignment(Qt::AlignCenter);
        CellStyle(titulo);
        tw->setItem(0,i,titulo);
        QTableWidgetItem *number = new QTableWidgetItem(QString::number(0,'f',precission));
        number->setTextAlignment(Qt::AlignCenter);
        QString item = Separador(number,false);
        number->setText(item);
        tw->setItem(1,i,number);
    }
    connect(FI->ui->CalcularIncidencia,SIGNAL(clicked()),this,SLOT(slotCalcularPHCIncidenciaiCuenta()));
    FI->show();
}

/**
    @brief Función que permite calcular la incidencia según el modelo clásico por una cuenta seleccionada
    @date 02/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCalcularPHCIncidenciaiCuenta()
{
    QTableWidget *tw = FI->ui->TableIncidencia;
    QStringList nombreCuenta = obtenerCuentas();
    int cuentas = nombreCuenta.count();
    QMap<QString,double> cantidades;
    for(int i=0;i<cuentas;i++)
    {
        QString cuenta = tw->item(0,i)->text();
        QString value = Separador(tw->item(1,i),true);
        cantidades.insert(cuenta,value.toDouble());
    }

    QTableWidget *MatrizIC = new QTableWidget;
    MatrizIC->setObjectName(QString("PHCIcuenta %1").arg(cantidadPHCindidenciaiCuenta));
    calcularPHCIncidencia100(MatrizIC);
    calcularPHCIncidenciaI(MatrizIC,cantidades);

    createTab(QString("PIHci %1").arg(cantidadPHCindidenciaiCuenta),MatrizIC,true);
    cantidadPHCindidenciaiCuenta++;
}

/**
    @brief Función que permite calcular la incidencia "i" en los precios homogéneos clásico (cuenta)
    @date 02/11/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <inci> Recibe el diccionario con las cuentas-valor
*/
void MainWindow::calcularPHCIncidenciaI(QTableWidget *tw,QMap<QString,double> inci)
{
    int fila = tw->rowCount();
    int columna = tw->columnCount();
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<columna;j++)
        {

            QString cuenta= tw->item(i,0)->text();
            QString number = Separador(tw->item(i,j),true);
            double valor = number.toDouble();
            if(inci.contains(cuenta) and inci[cuenta]!=0)
            {
                valor = valor*(inci[cuenta]/100);
            }
            QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',precission));
            ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
            ValoraInsertar->setTextAlignment(Qt::AlignCenter);
            QString value = Separador(ValoraInsertar,false);
            tw->item(i,j)->setText(value);
        }
    }
    FI->close();
}

/**
    @brief Función que permite calcular la incidencia según el modelo clásico por un componente seleccionado
    @date 03/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPHCIncidenciaiComponente()
{
    if(opcionMAT == 0)
    {
        calcularMaT();
    }
    FI = new FormIncidenciaI(this);
    int contador = ComponentesEndogenos.count();
    QTableWidget *tw = FI->ui->TableIncidencia;
    crearTablaVaciaEncadenamiento(2,tw,contador);

    for(int i=0;i<contador;i++)
    {
        QTableWidgetItem *titulo = new QTableWidgetItem(ComponentesEndogenos.at(i));
        titulo->setFlags(titulo->flags() ^ Qt::ItemIsEditable);
        titulo->setTextAlignment(Qt::AlignCenter);
        CellStyleComponente(titulo);
        tw->setItem(0,i,titulo);
        QTableWidgetItem *number = new QTableWidgetItem(QString::number(0,'f',precission));
        number->setTextAlignment(Qt::AlignCenter);
        QString item = Separador(number,false);
        number->setText(item);
        tw->setItem(1,i,number);
    }
    connect(FI->ui->CalcularIncidencia,SIGNAL(clicked()),this,SLOT(slotCalcularPHCIncidenciaiComponente()));
    FI->show();
}

/**
    @brief Función que permite calcular la incidencia "i" según el modelo clásico por un componente seleccionado
    @date 03/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCalcularPHCIncidenciaiComponente()
{
    QTableWidget *tw = FI->ui->TableIncidencia;

    QTableWidget *MatrizIComp = new QTableWidget;
    MatrizIComp->setObjectName(QString("PHCIcomponente %1").arg(cantidadPHCindidenciaiComponente));
    calcularPHCIncidencia100(MatrizIComp);
    calcularPHCIncidenciaIComponente(MatrizIComp,tw);

    createTab(QString("PIHcic %1").arg(cantidadPHCindidenciaiComponente),MatrizIComp,true);
    cantidadPHCindidenciaiComponente++;
}

/**
    @brief Función que permite calcular la incidencia "i" en los precios homogéneos clásico (componente)
    @date 03/11/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <ot> Recibe el widget de la tabla donde se colocarán las incidencias
*/
void MainWindow::calcularPHCIncidenciaIComponente(QTableWidget *tw,QTableWidget *ot)
{
    int fila = tw->rowCount();
    int columna = tw->columnCount();
    for(int i=2;i<fila;i++)
    {
        QString incidencia = ot->item(1,i-2)->text();
        double inci = incidencia.toDouble();
        for(int j=2;j<columna;j++)
        {
            QString number = Separador(tw->item(i,j),true);
            double valor = number.toDouble();
            if(inci!=0)
            {
                valor = valor*(inci/100);
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',precission));
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                QString value = Separador(ValoraInsertar,false);
                tw->item(i,j)->setText(value);
            }
        }
    }
    FI->close();
}

/**
    @brief Función que calcular la Ma Transpuesta
    @date 04/11/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularMbT()
{
    if(opcionMa == 0)
    {
        slotMa();
    }
    if(opcionMb == 0)
    {
        calcularMb();
    }
    QTableWidget *MbT = new QTableWidget;
    MbT->setObjectName("MatrizMbT");
    QTableWidget *Mb = findChild<QTableWidget *>("MatrizMb");
    int filas = Mb->rowCount();
    int columnas = Mb->columnCount();
    crearTablaVaciaEncadenamiento(columnas,MbT,filas);
    MatrizMbt = MatrixMb.transpose();
    for(int i=0;i<columnas;i++)
    {
        for(int j=0;j<filas;j++)
        {
            if(i>=2 and j>=2)
            {
                double value = MatrizMbt(i-2,j-2);
                QString valor = QString::number(value,'f',precission);
                QTableWidgetItem *item = new QTableWidgetItem(valor);
                valor = Separador(item,false);
                item->setText(valor);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setTextAlignment(Qt::AlignCenter);
                MbT->setItem(i,j,item);
            }
            else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=Mb->item(j,i)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                if((i==0 && j>1)||(j==0 && i>1))
                {
                    CellStyle(ValoraInsertar);
                    ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                }
                else if((i==1 && j>1)||(j==1 && i>1))
                {
                    CellStyleComponente(ValoraInsertar);
                }
                MbT->setItem(i,j,ValoraInsertar);
            }
            /*      Se colocan no editables algunas de las celdas que estan vacias*/
            else
            {
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                MbT->setItem(i,j,ValoraInsertar);
            }
        }
    }
    titlespanMatrizExgEnd(MbT);
    createTab("Pnc",MbT);
    opcionMBT++;
}

//FH_008
/**
    @brief Función que permite calcular la incidencia al 100% según el modelo no clásico
    @date 04/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPHNCIncidencia100()
{
    if(opcionMBT == 0)
    {
        calcularMbT();
    }
    QTableWidget *MatrizMi = new QTableWidget;
    MatrizMi->setObjectName("PIHnc100");
    calcularPHNCIncidencia100(MatrizMi);

    createTab("PIHnc100",MatrizMi,true);

    actionPHNoClasicoIncidencia100.setDisabled(true);
}

/**
    @brief Función que permite calcular la incidencia "i" en los precios homogéneos no clásico (cuenta)
    @date 05/11/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
*/
void MainWindow::calcularPHNCIncidencia100(QTableWidget *tw)
{
    QTableWidget *Mbt = findChild<QTableWidget *>("MatrizMbT");
    int fila = Mbt->rowCount()-2;
    int columna = Mbt->columnCount()-2;
    MatrixXd Res(fila,columna);
    for(int i=0;i<fila;i++)
    {
        for(int j=0;j<columna;j++)
        {
            Res(i,j)=MatrizMbt(i,j) * Vpond.at(i);
        }
    }
    crearTablaVaciaEncadenamiento(fila+2,tw,columna+2);
    for(int i=0;i<fila+2;i++)
    {
        for(int j=0;j<columna+2;j++)
        {
            if(i>=2 and j>=2)
            {
                double value = Res(i-2,j-2);
                QString valor = QString::number(value,'f',precission);
                QTableWidgetItem *item = new QTableWidgetItem(valor);
                valor = Separador(item,false);
                item->setText(valor);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setTextAlignment(Qt::AlignCenter);
                tw->setItem(i,j,item);
            }
            else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=Mbt->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                if((i==0 && j>1)||(j==0 && i>1))
                {
                    CellStyle(ValoraInsertar);
                    ValoraInsertar->setTextAlignment(Qt::AlignCenter);
                }
                else if((i==1 && j>1)||(j==1 && i>1))
                {
                    CellStyleComponente(ValoraInsertar);
                }
                tw->setItem(i,j,ValoraInsertar);
            }
            /*      Se colocan no editables algunas de las celdas que estan vacias*/
            else
            {
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                tw->setItem(i,j,ValoraInsertar);
            }
        }
    }
    titlespanMatrizExgEnd(tw);
}

/**
    @brief Función que permite generar una tabla con las incidencias "i" por cuenta segn el modelo no clásico
    @date 05/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPHNCIncidenciaiCuenta()
{
    if(opcionMBT == 0)
    {
        calcularMbT();
    }
    FI = new FormIncidenciaI(this);
    QTableWidget *tw = FI->ui->TableIncidencia;
    QStringList nombreCuenta = obtenerCuentas();
    int cuentas = nombreCuenta.count();
    crearTablaVaciaEncadenamiento(2,tw,cuentas);
    for(int i=0;i<cuentas;i++)
    {
        QTableWidgetItem *titulo = new QTableWidgetItem(nombreCuenta.at(i));
        titulo->setFlags(titulo->flags() ^ Qt::ItemIsEditable);
        titulo->setTextAlignment(Qt::AlignCenter);
        CellStyle(titulo);
        tw->setItem(0,i,titulo);
        QTableWidgetItem *number = new QTableWidgetItem(QString::number(0,'f',precission));
        number->setTextAlignment(Qt::AlignCenter);
        QString item = Separador(number,false);
        number->setText(item);
        tw->setItem(1,i,number);
    }
    connect(FI->ui->CalcularIncidencia,SIGNAL(clicked()),this,SLOT(slotCalcularPHNCIncidenciaiCuenta()));
    FI->show();
}

/**
    @brief Función que permite calcular la incidencia según el modelo no clásico por una cuenta seleccionada
    @date 05/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCalcularPHNCIncidenciaiCuenta()
{
    QTableWidget *tw = FI->ui->TableIncidencia;
    QStringList nombreCuenta = obtenerCuentas();
    int cuentas = nombreCuenta.count();
    QMap<QString,double> cantidades;
    for(int i=0;i<cuentas;i++)
    {
        QString cuenta = tw->item(0,i)->text();
        QString value = Separador(tw->item(1,i),true);
        cantidades.insert(cuenta,value.toDouble());
    }

    QTableWidget *MatrizIC = new QTableWidget;
    MatrizIC->setObjectName(QString("PHNCIcuenta %1").arg(cantidadPHNCindidenciaiCuenta));
    calcularPHNCIncidencia100(MatrizIC);
    calcularPHCIncidenciaI(MatrizIC,cantidades);

    createTab(QString("PIHnci %1").arg(cantidadPHNCindidenciaiCuenta),MatrizIC,true);
    cantidadPHNCindidenciaiCuenta++;
}

/**
    @brief Función que permite calcular la incidencia según el modelo no clásico por un componente seleccionado
    @date 05/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPHNCIncidenciaiComponente()
{
    if(opcionMBT == 0)
    {
        calcularMbT();
    }
    FI = new FormIncidenciaI(this);
    int contador = ComponentesEndogenos.count();

    QTableWidget *tw = FI->ui->TableIncidencia;
    crearTablaVaciaEncadenamiento(2,tw,contador);

    for(int i=0;i<contador;i++)
    {
        QTableWidgetItem *titulo = new QTableWidgetItem(ComponentesEndogenos.at(i));
        titulo->setFlags(titulo->flags() ^ Qt::ItemIsEditable);
        titulo->setTextAlignment(Qt::AlignCenter);
        CellStyleComponente(titulo);
        tw->setItem(0,i,titulo);
        QTableWidgetItem *number = new QTableWidgetItem(QString::number(0,'f',precission));
        number->setTextAlignment(Qt::AlignCenter);
        QString item = Separador(number,false);
        number->setText(item);
        tw->setItem(1,i,number);
    }
    connect(FI->ui->CalcularIncidencia,SIGNAL(clicked()),this,SLOT(slotCalcularPHNCIncidenciaiComponente()));
    FI->show();
}

/**
    @brief Función que permite calcular la incidencia "i" en los precios homogéneos no clásico (componente)
    @date 05/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCalcularPHNCIncidenciaiComponente()
{
    QTableWidget *tw = FI->ui->TableIncidencia;

    QTableWidget *MatrizIComp = new QTableWidget;
    MatrizIComp->setObjectName(QString("PHNCIcomponente %1").arg(cantidadPHNCindidenciaiComponente));
    calcularPHNCIncidencia100(MatrizIComp);
    calcularPHCIncidenciaIComponente(MatrizIComp,tw);

    createTab(QString("PIHncic %1").arg(cantidadPHNCindidenciaiComponente),MatrizIComp,true);
    cantidadPHNCindidenciaiComponente++;
}

//FH_009
/**
    @brief Función que permite abrir el formulario para las incidencias al 100%
    @date 06/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPNHIncudencia100()
{
    if(opcionFormPNH==0)
    {
        crearFormularioPNH();
        QPushButton *buttonSeleccionar = findChild<QPushButton *>("SeleccionarPNH");
        connect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNH()));
        formPreciosNoHomogeneos->show();
    }
    else
    {
        QPushButton *buttonSeleccionar = findChild<QPushButton *>("SeleccionarPNH");
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHi()));
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHic()));
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNH()));
        connect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNH()));
        formPreciosNoHomogeneos->show();
    }
}

/**
    @brief Función que permite cerrar el formulario para las incidencias al 100%
    @date 06/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCloseformPNH()
{
    formPreciosNoHomogeneos->close();
}

/**
    @brief Función que permite seleccionar los componentes en el formulario para las incidencias al 100%
    @date 06/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotSelectPNH()
{
    int cantidad=stackPNH->comboAccount->count();
    int seleccionados = 0;
    for(int i = 0;i<cantidad;i++)
    {
        QListWidget *lw = findChild<QListWidget *>(QString("accountlistPNH %1").arg(i+1));
        seleccionados += lw->selectedItems().count();
    }
    if(seleccionados>1)
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar sólo\nun componente");
    }
    else if(seleccionados<1)
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar un componente");
    }
    else
    {
        QStringList componentes;
        for(int i = 0;i<cantidad;i++)
        {
            QListWidget *lw = findChild<QListWidget *>(QString("accountlistPNH %1").arg(i+1));
            if(lw->selectedItems().count()!=0)
            {
                componentes.append(lw->selectedItems().value(0)->text());
            }
        }
        QString componente = componentes.at(0);
        QVector<double> Send;
        calcularVectorSend(componente,Send);
        QTableWidget *PNH100 = new QTableWidget;
        opcionPNHT = 0;
        multiplicarMatricesPNH(PNH100,Send);
        formPreciosNoHomogeneos->close();
    }
}

/**
    @brief Funcion para calcular el vector Send, que se utiliza para crear una matriz identidad con una diagonal conformada
                                    por los valores de un componente previamente seleccionado
    @date 06/11/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularVectorSend(QString componente,QVector<double> &vector)
{
    if(opcionMa == 0)
    {
        slotMa();
    }
    if(opcionMb == 0)
    {
        calcularMb();
    }
    QTableWidget *Bn = findChild<QTableWidget *>("Bn");
    int filas = Bn->rowCount();
    int columnas = Bn->columnCount();
    for(int i=2;i<filas;i++)
    {
        if(Bn->item(i,1)->text()==componente)
        {
            for(int j=2;j<columnas;j++)
            {
                QString value = Separador(Bn->item(i,j),true);
                vector.append(value.toDouble());
            }
            break;
        }
    }
}

/**
    @brief Función que permite realizar la multiplicación de matrices en los precios no homogéneos
    @date 08/11/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <vector> Recibe el vector con los valores que irán en la diagonal principal
*/
void MainWindow::multiplicarMatricesPNH(QTableWidget *tw,QVector<double> vector)
{
    int count = MatrixMa.rows();
    MatrixXd ident = MatrixXd::Identity(count,count);
    for(int i = 0;i<count;i++)
    {
        for(int j = 0;j<count;j++)
        {
            if(i==j)
            {
                ident(i,j) = vector.at(i);
            }
        }
    }
    MatrixXd res = ident*MatrixMa;
    /*for(int i = 0;i<count;i++)
    {
        for(int j = 0;j<count;j++)
        {
            double value = res(i,j);
            QString valor = QString::number(value,'f',precission);
            QTableWidgetItem *item = new QTableWidgetItem(valor);
            valor = Separador(item,false);
            item->setText(valor);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            tw->setItem(i,j,item);
        }
    }
    tabWidget->addTab(new QWidget,"PNHMa");
    int indice=ObtenerIndice("PNHMa");

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tw);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);*/

    MatrixXd trans = res.transpose();
    /*QTableWidget *nt = new QTableWidget;
    CrearTablaVacia(count+1,nt);
    for(int i = 0;i<count;i++)
    {
        for(int j = 0;j<count;j++)
        {
            double value = trans(i,j);
            QString valor = QString::number(value,'f',precission);
            QTableWidgetItem *item = new QTableWidgetItem(valor);
            valor = Separador(item,false);
            item->setText(valor);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            nt->setItem(i,j,item);
        }
    }
    tabWidget->addTab(new QWidget,"PNHMa^T");
    indice=ObtenerIndice("PNHMa^T");
    QHBoxLayout * layoutCentralWidget2 = new QHBoxLayout;
    layoutCentralWidget2->addWidget(nt);
    QWidget *widget2 = tabWidget->widget(indice);
    widget2->setLayout(layoutCentralWidget2);
    tabWidget->setCurrentIndex(indice);*/

    calcularPNHIncidencia100(tw,trans);
    if(opcionPNHT == 0)
    {
        createTab(QString("PINH100 %1").arg(cantidadPNHincidencia100),tw,true);
        cantidadPNHincidencia100++;
        opcionPNHT = 1;
    }
}

/**
    @brief Función que permite realizar la multiplicación de matrices en los precios no homogéneos con incidencia al 100%
    @date 10/11/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <Diagonal> Recibe el vector con la diagonal principal
*/
void MainWindow::calcularPNHIncidencia100(QTableWidget *tw,MatrixXd Diagonal)
{
    int count = Vpond.count();
    MatrixXd Res(count,count);
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
        {
            Res(i,j)=Diagonal(i,j) * Vpond.at(i);
        }
    }
    CrearTablaVacia(count+1,tw);
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
        {
            double value = Res(i,j);
            QString valor = QString::number(value,'f',precission);
            QTableWidgetItem *item = new QTableWidgetItem(valor);
            valor = Separador(item,false);
            item->setText(valor);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            tw->setItem(i,j,item);
        }
    }
    titleEndogena(tw);
    spanEndogenaCell(tw,2,0,false);
}

/**
    @brief Función que permite abrir el formulario para las incidencias por cuenta en los precios no homogéneos
    @date 06/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPNHIncidenciaiCuenta()
{
    if(opcionFormPNH==0)
    {
        crearFormularioPNH();
        QPushButton *buttonSeleccionar = findChild<QPushButton *>("SeleccionarPNH");
        connect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHi()));
        formPreciosNoHomogeneos->show();
    }
    else
    {
        QPushButton *buttonSeleccionar = findChild<QPushButton *>("SeleccionarPNH");
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNH()));
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHic()));
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHi()));
        connect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHi()));
        formPreciosNoHomogeneos->show();
    }

}

/**
    @brief Función que permite seleccionar los componentes el formulario para las incidencias por cuenta en los precios no homogéneos
    @date 06/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotSelectPNHi()
{
    int cantidad=stackPNH->comboAccount->count();
    int seleccionados = 0;
    for(int i = 0;i<cantidad;i++)
    {
        QListWidget *lw = findChild<QListWidget *>(QString("accountlistPNH %1").arg(i+1));
        seleccionados += lw->selectedItems().count();
    }
    if(seleccionados>1)
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar sólo\nun componente");
    }
    else if(seleccionados<1)
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar un componente");
    }
    else
    {
        QStringList componentes;
        for(int i = 0;i<cantidad;i++)
        {
            QListWidget *lw = findChild<QListWidget *>(QString("accountlistPNH %1").arg(i+1));
            if(lw->selectedItems().count()!=0)
            {
                componentes.append(lw->selectedItems().value(0)->text());
            }
        }
        componentePNH = componentes.at(0);
        formPreciosNoHomogeneos->close();
        FI = new FormIncidenciaI(this);
        QTableWidget *tw = FI->ui->TableIncidencia;
        QStringList nombreCuenta = obtenerCuentas();
        int cuentas = nombreCuenta.count();
        crearTablaVaciaEncadenamiento(2,tw,cuentas);        
        for(int i=0;i<cuentas;i++)
        {
            QTableWidgetItem *titulo = new QTableWidgetItem(nombreCuenta.at(i));
            titulo->setFlags(titulo->flags() ^ Qt::ItemIsEditable);
            titulo->setTextAlignment(Qt::AlignCenter);
            CellStyle(titulo);
            tw->setItem(0,i,titulo);
            QTableWidgetItem *number = new QTableWidgetItem(QString::number(0,'f',precission));
            number->setTextAlignment(Qt::AlignCenter);
            QString item = Separador(number,false);
            number->setText(item);
            tw->setItem(1,i,number);
        }
        connect(FI->ui->CalcularIncidencia,SIGNAL(clicked()),this,SLOT(slotCalcularPNHIncidenciaiCuenta()));
        FI->show();
    }
}

/**
    @brief Función que permite calcular las incidencias "i" por cuenta en los precios no homogéneos
    @date 08/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCalcularPNHIncidenciaiCuenta()
{
    QVector<double> Send;
    calcularVectorSend(componentePNH,Send);
    QTableWidget *PNH100 = new QTableWidget;
    multiplicarMatricesPNH(PNH100,Send);
    int count = PNH100->rowCount();
    QTableWidget *PNHI = new QTableWidget;
    CrearTablaVacia(count+1,PNHI);
    clonarTabla(PNH100,PNHI,count+1);
    spanEndogenaCell(PNHI,2,0,false);

    QTableWidget *tw = FI->ui->TableIncidencia;
    QStringList nombreCuenta = obtenerCuentas();
    int cuentas = nombreCuenta.count();
    QMap<QString,double> cantidades;
    for(int i=0;i<cuentas;i++)
    {
        QString cuenta = tw->item(0,i)->text();
        QString value = Separador(tw->item(1,i),true);
        cantidades.insert(cuenta,value.toDouble());
    }

    calcularPHCIncidenciaI(PNHI,cantidades);

    createTab(QString("PINHi %1").arg(cantidadPNHincidenciaiCuenta),PNHI,true);
    cantidadPNHincidenciaiCuenta++;
    FI->close();
}

/**
    @brief Función que permite generar una tabla con las incidencias "i" por cuenta en los precios no homogéneos
    @date 11/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotPNHIncidenciaiComponente()
{
    if(opcionFormPNH==0)
    {
        crearFormularioPNH();
        QPushButton *buttonSeleccionar = findChild<QPushButton *>("SeleccionarPNH");
        connect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHic()));
        formPreciosNoHomogeneos->show();
    }
    else
    {
        QPushButton *buttonSeleccionar = findChild<QPushButton *>("SeleccionarPNH");
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNH()));
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHi()));
        disconnect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHic()));
        connect(buttonSeleccionar,SIGNAL(clicked()),this,SLOT(slotSelectPNHic()));
        formPreciosNoHomogeneos->show();
    }
}

/**
    @brief Función que permite seleccionar los componentes en el formulario de precios no homogéneos
    @date 11/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotSelectPNHic()
{
    int cantidad=stackPNH->comboAccount->count();
    int seleccionados = 0;
    for(int i = 0;i<cantidad;i++)
    {
        QListWidget *lw = findChild<QListWidget *>(QString("accountlistPNH %1").arg(i+1));
        seleccionados += lw->selectedItems().count();
    }
    if(seleccionados>1)
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar sólo\nun componente");
    }
    else if(seleccionados<1)
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar un componente");
    }
    else
    {
        QStringList componentes;
        for(int i = 0;i<cantidad;i++)
        {
            QListWidget *lw = findChild<QListWidget *>(QString("accountlistPNH %1").arg(i+1));
            if(lw->selectedItems().count()!=0)
            {
                componentes.append(lw->selectedItems().value(0)->text());
            }
        }
        componentePNH = componentes.at(0);
        formPreciosNoHomogeneos->close();
        FI = new FormIncidenciaI(this);
        QTableWidget *tw = FI->ui->TableIncidencia;
        int contador = ComponentesEndogenos.count();
        crearTablaVaciaEncadenamiento(2,tw,contador);

        for(int i=0;i<contador;i++)
        {
            QTableWidgetItem *titulo = new QTableWidgetItem(ComponentesEndogenos.at(i));
            titulo->setFlags(titulo->flags() ^ Qt::ItemIsEditable);
            titulo->setTextAlignment(Qt::AlignCenter);
            CellStyleComponente(titulo);
            tw->setItem(0,i,titulo);
            QTableWidgetItem *number = new QTableWidgetItem(QString::number(0,'f',precission));
            number->setTextAlignment(Qt::AlignCenter);
            QString item = Separador(number,false);
            number->setText(item);
            tw->setItem(1,i,number);
        }
        connect(FI->ui->CalcularIncidencia,SIGNAL(clicked()),this,SLOT(slotCalcularPNHIncidenciaiComponente()));
        FI->show();
    }
}

/**
    @brief Función que permite calcular las incidencias "i" por componentes
    @date 12/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotCalcularPNHIncidenciaiComponente()
{
    QVector<double> Send;
    calcularVectorSend(componentePNH,Send);
    QTableWidget *PNH100 = new QTableWidget;
    multiplicarMatricesPNH(PNH100,Send);
    int count = PNH100->rowCount();
    QTableWidget *PNHIc = new QTableWidget;
    CrearTablaVacia(count+1,PNHIc);
    clonarTabla(PNH100,PNHIc,count+1);
    spanEndogenaCell(PNHIc,2,0,false);

    QTableWidget *tw = FI->ui->TableIncidencia;
    calcularPHCIncidenciaIComponente(PNHIc,tw);

    createTab(QString("PINHic %1").arg(cantidadPNHincidenciaiComponente),PNHIc,true);
    cantidadPNHincidenciaiComponente++;
    FI->close();
}

/**
    @brief Función que permite generar el formularios para precios no homogéneos
    @date 05/11/2015
    @author Rodrigo Boet
*/
void MainWindow::crearFormularioPNH()
{
    formPreciosNoHomogeneos = new FormPreciosNoHomogeneos(this);
    QHBoxLayout * layoutLateralWidget = new QHBoxLayout;
    QVBoxLayout * layoutCentralWidget = new QVBoxLayout;
    QHBoxLayout * layoutAccounts = new QHBoxLayout;
    QHBoxLayout * labels = new QHBoxLayout;
    QLabel *label1 = new QLabel;
    QLabel *label2 = new QLabel;
    label1->setText("Cuentas");
    label2->setText("Componentes");
    labels->addWidget(label1);
    labels->addWidget(label2);
    QWidget *nw = new QWidget;
    nw->setLayout(labels);
    QGroupBox * groupBoxAccount = new QGroupBox;
    layoutCentralWidget->addWidget(nw);
    layoutAccounts->addWidget(stackPNH=new StackPreciosNoHomogeneos(diccCuentasExogenas,groupBoxAccount));

    groupBoxAccount->setObjectName("PNHgroupbox");//Se le asigna nombre al objeto
    groupBoxAccount->setLayout(layoutAccounts);;
    groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                     "border-radius: 3px; margin-top: 0.5em;} "
                     "QGroupBox::title { subcontrol-origin: margin; "
                     "left: 10px; padding: 0 3px 0 3px; } ");


    layoutLateralWidget->addWidget(groupBoxAccount);

    /***        Se crean y personalizan los bottones para seleccionar y cancelar    ***/
    QPushButton * buttonSeleccionar = new QPushButton;
    buttonSeleccionar->setObjectName("SeleccionarPNH");//Se le asigna nombre al objeto
    buttonSeleccionar->setText("&Seleccionar");
    buttonSeleccionar->setFixedWidth(130);
    buttonSeleccionar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    QPushButton * buttonCancelar = new QPushButton;
    buttonCancelar->setObjectName("CancelarPNH");//Se le asigna nombre al objeto
    buttonCancelar->setText("&Cancelar");
    buttonCancelar->setFixedWidth(130);
    buttonCancelar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");

    connect(buttonCancelar,SIGNAL(clicked()),this,SLOT(slotCloseformPNH()));

    QHBoxLayout * layoutsButtons = new QHBoxLayout;
    layoutsButtons->addWidget(buttonSeleccionar);
    layoutsButtons->addWidget(buttonCancelar);
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(layoutsButtons);

    QWidget *widget = new QWidget;
    widget->setLayout(layoutLateralWidget);
    layoutCentralWidget->addWidget(widget);
    layoutCentralWidget->addWidget(buttonWidget);//Se agregan los botones
    formPreciosNoHomogeneos->setLayout(layoutCentralWidget);
    opcionFormPNH++;
}

//  FV_001
/*                      A partir de aquí comienzan las operaciones del menu Visualización                   */
/**
    @brief Función que permite seleccionar un fragmento de una tabla y mostrarla en una pestaña a parte
    @date 15/11/2015
    @author Rodrigo Boet
*/
void MainWindow::slotSeleccionarTabla()
{
    int index = tabWidget->currentIndex();
    QString tabName = tabWidget->tabText(index);
    if(tabName.contains("Inicio") or tabName.contains("Encadenamiento") or tabName.contains("Escenario") or tabName.contains("Clasificador")
            or tabName.contains("Resultado") or tabName.contains("Comparacion") or tabName.contains("Seleccion"))
    {
        QMessageBox::warning(this,"Alerta","Esta pestaña no se puede\nseleccionar");
    }
    else
    {
        int inicio = 2;
        int cuentaNumber = 0;
        int componenteNumber = 1;
        if(tabName=="Tipo de Variable")
        {
            inicio = 3;
            cuentaNumber = 1;
            componenteNumber = 2;
        }
        QTableWidget *tw = tabWidget->widget(index)->findChild<QTableWidget *>();
        int fila = tw->rowCount();
        int columna = tw->columnCount();
        int filas = 0;
        int columnas = 0;
        for(int i = inicio; i<fila; i++)
        {
            bool selected = false;
            for(int j = inicio; j<columna; j++ )
            {
                if(tw->item(i,j)->isSelected())
                {
                    columnas++;
                    selected = true;
                }
            }
            if(selected)
            {
                filas++;
            }
        }
        if(filas==0 or columnas==0)
        {
            QMessageBox::warning(this,"Alerta","Debe Seleccionar al menos\n alguna fila/columna");
        }
        else
        {
            columnas =  columnas/filas;
            QTableWidget *nuevaTabla = new QTableWidget;
            if(filas==columnas)
            {
                CrearTablaVacia(filas+3,nuevaTabla);
            }
            else
            {
                crearTablaVaciaEncadenamiento(filas+2,nuevaTabla,columnas+2);
            }
            bool centinela = false;
            int probFila = 2;
            for(int i = 0; i<fila; i++)
            {
                int probCol = 2;
                bool select = false;
                for(int j = 0; j<columna; j++ )
                {
                    if(tw->item(i,j)->isSelected())
                    {
                        if(i<inicio or j<inicio)
                        {
                            centinela=true;
                            break;
                        }
                        else
                        {
                            //Cuentas
                            QTableWidgetItem *cuentaFila = new QTableWidgetItem(tw->item(cuentaNumber,j)->text());
                            cuentaFila->setFlags(cuentaFila->flags() ^ Qt::ItemIsEditable);
                            cuentaFila->setTextAlignment(Qt::AlignCenter);
                            QTableWidgetItem *cuentaColumna = new QTableWidgetItem(tw->item(i,cuentaNumber)->text());
                            cuentaColumna->setFlags(cuentaColumna->flags() ^ Qt::ItemIsEditable);
                            cuentaColumna->setTextAlignment(Qt::AlignCenter);
                            CellStyle(cuentaFila);
                            CellStyle(cuentaColumna);
                            nuevaTabla->setItem(0,probCol,cuentaFila);
                            nuevaTabla->setItem(probFila,0,cuentaColumna);
                            //Componentes
                            QTableWidgetItem *componenteFila = new QTableWidgetItem(tw->item(componenteNumber,j)->text());
                            componenteFila->setFlags(componenteFila->flags() ^ Qt::ItemIsEditable);
                            QTableWidgetItem *componenteColumna = new QTableWidgetItem(tw->item(i,componenteNumber)->text());
                            componenteColumna->setFlags(componenteColumna->flags() ^ Qt::ItemIsEditable);
                            CellStyleComponente(componenteFila);
                            CellStyleComponente(componenteColumna);
                            nuevaTabla->setItem(1,probCol,componenteFila);
                            nuevaTabla->setItem(probFila,1,componenteColumna);
                            //Valor
                            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(tw->item(i,j)->text());
                            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
                            nuevaTabla->setItem(probFila,probCol,valoraInsertar);
                            probCol++;
                            select = true;
                        }
                    }
                }
                if(select)
                {
                    probFila++;
                }
            }
            if(centinela)
            {
                QMessageBox::warning(this,"Alerta","No es necesario seleccionar cuenta/componente");
            }
            else
            {
                ItemsNoEditable(nuevaTabla,0,2,1);

                titleSeleccionar(nuevaTabla);
                createTab(QString("Seleccion %1").arg(cantidadSelecciones),nuevaTabla,true);
                cantidadSelecciones++;
            }
        }
    }
}

/**
    @brief Función para mostrar el formulario para la descomposicion
    @date 27/09/2015
    @author Rodrigo Boet
*/
void MainWindow::slotDescomposicion()
{
    formdescomposicion = new FormDescomposicion(this);
    QStringList list;
    foreach(int key,diccCuentasEndogenas.keys())
    {
        list.append(diccCuentasEndogenas[key][0]);
    }
    formdescomposicion->ui->listAgregar->addItems(list);
    connect(formdescomposicion->ui->pushButton_3,SIGNAL(clicked()),this,SLOT(slotAgregarDescomposicion()));
    formdescomposicion->show();
}

/**
    @brief Función para seleccionar las cuentas que seran actividad/producto
    @date 27/09/2015
    @author Rodrigo Boet
*/
void MainWindow::slotAgregarDescomposicion()
{
    int item = formdescomposicion->ui->listSeleccionado->count();
    if(item==2)
    {
        QStringList list;
        for(int i=0;i<item;i++)
        {
            list.append(formdescomposicion->ui->listSeleccionado->item(i)->text());
        }
        if(validarDescomposicion(list))
        {
            QTableWidget *tw = findChild<QTableWidget *>("MatrizAn");
            int filas = tw->rowCount();
            Eigen::MatrixXd M1 = extractSubMatriz(tw,list.at(0),list.at(0),An);
            Eigen::MatrixXd M2 = extractSubMatriz(tw,list.at(0),list.at(1),An);
            Eigen::MatrixXd M3 = extractSubMatriz(tw,list.at(1),list.at(0),An);
            Eigen::MatrixXd M4 = extractSubMatriz(tw,list.at(1),list.at(1),An);
            QVector<double> V1 = extractDiagonal(M1);
            QVector<double> V2 = extractDiagonal(M2);
            QVector<double> V3 = extractDiagonal(M3);
            QVector<double> V4 = extractDiagonal(M4);
            QVector<double> diagonal;
            if(validarDiagonal(V1))
            {
                appendElements(V1,diagonal);
            }
            if(validarDiagonal(V2))
            {
                appendElements(V2,diagonal);
            }
            if(validarDiagonal(V3))
            {
                appendElements(V3,diagonal);
            }
            if(validarDiagonal(V4))
            {
                appendElements(V4,diagonal);
            }
            for (int i = 2; i<filas;i++)
            {
                for(int j=2; j<filas;j++)
                {
                    if(tw->item(0,j)->text()!=list.at(0) and tw->item(0,j)->text()!=list.at(1))
                    {
                        if(i==j)
                        {
                            diagonal.append(An(i-2,j-2));
                        }
                    }
                }
            }
            calcularA0(diagonal);
            calcularAuxiliares();
            calcularMatricesDescomposicion();

        }
        else
        {
            QMessageBox::warning(this,"Error","La cuenta Producto y Actividad\ndeben ser simétricas, ajuste la matriz\ne intente de nuevo");
        }
    }
    else
    {
        QMessageBox::warning(this,"Alerta","Debe seleccionar dos (2) cuentas");
    }

}

/**
    @brief Función para validar que las cuentas producto y actividad sean simétricas
    @date 28/09/2015
    @author Rodrigo Boet
    @param <cuentas> Recibe la lista con las cuentas
    @return <valores> Retorna verdadera si son simétricas, falso en caso contrario
*/
bool MainWindow::validarDescomposicion(QStringList cuentas)
{
    QStringList valores;
    foreach (int key, diccCuentasEndogenas.keys()) {
       if (diccCuentasEndogenas[key][0]==cuentas.at(0) or diccCuentasEndogenas[key][0]==cuentas.at(1))
       {
           valores.append(diccCuentasEndogenas[key][1]);
       }
    }
    if(valores.at(0)==valores.at(1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
    @brief Función para calcular A0
    @date 28/09/2015
    @author Rodrigo Boet
    @param <diagonal> Recibe el valor de las diagonales
*/
void MainWindow::calcularA0(QVector<double> diagonal)
{
    A0 = MatrixXd::Identity(An.rows(),An.cols());
    int fila = A0.rows();
    for(int i=0;i<fila;i++)
    {
        for(int j=0;j<fila;j++)
        {
            if(i==j)
            {
                A0(i,j)=diagonal.at(i);
            }
        }
    }
    QTableWidget *MAN = findChild<QTableWidget *>("MatrizAn");
    QTableWidget *tw = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),tw);
    noEditColZero(tw);
    clonarTabla(MAN,tw,MAN->rowCount());
    fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(A0(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            tw->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(tw,2,0,false);
    createTab("A0",tw,true);
    formdescomposicion->close();

    MatrixXd ident = MatrixXd::Identity(An.rows(),An.cols());
    M1 = ident - A0;
    M1 = M1.inverse();
    QTableWidget *Mm1 = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),Mm1);
    noEditColZero(Mm1);
    clonarTabla(MAN,Mm1,MAN->rowCount());
    fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(M1(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            Mm1->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(Mm1,2,0,false);
    createTab("M1",Mm1);
}

/**
    @brief Función para calcular los auxiliares de la descomposicion y también M2 y M3
    @date 28/09/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularAuxiliares()
{
    MatrixXd ident = MatrixXd::Identity(A0.rows(),A0.cols());
    MatrixXd aux = M1*(A0-An);
    M2 = ident+aux;
    int cantidad = diccCuentasEndogenas.count()-2;
    MatrixXd ant = aux;
    for(int i=0;i<cantidad;i++)
    {
        aux *= ant;
        ant = aux;
        if(i<cantidad-1)
        {
            M2 += aux;
        }
    }
    M3 = ident - aux;
    M3 = M3.inverse();
    QTableWidget *MAN = findChild<QTableWidget *>("MatrizAn");
    QTableWidget *Mm2 = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),Mm2);
    noEditColZero(Mm2);
    clonarTabla(MAN,Mm2,MAN->rowCount());
    int fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(M2(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            Mm2->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(Mm2,2,0,false);
    createTab("M2",Mm2);

    QTableWidget *Mm3 = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),Mm3);
    noEditColZero(Mm3);
    clonarTabla(MAN,Mm3,MAN->rowCount());
    fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(M3(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            Mm3->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(Mm3,2,0,false);
    createTab("M3",Mm3);
}

/**
    @brief Función para calcular las matrices de Transferencia (T), Open(O) y Close(C)
    @date 28/09/2015
    @author Rodrigo Boet
*/
void MainWindow::calcularMatricesDescomposicion()
{
    MatrixXd ident = MatrixXd::Identity(A0.rows(),A0.cols());
    T = M1 - ident;
    O = (M2 - ident) * M1;
    C = (M3 - ident) * (M2 * M1);

    QTableWidget *MAN = findChild<QTableWidget *>("MatrizAn");
    QTableWidget *mt = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),mt);
    noEditColZero(mt);
    clonarTabla(MAN,mt,MAN->rowCount());
    int fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(T(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            mt->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(mt,2,0,false);
    createTab("T",mt);

    QTableWidget *mo = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),mo);
    noEditColZero(mo);
    clonarTabla(MAN,mo,MAN->rowCount());
    fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(O(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            mo->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(mo,2,0,false);
    createTab("O",mo);

    QTableWidget *mc = new QTableWidget;
    CrearTablaVacia(MAN->rowCount(),mc);
    noEditColZero(mc);
    clonarTabla(MAN,mc,MAN->rowCount());
    fila = MAN->rowCount()-1;
    for(int i=2;i<fila;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QTableWidgetItem *valoraInsertar = new QTableWidgetItem(QString::number(C(i-2,j-2),'f',precission));
            valoraInsertar->setFlags(valoraInsertar->flags() ^ Qt::ItemIsEditable);
            mc->setItem(i,j,valoraInsertar);
        }
    }
    spanEndogenaCell(mc,2,0,false);
    createTab("C",mc);
}

/**
    @brief Función para crear un nueva pestaña
    @date 28/09/2015
    @author Rodrigo Boet
    @param <texto> Recibe el nombre de la pestaña
    @param <tw> Recibe el widget de la tabla que se insertara
    @param <current> recibe un booleano (verdadero si se coloca como activo, falso en caso contrario)
*/
void MainWindow::createTab(QString texto, QTableWidget *tw, bool current)
{
    tabWidget->addTab(new QWidget,texto);
    int indice=ObtenerIndice(texto);

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tw);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    if(current)
    {
        tabWidget->setCurrentIndex(indice);
    }

}

