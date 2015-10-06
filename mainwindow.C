/*
    Creado bajo la Licencia GPL v.2.0 de la Free Software Foundation.
    primer aporte realizado por José Ruiz en Mayo de 2015
    resto del proyecto realizado por Rodrigo Boet desde Junio/2015
*/

#include "mainwindow.H"
#include "accountwidget.H"
#include "stackvariablesexogenas.h"
#include "formexportmatrix.h"
#include <stackencadenamientos.h>
#include <QDebug>

using namespace Eigen;

//  FA_001
/*                      A partir de aquí comienzan las operaciones del menu Archivo                   */
void MainWindow::slotLoadMatrix()
{
    formLoadMatrix = new  FormLoadMatrix(this);
    formLoadMatrix->show();
    connect(formLoadMatrix, SIGNAL(formAccepted(QString,int,int)),
            this, SLOT(slotFormLoadMatrixAccepted(QString,int,int)));
}

void MainWindow::slotFormLoadMatrixAccepted(const QString & filePath,
                                            int accountNumber, int pre)
{
    csvFilePath = filePath;
    csvSeparator = ';';
    numAccounts = accountNumber;
    precission = pre;

    createMatrixCentralWidget();
}

void MainWindow::slotFormLoadMatrixClosed()
{
    disconnect(formLoadMatrix, SIGNAL(formAccepted(QString,int)),
               this, SLOT(slotFormLoadMatrixAccepted(QString,int)));
    formLoadMatrix = 0;
}

/*      Funcion para crear un nuevo proyecto        */
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
        buttonExplorar->setIcon(QIcon("./img/folder_blue.png"));

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

void MainWindow::slotCloseExport()
{
    formExportMatriz->ExportLine->setText("");
    formExportMatriz->close();
}

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
            formExportMatriz->ExportLine->setText("");
            formExportMatriz->close();
        }
        else
        {
            QMessageBox::critical(this,"Alerta","No puede exportar la pestaña\n inicio");
        }
    }
}

void MainWindow::slotSearchExport()
{
    QString format = ".csv";

    QString filename = QFileDialog::getSaveFileName(this,
            "Elija el nombre", QDir::homePath(),"*.csv");

    filename.remove(format);

    filename +=format;

    formExportMatriz->ExportLine->setText(filename);
}

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
    lblMatrix->setPixmap(QPixmap("./img/Imagen-matriz.png"));
    layoutMatrix->addWidget(lblMatrix);
    layoutCentralWidget->addLayout(layoutMatrix);

    QHBoxLayout * layoutFoot = new QHBoxLayout;
    QLabel * lblFoot = new QLabel("Fundación Centro Nacional de Desarrollo e" \
                                  " Investigación en\nTecnologías Libres." \
                                  " Nodo Mérida.");
    lblFoot->setFont(QFont("Aero Matics", 19, 1));
    lblFoot->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    QLabel * lblLogo = new QLabel;
    lblLogo->setPixmap(QPixmap("./img/logo_cenditel.jpg"));
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

    menuTools.addMenu(&CoeficientesTecnicos);

    actionVariableExogena.setText("Definir Variables &Exogenas");
    actionVariableExogena.setDisabled(true);

    menuTools.addAction(&actionVariableExogena);

    Encadenamientos.setTitle("E&ncadenamientos");
    Encadenamientos.setDisabled(true);

    actionEncadenamiento.setText("&Estimar Encadenamientos");
    actionEncadenamiento.setDisabled(true);
    Encadenamientos.addAction(&actionEncadenamiento);

    actionClasificarCuentas.setText("&Clasificar Cuentas");
    actionClasificarCuentas.setDisabled(true);
    Encadenamientos.addAction(&actionClasificarCuentas);

    menuTools.addMenu(&Encadenamientos);

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

void MainWindow::closeEvent(QCloseEvent * event)
{
    QMessageBox msBox(QMessageBox::Question,"Alerta","¿Desea Salir?", QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    if(msBox.exec()==QMessageBox::No)
    {
        event->ignore();
    }
}

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
    buttonRestaurar->setIcon(QIcon("./img/undo-habilitado.png"));
    buttonRestaurar->setFlat(true);
    buttonRestaurar->setObjectName("Restaurar");
    buttonRestaurar->setFixedWidth(100);
    /*buttonRestaurar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");*/

    //buttonModificar->setText("&Editar ");
    buttonModificar->setIcon(QIcon("./img/edit-deshabilitado.png"));
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

void MainWindow::populateTable(QTableWidget * tableWidget) {

    QFile file(csvFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int row = 0;
        QString lineHead = file.readLine();
        const std::vector<std::string> rowVH =
                csv_read_row(lineHead.toStdString(), csvSeparator);


        matrixSize = rowVH.size();
        tableWidget->setRowCount(matrixSize+1);
        tableWidget->setColumnCount(matrixSize+1);

        for(int column=0; column<matrixSize; column++) {
            QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::fromUtf8(rowVH[column].c_str()).
                    toLocal8Bit().constData());
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);//Se coloca como no editable
            CellStyleComponente(newItem);
            tableWidget->setItem(row, column+1, newItem);
        }
        ++row;

        while (!file.atEnd() and row<=matrixSize)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::fromUtf8(rowVH[row-1].c_str()).
                    toLocal8Bit().constData());
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);//Se coloca como no editable
            CellStyleComponente(newItem);
            tableWidget->setItem(row, 0, newItem);

            QString line = file.readLine();

            std::vector<std::string> rowV =
                    csv_read_row(line.toStdString(), csvSeparator);
            for(int column=0, leng=rowV.size();
            column < leng and column<matrixSize; column++) {

                /*              Aqui se incorporan los valores luego de la coma(,)          */
                QString rowVal = QString::fromUtf8(rowV[column].c_str());
                double value = rowVal.toDouble();


                QTableWidgetItem *newItem = new QTableWidgetItem(
                        numberFormat(value).
                        toLocal8Bit().constData());
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);//Se coloca como no editable
                newItem->setTextAlignment(Qt::AlignCenter);
                tableWidget->setItem(row, column+1, newItem);
                matrix[row-1][column] =  atof(rowV[column].c_str());
            }
            ++row;
        }
        file.close();
    }
}

std::vector<std::string> MainWindow::csv_read_row(std::string line,
                                                  char delimiter)
{
    std::stringstream ss(line);    void msghere();
    return csv_read_row(ss, delimiter);
}

std::vector<std::string> MainWindow::csv_read_row(std::istream &in,
                                                  char delimiter)
{
    std::stringstream ss;
    bool inquotes = false;
    std::vector<std::string> row;//relying on RVO
    while(in.good())
    {
        char c = in.get();
        if (!inquotes && c=='"') //beginquotechar
        {
            inquotes=true;
        }
        else if (inquotes && c=='"') //quotechar
        {
            if ( in.peek() == '"')//2 consecutive quotes resolve to 1
            {
                ss << (char)in.get();
            }
            else //endquotechar
            {
                inquotes=false;
            }
        }
        else if (!inquotes && c==delimiter) //end of field
        {
            row.push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row.push_back( ss.str() );
            return row;
        }
        else
        {
            ss << c;
        }
    }
}

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
void MainWindow::abrirManual()//Funcion para abrir el manual
{
    QDesktopServices::openUrl(QUrl("manual.html"));
}

void MainWindow::acercaDe()//Funcion para el mensaje acerca de
{
    QString Mensaje = "Sistema de Manejo de Matrices de Contabilidad Social\n\n";
    Mensaje+="Fundación Centro Nacional de Desarrollo e Investigación en Tecnologías Libres, 2015.\n";
    Mensaje+="Distribuido bajo la licencia GNU V.2.0\n\n";
    Mensaje+="miv.cenditel.gob.ve/mmcs";
    QMessageBox::information(this,"Acerca de..",Mensaje);
}

//  Main_001
/*                      Aquí se encuentra el centro de la aplicación                   */
MainWindow::MainWindow()
    : actionNewProject(this),actionLoadMatrix(this), actionExportMatrix(this), actionQuit(this),actionCH(this), actionCV(this),
      actionVariableExogena(this),actionEncadenamiento(this),actionClasificarCuentas(this), actionModeloClasico(this),
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

void MainWindow::slotAccChange()
{
    StackWidget *sw = findChild<StackWidget *>();
    int indice = sw->comboAccount->currentIndex();
    QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(indice + 1));
    QPushButton *Modificar = findChild<QPushButton *>("Modificar");
    if(!le->isEnabled())
    {
        Modificar->setEnabled(true);
        Modificar->setIcon(QIcon("./img/edit-habilitado"));
    }
    else
    {
        Modificar->setDisabled(true);
        Modificar->setIcon(QIcon("./img/edit-deshabilitado"));
    }
}

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
                    Modificar->setIcon(QIcon("./img/edit-habilitado"));
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

void MainWindow::FinalizarCuentas()
{
    QMessageBox msBox(QMessageBox::Question,"Finalizar Carga","¿Está seguro que desea finalizar?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        bool Centinela=ComprobarCuentas();//Se llama a la funcion que comprueba si todos los campos de las cuentas estan llenos
        if(Centinela)
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

            QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
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
    }
}

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
        if(SumaFila!=SumaColumna)
        {
            iguales = false;
        }
    }
    /*          Se coloca como no editable la última celda      */
    QTableWidgetItem *Valor = new QTableWidgetItem;
    Valor->setFlags(Valor->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(filas,columnas,Valor);
    //
    int cantidad = tableWidget->rowCount();
    ItemsNoEditable(tableWidget,0,inicio-1,cantidad-1);
}

void MainWindow::RestaurarCeldas()//Slot que permite restaurar el titulo de las cuentas en las celdas
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

void MainWindow::ModificarCuenta()//Slot que permite habilitar la edicion de una cuenta una vez agregada
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

bool MainWindow::ComprobarCuentas()//Se verifica que las lineas de texto y spin box de todas las cuentas no esten vacios
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

/***        Funcion que obtiene el nombre las cuentas a traves de los lineeidt y los retorna en una lista de string     ***/
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

/***        Funcion que obtiene los inicios/fin de las cuentas y las retorna como entero en una lista
                si la oopcion es cero crea la lista por el inicio, de lo contrario la crea por el fin   ***/
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

void MainWindow::CalcularAn(QTableWidget *tw,QTableWidget *nuevaTabla,QTableWidget *tablaOriginal,int count,bool endogena)//Funcion para calcular el Coeficiente Tecnico Horizontal (An)
{
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
                    value = Separador(tw->item(count-1,i),true);
                    value = QString::number(value.toDouble(),'f',precission);
                    total=value.toDouble();
                }
                QString values = Separador(tw->item(j,i),true);
                values = QString::number(values.toDouble(),'f',precission);
                double valor=values.toDouble();
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

int MainWindow::ObtenerIndice(QString text)//Funcion para obtener el indice de una pestaña buscada por un nombre dado
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

void MainWindow::CrearTablaVacia(int contador, QTableWidget *tw)//Funcion para crear una tabla vacia
{
    for(int k=0;k<contador-1;k++)
    {
        tw->insertRow(k);
        tw->insertColumn(k);
    }
}

/*          Funcion para crear una tabla vacia, específicamente para los encadenamientos        */
void MainWindow::crearTablaVaciaEncadenamiento(int filas, QTableWidget *tw,int columnas)
{
    for(int j=0;j<columnas;j++)
    {
        tw->insertColumn(0);
    }
    for(int k=0;k<filas;k++)
    {
        tw->insertRow(k);
    }
}

int MainWindow::contarElementosMap(QMap<QString,QStringList> diccionario)//Funcion para contar los elementos en el map o diccionario
{
    int contador=0;
    foreach(QString key,diccionario.keys())
    {
        contador+=diccionario[key].count();
    }
    return contador;
}

/*Funcion para agregar los componentes y cuentas a partir de la matriz endogena-endogena*/
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

/*       Funcion para volver la celda(0,0) no editable     */
void MainWindow::noEditColZero(QTableWidget *tw)
{
    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
    tw->setItem(0,0,ValoraInsertar);
}

/*          Funcion para colocar los titulos de las cuentas         */
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

/*                      Funcion para agregar/quitar el separador de miles y la coma en las tablas           */
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

/* Funcion estandar para hacer algunas celdas no editables debido a que son dificiles de manipular(por motivos de colocado y borrado dinamico)*/
void MainWindow::ItemsNoEditable(QTableWidget *tw,int inicio,int fin,int col)
{
    noEditColZero(tw);
    for(int i=inicio;i<fin;i++)
    {
        QTableWidgetItem *ValoraInsertarFila = new QTableWidgetItem;
        ValoraInsertarFila->setFlags(ValoraInsertarFila->flags() ^ Qt::ItemIsEditable);
        tw->setItem(i,col,ValoraInsertarFila);
        QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem;
        ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
        tw->setItem(col,i,ValoraInsertarColumna);

    }
}

/*          Funcion para agregar el estilo de una celda en negrita(letra blanca) con fondo de color azul (Cuenta)       */
void MainWindow::CellStyle(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(53,140,203));
    ti->setTextColor(Qt::white);
    QFont font;
    font.setBold(true);
    ti->setFont(font);
}

/*          Funcion para agregar el estilo de una celda con fondo de color gris (Componente)       */
void MainWindow::CellStyleComponente(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(221,227,230));
}

/*              Funcion para obtener las cuentas de la parte endogena        */
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
void MainWindow::slotCoeficienteVertical()
{
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
}

void MainWindow::slotCoeficienteHorizontal()
{
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
        QString STotal = Separador(tw->item(i,count-1),true);
        double total=STotal.toDouble();//Se obtiene el total de esa columna
        for(int j=0;j<count-1;j++)
        {
            if(i!=0 && j!=0)
            {
                QString value = Separador(tw->item(i,j),true);
                double valor=value.toDouble();
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
                value = Separador(ValoraInsertar,false);
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
}

//FH_002
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

void MainWindow::slotCloseExogena()
{
    formVariablesExogenas->close();
}

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

void MainWindow::slotAgregarExogena()
{
    actionVariableExogena.setDisabled(true);//Se deshabilita la opcion de agregar variables exogenas
    QString nombre_cuenta=stackVE->comboAccount->currentText();//Se obtiene el nombre de la cuenta seleccionado
    QListWidget *lw=new QListWidget;
    //lw=stackVE->veWidget->accounListWidget;
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

void MainWindow::slotFinalizarExogena()
{
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
                    QString value = Separador(tablaPPAL->item(i,j),true);
                    double valor=value.toDouble();
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
                    tablaEE->setItem(i,j,ValoraInsertar);
                }

             }
        }

        /***                    Se acomodan los componentes de las cuentas exogenas                 ***/
        int cantidad =tablaEE->rowCount();
        foreach(QString key,diccCuentasExogenas.keys())
        {
            foreach(QString key2,diccCuentasExogenas[key])
            {
                for(int i=2;i<cantidad;i++)
                {
                    QString cuenta=tablaEE->item(1,i)->text();
                    QString componente =tablaEE->item(2,i)->text();
                    if(key==cuenta and key2==componente)
                    {
                        QList<QString> fila;
                        fila=llenarLista(fila,tablaEE,i,1);
                        tablaEE->removeRow(i-1);
                        tablaEE->insertRow(tablaEE->rowCount());
                        insertRowExogena(fila,tablaEE,1);
                        fila.clear();

                        QList<QString> columna;
                        columna=llenarLista(columna,tablaEE,i,0);
                        tablaEE->removeColumn(i-1);
                        tablaEE->insertColumn(tablaEE->columnCount());
                        insertRowExogena(columna,tablaEE,0);
                        columna.clear();
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

        CalcularTotales(tablaEE,2,var);
        setEndogenaExogenaCell(tablaEE,inicioExogena,elementos,true);

        //Se crea la nueva pestaña
        tabWidget->addTab(new QWidget,"Tipo de Variable");
        int indice=ObtenerIndice("Tipo de Variable");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(tablaEE);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        formVariablesExogenas->close();

        /*                  Se crea la pestaña endogena-endogena            */
        tabWidget->addTab(new QWidget,"Endogena-Endogena");
        int indiceEndogeno=ObtenerIndice("Endogena-Endogena");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutEndogeno = new QHBoxLayout;
        layoutEndogeno->addWidget(matrizEndogena);
        QWidget *widgetEndogeno = tabWidget->widget(indiceEndogeno);
        widgetEndogeno->setLayout(layoutEndogeno);//Se añade el widget y layout a la pestaña creada

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
        Encadenamientos.setEnabled(true);
        connect(&actionEncadenamiento,SIGNAL(triggered()),this,SLOT(slotEncadenamientos()));
        actionEncadenamiento.setEnabled(true);
        //Clasificador de Cuentas
        connect(&actionClasificarCuentas,SIGNAL(triggered()),this,SLOT(slotClasificarCuentas()));
        actionClasificarCuentas.setEnabled(true);

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

    }
    else
    {
        QMessageBox::warning(this,"Alerta","No Agregó ninguna cuenta");
    }
}

//FH_003
/***        Slot para calcular el coeficiente tecnico vertical de la matriz endogena/exogena      ***/
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
    tabWidget->removeTab(indice);
    crearMatrizEndogena(tablaAn);
}

void MainWindow::slotMa()
{
    QTableWidget *tw = findChild<QTableWidget *>("MatrizAn");
    restarIdentidadAn(tw);
}


void MainWindow::loadMatrizExogena()
{

}

/***     Funcion para retornar todos los componentes en una lista     ***/
QStringList MainWindow::ObtenerComponentes(QTableWidget *tw)
{
    QStringList MiLista;
    int contador=tw->rowCount();
    for(int i=1;i<contador-1;i++)
    {
        MiLista.append(tw->item(0,i)->text());
    }
    return MiLista;
}


/***        Funcion que permite llenar una lista con los elementos en un intervalo dado(fila o columna)         ***/
QList<QString> MainWindow::llenarLista(QList<QString> lista,QTableWidget *tw,int valor,int opcion)
{
    int cantidad = tw->rowCount();
    for(int i=0;i<cantidad;i++)
    {
        if(opcion==1)
        {
            lista.append(tw->item(valor,i)->text());
        }
        else
        {
            lista.append(tw->item(i,valor)->text());
        }
    }
    return lista;
}

/***        Funcion que escribe en una columna o fila con la lista dada              ***/
void MainWindow::insertRowExogena(QList<QString> lista,QTableWidget *tw,int opcion)
{
    for(int i=0;i<tw->rowCount();i++)
    {
        QTableWidgetItem *twi =new QTableWidgetItem;
        twi->setText(lista[i]);
        twi->setFlags(twi->flags() ^ Qt::ItemIsEditable);
        int fin=tw->rowCount();
        if(opcion==1)
        {
            tw->setItem(fin-1,i,twi);
        }
        else
        {
            tw->setItem(i,fin-1,twi);
        }
    }
}

/***        Funcion que permite insertar, alinear y combinar las celdas con los titulos endogena/exogena        ***/
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

/*              Funcion que crea la matriz endogena-endogena        */
void MainWindow::crearMatrizEndogena(QTableWidget *tw)
{
    int cantidad=tw->rowCount();
    for(int i=0;i<cantidad;i++)
    {
        for(int j=0;j<cantidad;j++)
        {
            if(i>=2 && j>=2)
            {
                double valor=tw->item(i,j)->text().toDouble();
                MatrizEndogenaEndogena[i-2][j-2]=valor;
            }

         }
    }
}

/*          Funcion que determina los Multiplicadores de Leontief       */
void MainWindow::restarIdentidadAn(QTableWidget *tw)
{
    int cantidad=tw->rowCount()-1;
    MatrixXd A(cantidad-1,cantidad-1);
    MatrixXd ident = MatrixXd::Identity(cantidad-1,cantidad-1);
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            A(i,j) = ident(i,j)-MatrizEndogenaEndogena[i][j];
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
        tabWidget->addTab(new QWidget,"Ma");
        int indice=ObtenerIndice("Ma");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(tablaMa);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada

        opcionMa = 1;
        tabWidget->removeTab(indice);
    }
}

/*          Funcion que crea un diccionario con cuenta/cantidad de veces que se repiten para el espacio de las celdas          */
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

/*              Crea una lista de las cuentas endogenas          s*/
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

/*              Crea una lista de las cuentas exogenas          */
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

/*              Permite crear los espacios en las celdas de las cuentas en la matriz endogena          */
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

/*          obtiene un diccionario de cuentas/componentes de la matriz endogena/endogena         */
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

/*          Funcion para agregar el estilo de una celda en negrita(letras blancas) con fondo de color gris oscuro (endogéna-exogéna)       */
void MainWindow::CellStyleExEn(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(110,110,110));
    ti->setTextColor(Qt::white);
    QFont font;
    font.setBold(true);
    ti->setFont(font);
}

/*      Funcion que determina los totales de la matriz end-end y end-exog       */
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

void MainWindow::tableItem(QTableWidget *tw, int inicio, int fin, QString texto)
{
    for(int i=inicio;i<fin;i++)
    {
        QTableWidgetItem *itemFila = new QTableWidgetItem(texto);
        itemFila->setFlags(itemFila->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *itemColumna = new QTableWidgetItem(texto);
        itemColumna->setFlags(itemColumna->flags() ^ Qt::ItemIsEditable);
        tw->setItem(0,i,itemFila);
        tw->setItem(i,0,itemColumna);
    }
}

/*      Funcion que crea un vector con el total de las cuentas      */
void MainWindow::calcularTotalCuentas(QTableWidget *tw)
{
    int cantidad = tw->rowCount();
    for(int i = 3;i<cantidad-1;i++)
    {
        QString cuenta = tw->item(i,1)->text();
        QString value = Separador(tw->item(i,cantidad-1),true);
        double total = value.toDouble();
        if(totalCuentas.contains(cuenta))
        {
            totalCuentas[cuenta] += total;
        }
        else
        {
            totalCuentas.insert(cuenta,total);
        }
    }
    qDebug()<<"total de las cuentas"<<totalCuentas;
    estimarVectorPonderacion();
}

/*      Funcion que calcula el vector ponderacion       */
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
    qDebug()<<"Vector Ponderacion"<<Vpond;
}


//FH_004
/*                      Funcion para crear la ventana de los encadenamientos                     */
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
        buttonAgregar->setText("Agregar");
        buttonAgregar->setFixedWidth(130);
        buttonAgregar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonCancelar = new QPushButton;
        buttonCancelar->setObjectName("CancelarEncadenamiento");//Se le asigna nombre al objeto
        buttonCancelar->setText("Cancelar");
        buttonCancelar->setFixedWidth(130);
        buttonCancelar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonVer = new QPushButton;
        buttonVer->setObjectName("VerEncadenamiento");//Se le asigna nombre al objeto
        buttonVer->setText("Ver");
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

void MainWindow::slotCloseEncadenamiento()
{
    formEncadenamientos->close();
}


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
            QWidget *widget = tabWidget->widget(indice);
            widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
            formEncadenamientos->close();
            tabWidget->setCurrentIndex(indice);

        }
        else if (opcionCuentaEncadenamientos==2)//opcion para encadenar por la matriz endogena-endogena
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
            crearMatrizEncadenamientoEndogena(tw,enTable);//Se llama a la funcion que realiza todo el procedimiento
            tabWidget->addTab(new QWidget,QString("Encadenamiento %1").arg(cantidadEncadenamientos));
            int indice=ObtenerIndice(QString("Encadenamiento %1").arg(cantidadEncadenamientos));//Se obtiene el indice de la pestaña
            cantidadEncadenamientos++;
            QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
            layoutCentralWidget->addWidget(enTable);
            QWidget *widget = tabWidget->widget(indice);
            widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
            formEncadenamientos->close();
            tabWidget->setCurrentIndex(indice);
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

/*          Funcion para crear la tabla con los encadenamientos         */
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
    crearTablaVaciaEncadenamiento(elementos,enTable);
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
                                    EncadenamientoAtras = tw->item(k,j)->text().toDouble();//Suma Columna(Encadenamiento hacia atras)
                                    EncadenamientoAdelante = tw->item(j,k)->text().toDouble();//Suma Fila(Encadenamiento hacia adelante)
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
    encademientosStyle(encAtras);
    QTableWidgetItem *encAdelante = new QTableWidgetItem("Encadenamiento Parcial\nhacia adelante");
    encademientosStyle(encAdelante);
    enTable->setItem(0,2,encAtras);
    enTable->setItem(0,3,encAdelante);
    noEditColZero(enTable);
    //Se agregan las cuentas y sus componentes
    cuentacomponentesEncadenamiento(enTable,elementos);
    //Se agregan los totales
    calcularTotalesEncadenamientos(enTable);
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

/*          Funcion para crear  los encadenamientos de toda la matrix endógena-endógena     */
void MainWindow::crearMatrizEncadenamientoEndogena(QTableWidget *tw,QTableWidget *enTable)
{
    int countEndogena = tw->rowCount();
    crearTablaVaciaEncadenamiento(countEndogena-2,enTable);
    int columna=0;
    for(int i=2;i<countEndogena;i++)
    {
        double sumaColumna = 0;
        double sumaFila = 0;
        for(int j=2;j<countEndogena;j++)
        {
            double EncadenamientoAtras = tw->item(j,i)->text().toDouble();//Suma Columna(Encadenamiento hacia atras)
            sumaColumna+=EncadenamientoAtras;
            double EncadenamientoAdelante = tw->item(i,j)->text().toDouble();//Suma Fila(Encadenamiento hacia adelante)
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
        columna++;
    }
    //Se agregan los titulos
    enTable->insertRow(0);
    QTableWidgetItem *encAtras = new QTableWidgetItem("Encadenamiento Parcial\nhacia atrás");
    encademientosStyle(encAtras);
    QTableWidgetItem *encAdelante = new QTableWidgetItem("Encadenamiento Parcial\nhacia adelante");
    encademientosStyle(encAdelante);
    enTable->setItem(0,2,encAtras);
    enTable->setItem(0,3,encAdelante);
    noEditColZero(enTable);
    //Se agregan las cuentas y sus componentes
    cuentacomponentesResultado(enTable,countEndogena-1);
    //Se agregan los totales
    calcularTotalesEncadenamientos(enTable);
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

/*          Funcion para agregar los estilos de la tabla de encadenamientos     */
void MainWindow::encademientosStyle(QTableWidgetItem *ti)
{
    QFont font;
    font.setBold(true);
    ti->setFont(font);
    ti->setFlags(ti->flags() ^ Qt::ItemIsEditable);
    ti->setTextAlignment(Qt::AlignCenter);
}

/*          Funcion para agregar los totales en la matriz de encadenamientos        */
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
        QTableWidgetItem *zero = new QTableWidgetItem;
        zero->setFlags(zero->flags() ^ Qt::ItemIsEditable);
        tw->setItem(count,0,zero);
        QTableWidgetItem *titulo = new QTableWidgetItem(QString("Encadenamiento Parcial %1, Total").arg(accName.at(k)));
        encademientosStyle(titulo);
        tw->setItem(count,1,titulo);
        QTableWidgetItem *totalAtras = new QTableWidgetItem(QString::number(sumaAtras,'f',precission));
        QString value = Separador(totalAtras,false);
        totalAtras->setText(value);
        encademientosStyle(totalAtras);
        QTableWidgetItem *totalAdelante = new QTableWidgetItem(QString::number(sumaAdelante,'f',precission));
        value = Separador(totalAdelante,false);
        totalAdelante->setText(value);
        encademientosStyle(totalAdelante);
        tw->setItem(count,2,totalAtras);
        tw->setItem(count,3,totalAdelante);
    }
}

//Clasificador de cuentas
void MainWindow::slotClasificarCuentas()
{
    QTableWidget *An = findChild<QTableWidget *>("MatrizAn");
    QTableWidget *Ma = findChild<QTableWidget *>("MatrizMa");
    int count = An->rowCount()-1;
    QTableWidget *CC = new QTableWidget;
    CC->setObjectName("Clasificador de Cuentas");
    crearTablaVaciaEncadenamiento(count,CC,8);
    cuentacomponentesResultado(CC,count-1,true);
    QVector<double> vectorFila;
    QVector<double> vectorColumna;
    obtenerUiUj(An,vectorFila,vectorColumna);
    calcularClasificador(CC,vectorFila,vectorColumna);
    vectorFila.clear();
    vectorColumna.clear();
    obtenerUiUj(Ma,vectorFila,vectorColumna);
    calcularClasificador(CC,vectorFila,vectorColumna,5);
    CC->resizeColumnsToContents();//Ajuste de Columnas
    agregarPrimeraCelda(CC);

    tabWidget->addTab(new QWidget,"Clasificador");
    int indice=ObtenerIndice("Clasificador");
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(CC);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
    actionClasificarCuentas.setDisabled(true);
    tabWidget->setCurrentIndex(indice);
}

/*      Funcion que calcular los Ui y Uj para los clasificadores    */
void MainWindow::obtenerUiUj(QTableWidget *tw, QVector<double> &ui, QVector<double> &uj)
{
    int contador = tw->rowCount();
    double totalFila = 0;
    double totalColumna = 0;
    QVector<double> vectorFila;
    QVector<double> vectorColumna;
    for(int i=2;i<contador;i++)
    {
        double sumaFila = 0;
        double sumaColumna = 0;
        for(int j=2;j<contador;j++)
        {
            QString itemFila = Separador(tw->item(i,j),true);
            QString itemColumna = Separador(tw->item(j,i),true);
            double fila = itemFila.toDouble();
            double columna = itemColumna.toDouble();
            sumaFila+=fila;
            sumaColumna+=columna;
            totalFila+=fila;
            totalColumna+=columna;
        }
        vectorFila.append(sumaFila);
        vectorColumna.append(sumaColumna);
    }
    int cantidad = vectorFila.count();
    for(int i=0;i<cantidad;i++)
    {
        double fila = vectorFila.at(i)/totalFila;
        ui.append(fila);
        double columna = vectorColumna.at(i)/totalColumna;
        uj.append(columna);
    }
}

/*          Funcion que hace los cálculos de los clasificadores            */
void MainWindow::calcularClasificador(QTableWidget *tw, QVector<double> ui, QVector<double> uj,int init)
{
    int count = tw->rowCount()-1;
    //Fuente Negrita
    QFont font;
    font.setBold(true);
    //Titulos Ui, Uj y Tipo de Cuenta
    QTableWidgetItem *uiItem = new QTableWidgetItem("Ui");
    uiItem->setFlags(uiItem->flags() ^ Qt::ItemIsEditable);
    uiItem->setFont(font);
    tw->setItem(0,init,uiItem);
    QTableWidgetItem *ujItem = new QTableWidgetItem("Uj");
    ujItem->setFlags(ujItem->flags() ^ Qt::ItemIsEditable);
    ujItem->setFont(font);
    tw->setItem(0,init+1,ujItem);
    QTableWidgetItem *tcItem = new QTableWidgetItem("Tipo de Cuenta");
    tcItem->setFlags(tcItem->flags() ^ Qt::ItemIsEditable);
    tcItem->setFont(font);
    tw->setItem(0,init+2,tcItem);
    for(int i=0;i<count;i++)
    {
        QTableWidgetItem *vFila = new QTableWidgetItem(QString::number(ui.at(i),'f',precission));
        vFila->setFlags(vFila->flags() ^ Qt::ItemIsEditable);
        QString itemFila = Separador(vFila,false);
        vFila->setText(itemFila);
        tw->setItem(i+1,init,vFila);
        QTableWidgetItem *vColumna = new QTableWidgetItem(QString::number(uj.at(i),'f',precission));
        vColumna->setFlags(vColumna->flags() ^ Qt::ItemIsEditable);
        QString itemColumna = Separador(vColumna,false);
        vColumna->setText(itemColumna);
        tw->setItem(i+1,init+1,vColumna);
        QTableWidgetItem *tipo = new QTableWidgetItem;
        tipo->setFlags(tipo->flags() ^ Qt::ItemIsEditable);
        //Se determina que tipo de cuenta es
        if(ui.at(i)<1 and uj.at(i)<1)
        {
            tipo->setText("Independiente");
        }
        else if(ui.at(i)>1 and uj.at(i)<1)
        {
            tipo->setText("Impulsor de Economía");
        }
        else if(ui.at(i)<1 and uj.at(i)>1)
        {
            tipo->setText("Base");
        }
        else if(ui.at(i)>1 and uj.at(i)>1)
        {
            tipo->setText("Clave");
        }
        tw->setItem(i+1,init+2,tipo);
    }
}

void MainWindow::agregarPrimeraCelda(QTableWidget *tw)
{
    tw->insertRow(0);
    //Se colocan no editables la celda 0 y 1
    noEditColZero(tw);
    QTableWidgetItem *one = new QTableWidgetItem;
    one->setFlags(one->flags() ^ Qt::ItemIsEditable);
    tw->setItem(0,1,one);
    for(int i=0;i<3;i++)
    {
        QTableWidgetItem *cAn = new QTableWidgetItem("Clasificador por An");
        cAn->setTextAlignment(Qt::AlignCenter);
        cAn->setFlags(cAn->flags() ^ Qt::ItemIsEditable);
        CellStyleExEn(cAn);
        tw->setItem(0,i+2,cAn);
        QTableWidgetItem *cMa = new QTableWidgetItem("Clasificador por Ma");
        cMa->setTextAlignment(Qt::AlignCenter);
        cMa->setFlags(cMa->flags() ^ Qt::ItemIsEditable);
        CellStyleExEn(cMa);
        tw->setItem(0,5+i,cMa);
    }
    tw->setSpan(0,2,1,3);
    tw->setSpan(0,5,1,3);
}

//FH_005
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
/*          Funcion que realiza las operaciones en el escenario         */
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

        tabWidget->addTab(new QWidget,QString("Resultado C %1").arg(cantidadEscenarios));
        int indice=ObtenerIndice(QString("Resultado C %1").arg(cantidadEscenarios));

        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(resultadoEscenario);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        tabWidget->setCurrentIndex(indice);

        cantidadEscenarios++;
        actionModeloClasico.setEnabled(true);
        if(cantidadEscenarios>2)
        {
            actionCompararResultados.setEnabled(true);
            connect(&actionCompararResultados,SIGNAL(triggered()),this,SLOT(slotCompararResultados()));
        }
    }
}

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

/*          funcion que calcula el resultado de multiplicar Ma por el subtotal del escenario y lo retorna en un vector      */
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

    tabWidget->addTab(new QWidget,QString("Comparacion %1").arg(cantidadResultados));
    int indice=ObtenerIndice(QString("Comparacion %1").arg(cantidadResultados));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tablaComparar);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);

    formCompararResultados->close();
    tabWidget->setCurrentIndex(indice);
    cantidadResultados++;
}

void MainWindow::crearTablaComparar(QTableWidget *to, QTableWidget *tw)
{
    int count = to->rowCount();
    int col = to->columnCount();
    to->insertColumn(col);
    to->insertColumn(col);
    for(int i=0;i<count;i++)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(tw->item(i,2)->text());
        item1->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *item2 = new QTableWidgetItem(tw->item(i,3)->text());
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        if(i==0)
        {
            QFont font;
            font.setBold(true);
            item1->setFont(font);
            item2->setFont(font);
        }
        to->setItem(i,col,item1);
        to->setItem(i,col+1,item2);
    }
    to->resizeColumnsToContents();
    to->resizeRowsToContents();
}

/*      Funcion para colocar cuenta/componentes en las tablas de modelo clasico, resultados y comparar resultados*/
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
void MainWindow::slotModeloNoClasico()
{
    if(opcionMa == 0)
    {
        slotMa();
    }
    obtenerMatrizExgEnd();
    actionModeloNoClasico.setDisabled(true);
}

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
    calcularMatrizExgEnd(MatrizExgEnd);
    ctvMatrizExgEnd(MatrizExgEnd,Bn);
    titlespanMatrizExgEnd(Bn);

    tabWidget->addTab(new QWidget,"Bn");
    int indice=ObtenerIndice("Bn");
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(Bn);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->removeTab(indice);

    estimarMb(Bn,Mb);
    calcularSubtotalEndExg();
    opcionMb++;
}
/*      Funcion para crear la Matriz Exógena Endógena*/
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

/*      Funcion para calcular los totales de la matriz Exógena-Endógena     */
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

void MainWindow::ctvMatrizExgEnd(QTableWidget *MatrizExgEnd,QTableWidget *Bn)
{
    //Calcular CTV
    int fila = MatrizExgEnd->rowCount()-1;
    int columna = MatrizExgEnd->columnCount();
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
    int totalLocal = tw->rowCount()-1;
    for(int i = 0; i<columna; i++)
    {

        QString value;
        double total;
        for(int j = 0;j<fila;j++)
        {
            if(i>=2 and j>=2)
            {
                value = Separador(tw->item(totalLocal,i),true);
                total = value.toDouble();
                double valoraInsertar;
                if(total==0)
                {
                    valoraInsertar=0;
                }
                else
                {
                    QString valor = Separador(MatrizExgEnd->item(j,i),true);
                    valoraInsertar = valor.toDouble();
                    valoraInsertar /= total;
                }
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

/*      Funcion para colocar los espacios de los títulos de las cuentas*/
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

void MainWindow::estimarMb(QTableWidget *Bn,QTableWidget *Mb)
{
    int fila = Bn->rowCount();
    int columna = Bn->columnCount();
    QTableWidget *Ma = findChild<QTableWidget *>("MatrizMa");
    int count = Ma->rowCount();
    MatrixXd Mbn(fila-2,columna-2);
    MatrixXd Mma(count-2,count-2);
    for(int i=2;i<columna;i++)
    {
        for(int j=2;j<fila;j++)
        {
            QString valueb = Separador(Bn->item(j,i),true);
            double doubleb = valueb.toDouble();
            Mbn(j-2,i-2) = doubleb;
        }
    }
    for(int i=2;i<count;i++)
    {
        for(int j=2;j<count;j++)
        {
            QString valuem = Separador(Ma->item(i,j),true);
            double doublem = valuem.toDouble();
            Mma(i-2,j-2) = doublem;
        }
    }
    MatrixMb = Mbn*Mma;
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
    tabWidget->addTab(new QWidget,"Mb");
    int indice=ObtenerIndice("Mb");
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(Mb);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->removeTab(indice);
}

void MainWindow::calcularEscenarioNC()
{
    calcularEscenario(false);
}

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

        tabWidget->addTab(new QWidget,QString("Resultado NC %1").arg(cantidadMNC));
        int indice=ObtenerIndice(QString("Resultado NC %1").arg(cantidadMNC));

        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(resultadoEscenario);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        tabWidget->setCurrentIndex(indice);

        cantidadMNC++;
        actionModeloNoClasico.setEnabled(true);
        if(cantidadMNC>2)
        {
            actionCompararResultadosMNC.setEnabled(true);
            connect(&actionCompararResultadosMNC,SIGNAL(triggered()),this,SLOT(slotCompararResultadosMNC()));
        }
    }
}

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

    tabWidget->addTab(new QWidget,QString("Comparacion MNC %1").arg(cantidadResultadosMNC));
    int indice=ObtenerIndice(QString("Comparacion MNC %1").arg(cantidadResultadosMNC));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tablaComparar);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);

    formCompararMNC->close();
    tabWidget->setCurrentIndex(indice);
    cantidadResultadosMNC++;
}


//FH_007
void MainWindow::slotPHCIncidencia100()
{
    if(opcionMAT == 0)
    {
        calcularMaT();
    }
    QTableWidget *MatrizMi = new QTableWidget;
    MatrizMi->setObjectName("PHC100");
    calcularPHCIncidencia100(MatrizMi);

    tabWidget->addTab(new QWidget,"PHC100");
    int indice=ObtenerIndice("PHC100");

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MatrizMi);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    actionPHClasicoIncidencia100.setDisabled(true);
}

/*          Funcion que determina Ma Transpuesta o Ma^T        */
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
    tabWidget->addTab(new QWidget,"Ma^T");
    int indice=ObtenerIndice("Ma^T");

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MaT);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->removeTab(indice);
    opcionMAT++;
}

/*          Calcula la incidencia al 100%       */
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

    tabWidget->addTab(new QWidget,QString("PHCI %1").arg(cantidadPHCindidenciaiCuenta));
    int indice=ObtenerIndice(QString("PHCI %1").arg(cantidadPHCindidenciaiCuenta));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MatrizIC);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    cantidadPHCindidenciaiCuenta++;
}

/*          Funcion para calcular la incidencia "i" en los precios homogéneos clásico (cuenta)       */
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

void MainWindow::slotCalcularPHCIncidenciaiComponente()
{
    QTableWidget *tw = FI->ui->TableIncidencia;

    QTableWidget *MatrizIComp = new QTableWidget;
    MatrizIComp->setObjectName(QString("PHCIcomponente %1").arg(cantidadPHCindidenciaiComponente));
    calcularPHCIncidencia100(MatrizIComp);
    calcularPHCIncidenciaIComponente(MatrizIComp,tw);

    tabWidget->addTab(new QWidget,QString("PHCIc %1").arg(cantidadPHCindidenciaiComponente));
    int indice=ObtenerIndice(QString("PHCIc %1").arg(cantidadPHCindidenciaiComponente));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MatrizIComp);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    cantidadPHCindidenciaiComponente++;
}

/*      Funcion para calcular la incidencia "i" en los precios homogéneos clásico (componente)      */
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
    tabWidget->addTab(new QWidget,"Mb^T");
    int indice=ObtenerIndice("Mb^T");

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MbT);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->removeTab(indice);
    opcionMBT++;
}

//FH_008
void MainWindow::slotPHNCIncidencia100()
{
    if(opcionMBT == 0)
    {
        calcularMbT();
    }
    QTableWidget *MatrizMi = new QTableWidget;
    MatrizMi->setObjectName("PHNC100");
    calcularPHNCIncidencia100(MatrizMi);

    tabWidget->addTab(new QWidget,"PHNC100");
    int indice=ObtenerIndice("PHNC100");

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MatrizMi);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    actionPHNoClasicoIncidencia100.setDisabled(true);
}

/*      Funcion para calcular la incidencia "i" en los precios homogéneos no clásico (cuenta)*/
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

    tabWidget->addTab(new QWidget,QString("PHNCI %1").arg(cantidadPHNCindidenciaiCuenta));
    int indice=ObtenerIndice(QString("PHNCI %1").arg(cantidadPHNCindidenciaiCuenta));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MatrizIC);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    cantidadPHNCindidenciaiCuenta++;
}

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

void MainWindow::slotCalcularPHNCIncidenciaiComponente()
{
    QTableWidget *tw = FI->ui->TableIncidencia;

    QTableWidget *MatrizIComp = new QTableWidget;
    MatrizIComp->setObjectName(QString("PHNCIcomponente %1").arg(cantidadPHNCindidenciaiComponente));
    calcularPHNCIncidencia100(MatrizIComp);
    calcularPHCIncidenciaIComponente(MatrizIComp,tw);

    tabWidget->addTab(new QWidget,QString("PHNCIc %1").arg(cantidadPHNCindidenciaiComponente));
    int indice=ObtenerIndice(QString("PHNCIc %1").arg(cantidadPHNCindidenciaiComponente));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(MatrizIComp);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    cantidadPHNCindidenciaiComponente++;
}

//FH_009
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

void MainWindow::slotCloseformPNH()
{
    formPreciosNoHomogeneos->close();
}

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

/*      Funcion para calcular el vector Send, que se utiliza para crear una matriz identidad con una diagonal conformada
                                    por los valores de un componente previamente seleccionado           */
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
        tabWidget->addTab(new QWidget,QString("PNH100 %1").arg(cantidadPNHincidencia100));
        int indice=ObtenerIndice(QString("PNH100 %1").arg(cantidadPNHincidencia100));
        QHBoxLayout * layoutCentralWidget3 = new QHBoxLayout;
        layoutCentralWidget3->addWidget(tw);
        QWidget *widget3 = tabWidget->widget(indice);
        widget3->setLayout(layoutCentralWidget3);
        tabWidget->setCurrentIndex(indice);
        cantidadPNHincidencia100++;
        opcionPNHT = 1;
    }
}

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

    tabWidget->addTab(new QWidget,QString("PNHI %1").arg(cantidadPNHincidenciaiCuenta));
    int indice=ObtenerIndice(QString("PNHI %1").arg(cantidadPNHincidenciaiCuenta));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(PNHI);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    cantidadPNHincidenciaiCuenta++;
    FI->close();
}

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

    tabWidget->addTab(new QWidget,QString("PNHIc %1").arg(cantidadPNHincidenciaiComponente));
    int indice=ObtenerIndice(QString("PNHIc %1").arg(cantidadPNHincidenciaiComponente));

    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(PNHIc);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);
    tabWidget->setCurrentIndex(indice);
    cantidadPNHincidenciaiComponente++;
    FI->close();
}

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
                tabWidget->addTab(new QWidget,QString("Seleccion %1").arg(cantidadSelecciones));
                int indice=ObtenerIndice(QString("Seleccion %1").arg(cantidadSelecciones));
                QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
                layoutCentralWidget->addWidget(nuevaTabla);
                QWidget *widget = tabWidget->widget(indice);
                widget->setLayout(layoutCentralWidget);
                tabWidget->setCurrentIndex(indice);
                cantidadSelecciones++;
            }
        }
    }
}

/*          Funcion para agregar el span en los titulos de la mtriz seleccionada    */
void MainWindow::titleSeleccionar(QTableWidget *tw)
{
    QStringList CuentaFila;
    QStringList CuentaColumna;
    int fila = tw->rowCount();
    int columna = tw->columnCount();
    /*      Se crea una lista con las veces que se repiten cuentas en filas/columnas*/
    //Fila
    for(int i = 2;i<fila;i++)
    {
        CuentaFila.append(tw->item(i,0)->text());
    }
    //Columna
    for(int j = 2;j<columna;j++)
    {
        CuentaColumna.append(tw->item(0,j)->text());
    }
    /*      Se crea el span tomando en cuenta las veces que se repite una cuenta en las listas      */
    //Fila
    for(int i=2;i<fila-1;i++)
    {
        QString accName=tw->item(i,0)->text();
        if(CuentaFila.contains(accName))
        {
            int contar = CuentaFila.count(accName);
            tw->setSpan(i,0,contar,1);
            CuentaFila.removeAll(accName);
        }
        if(CuentaFila.isEmpty())
        {
            break;
        }
    }
    //Columna
    for(int j=2;j<columna-1;j++)
    {
        QString accName=tw->item(0,j)->text();
        if(CuentaColumna.contains(accName))
        {
            int contar = CuentaColumna.count(accName);
            tw->setSpan(0,j,1,contar);
            CuentaColumna.removeAll(accName);
        }
        if(CuentaColumna.isEmpty())
        {
            break;
        }
    }
}
