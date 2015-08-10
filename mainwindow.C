#include "mainwindow.H"
#include "accountwidget.H"
#include "stackvariablesexogenas.h"
#include "formexportmatrix.h"
#include <QDebug>

#define ARMA_DONT_PRINT_ERRORS
#include <armadillo>


using namespace arma;

void MainWindow::slotLoadMatrix()
{
    formLoadMatrix = new  FormLoadMatrix(this);
    formLoadMatrix->show();
    connect(formLoadMatrix, SIGNAL(formAccepted(QString,int,char)),
            this, SLOT(slotFormLoadMatrixAccepted(QString,int,char)));
}

void MainWindow::slotExportMatrix()
{

    if(opcionExportarMatriz == 0)
    {
        formExportMatriz = new FormExportMatrix(this);
        QHBoxLayout * layoutLateralWidget = new QHBoxLayout;
        QVBoxLayout * layoutCentralWidget = new QVBoxLayout;

        QLabel *label = new QLabel;
        label->setText("Seleccione una de las matrices");
        label->setStyleSheet("font-size:14;font-weight:bold;");
        layoutLateralWidget->addWidget(label);

        formExportMatriz->Exportcb = new QComboBox;
        formExportMatriz->Exportcb->setFixedWidth(150);
        QVBoxLayout *cbLayout = new QVBoxLayout;
        cbLayout->addWidget(formExportMatriz->Exportcb);
        QWidget *cbWidget = new QWidget;
        cbWidget->setLayout(cbLayout);

        QStringList list;
        list << "valor1" << "valor2" << "valor3";
        formExportMatriz->Exportcb->addItems(list);

        layoutLateralWidget->addWidget(cbWidget);

        QLabel *label2 = new QLabel;
        label2->setText("Archivo");
        formExportMatriz->ExportLine = new QLineEdit;
        //line->setObjectName("lineaCarga");
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


        /***        Se crean y personalizan los bottones para agregar, finalizar, deshacer y cancelar    ***/
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
        formExportMatriz->show();
    }

}
void MainWindow::closeEvent(QCloseEvent * event)
{
    QMessageBox msBox(QMessageBox::Question,"Alerta","¿Desea Salir?", QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"Si");
    if(msBox.exec()==QMessageBox::No)
    {
        event->ignore();
    }
}

void MainWindow::initGUI()
{
    createMenuBar();
    createCentralWidget();
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
    OpMatrices.setTitle("&Herramientas");

    actionCH.setText("Coeficientes &Horizontales");
    actionCH.setDisabled(true);
    OpMatrices.addAction(&actionCH);

    actionCV.setText("Coeficientes &Verticales");
    actionCV.setDisabled(true);
    OpMatrices.addAction(&actionCV);

    EndoExo.setTitle("Variables &Exogenas");

    actionVariableExogena.setText("Definir Variables &Exogenas");
    actionVariableExogena.setDisabled(true);
    EndoExo.addAction(&actionVariableExogena);

    actionAn.setText("Coeficientes &Horizontales");
    actionAn.setDisabled(true);
    EndoExo.addAction(&actionAn);

    actionLa.setText("Multiplicadores de &Leontief");
    actionLa.setDisabled(true);
    EndoExo.addAction(&actionLa);

    OpMatrices.addMenu(&EndoExo);

    actionEncadenamiento.setText("Encadenamientos");
    actionEncadenamiento.setDisabled(true);
    OpMatrices.addAction(&actionEncadenamiento);


    menuBar()->addMenu(&OpMatrices);
}

MainWindow::MainWindow()
    : actionLoadMatrix(this), actionExportMatrix(this), actionQuit(this),actionCH(this), actionCV(this),
      actionVariableExogena(this),actionAn(this),actionLa(this),actionEncadenamiento(this), formLoadMatrix(0)
{
    tabWidget = new QTabWidget;

    /*    Opcion de la cuenta exogena, 0 para decir que nos se selecciono ninguna, 1 que se seleccionaron algunas
                                    y 2 para decir que se seleccionaron todas*/
    opcionCuentaExogena = 0;
    opcionVentanaExogena = 0;
    opcionExportarMatriz = 0;

    initGUI();

    connect(&actionLoadMatrix, SIGNAL(triggered()), this,
            SLOT(slotLoadMatrix()));
    connect(&actionExportMatrix, SIGNAL(triggered()), this,
            SLOT(slotExportMatrix()));
    connect(&actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    
    showMaximized();
}

void MainWindow::slotFormLoadMatrixAccepted(const QString & filePath,
                                            int accountNumber, char sep)
{
    QString msg = "Archivo: " + filePath + "\nNúmero de cuentas: " +
                   QString().setNum(accountNumber) +
                   "\nSeparador: " + sep;

    csvFilePath = filePath;
    csvSeparator = sep;
    numAccounts = accountNumber;

    createMatrixCentralWidget();
}

void MainWindow::slotFormLoadMatrixClosed()
{
    disconnect(formLoadMatrix, SIGNAL(formAccepted(QString,int,char)),
               this, SLOT(slotFormLoadMatrixAccepted(QString,int,char)));
    formLoadMatrix = 0;
}

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
        buttonAgregar->setText("Agregar");
        buttonAgregar->setFixedWidth(130);
        buttonAgregar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonCancelar = new QPushButton;
        buttonCancelar->setObjectName("CancelarExogena");//Se le asigna nombre al objeto
        buttonCancelar->setText("Cancelar");
        buttonCancelar->setFixedWidth(130);
        buttonCancelar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonFinalizar = new QPushButton;
        buttonFinalizar->setObjectName("FinalizarExogena");//Se le asigna nombre al objeto
        buttonFinalizar->setText("Finalizar");
        buttonFinalizar->setFixedWidth(130);
        buttonFinalizar->setStyleSheet("background-color: #358ccb; color: #fff;"
                                 "font-weight: bold; height: 30px; border: none;"
                                 "border-radius: 5px; margin-top: 40px;");
        QPushButton * buttonDeshacer = new QPushButton;
        buttonDeshacer->setObjectName("DeshacerExogena");//Se le asigna nombre al objeto
        buttonDeshacer->setText("Deshacer");
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


void MainWindow::slotCoeficienteHorizontal()
{
    actionCH.setDisabled(true);
    tabWidget->addTab(new QWidget,"CT_Horizontal");
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");

    /*      Se eliminan la fila y columna (0,0) para los calculos*/
    insertremoveRowCol(tw,0,false);

    QTableWidget *CT_HorizontalTW = new QTableWidget;
    int count=tw->rowCount();
    CrearTablaVacia(count,CT_HorizontalTW);//Se crea una tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(CT_HorizontalTW);
    /*****      Se llena la tabla vacia con los valores de la tabla principal ****/

    CalcularAn(tw,CT_HorizontalTW,new QTableWidget,count,false);//Funcion para calcular el Coeficiente Tecnico Horizontal (An)

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

}

void MainWindow::slotCoeficienteVertical()
{
    actionCV.setDisabled(true);
    tabWidget->addTab(new QWidget,"CT_Vertical");
    QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");

    /*      Se eliminan la fila y columna (0,0) para los calculos*/
    insertremoveRowCol(tw,0,false);

    int count=tw->rowCount();
    QTableWidget *CT_VerticalTW = new QTableWidget;
    CrearTablaVacia(count,CT_VerticalTW); //Se Crea la tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(CT_VerticalTW);
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
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                CT_VerticalTW->setItem(i,j,ValoraInsertar);
            }
            /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
            else if((i==0 && j>0)||(j==0 && i>0))
            {
                QString value=tw->item(j,i)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                CT_VerticalTW->setItem(j,i,ValoraInsertar);
            }

         }
    }
    /*      Se agrega la columna y fila (0,0) y se insertan los titulos de las cuentas      */
    insertremoveRowCol(tw,0,true);
    insertremoveRowCol(CT_VerticalTW,0,true);
    setAccountTitle(tw);
    setAccountTitle(CT_VerticalTW);

    int indice=ObtenerIndice("CT_Vertical");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(CT_VerticalTW);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
}

void MainWindow::slotCloseExogena()
{
    formVariablesExogenas->close();
}

void MainWindow::slotDeshacerExogena()
{
    QMessageBox msBox(QMessageBox::Question,"Deshacer","¿Desea deshacer todos los cambios?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"Si");
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
    actionVariableExogena.setDisabled(true);//Se deshabilita la oipcion de agregar variables exogenas
    QString nombre_cuenta=stackVE->comboAccount->currentText();//Se obtiene el nombre de la cuenta seleccionado
    QListWidget *lw=new QListWidget;
    lw=stackVE->veWidget->accounListWidget;
    int index=stackVE->comboAccount->currentIndex();//Se obtiene el indice selecionado
    lw = findChild<QListWidget *>(QString("accountlist %1").arg(index + 1));//Se obtiene la lista seleccionada
    QStringList componentes_cuenta;

    if(nombre_cuenta!="Todas las Cuentas")
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
            opcionCuentaExogena=1;//Se establece un valor para la variable de la opcion
            diccCuentasExogenas.insert(nombre_cuenta,componentes_cuenta);
        }
    }
    else
    {
        int cantidad=stackVE->comboAccount->count();
        for(int i=0;i<cantidad;i++)
        {
            QListWidget *lw=new QListWidget;
            lw=stackVE->veWidget->accounListWidget;
            lw = findChild<QListWidget *>(QString("accountlist %1").arg(i + 1));//Se obtiene la lista seleccionada
            lw->setDisabled(true);
            opcionCuentaExogena=2;//Se establece un valor para la variable de la opcion
        }

    }

}

void MainWindow::slotFinalizarExogena()
{
    QTableWidget *tablaEE = new QTableWidget;
    tablaEE->setObjectName("TablaExogenaEndogena");
    QTableWidget *tablaPPAL = findChild<QTableWidget *>("TablaPrincipal");//Se carga la tabla principal
    insertremoveRowCol(tablaPPAL,0,false);
    int count=tablaPPAL->rowCount();
    CrearTablaVacia(count,tablaEE);//Se crea la tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tablaEE);
    if(opcionCuentaExogena==1)//Si seleccionaron componentes
    {

        int elementos = contarElementosMap();

        /*****      Se llena la tabla vacia con los valores de la tabla principal ****/
        for(int i=0;i<count-1;i++)
        {
            for(int j=0;j<count-1;j++)
            {
                if(i!=0 && j!=0)
                {
                    QString value = Separador(tablaPPAL->item(i,j),true);
                    double valor=value.toDouble();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                    value = Separador(ValoraInsertar,false);
                    ValoraInsertar->setText(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }
                /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
                else if((i==0 && j>0)||(j==0 && i>0))
                {
                    QString value=tablaPPAL->item(i,j)->text();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }

             }
        }

        /***                    Se acomodan los componentes de las cuentas exogenas                 ***/

        foreach(QString key,diccCuentasExogenas.keys())
        {
            int indiceCuenta=retornarIndiceCuenta(key);
            QSpinBox *SBinicio = findChild<QSpinBox *>(QString("accountstart %1").arg(indiceCuenta+1));
            QSpinBox *SBFin = findChild<QSpinBox *>(QString("accountend %1").arg(indiceCuenta+1));
            int inicio=SBinicio->text().toInt();
            int fin=SBFin->text().toInt();
            foreach(QString key2,diccCuentasExogenas[key])
            {
                for(int i=inicio;i<fin+1;i++)
                {
                    QString item=tablaEE->item(0,i)->text();
                    if(item==key2)
                    {
                        QList<QString> fila;
                        fila=llenarLista(fila,tablaEE,i,1);
                        tablaEE->removeRow(i);
                        tablaEE->insertRow(tablaEE->rowCount());
                        insertRowExogena(fila,tablaEE,1);
                        fila.clear();

                        QList<QString> columna;
                        columna=llenarLista(columna,tablaEE,i,0);
                        tablaEE->removeColumn(i);
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
        QTableWidgetItem *ValoraInsertar = new QTableWidgetItem("");
        ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
        matrizEndogena->setItem(0,0,ValoraInsertar);


        clonarTabla(tablaEE,matrizEndogena,inicioExogena);
        CalcularTotales(matrizEndogena,1);

        setEndogenaExogenaCell(tablaEE,inicioExogena,elementos,true);
        CalcularTotales(tablaEE,2);

        //Se crea la nueva pestaña
        tabWidget->addTab(new QWidget,"Endogena-Exogena");
        int indice=ObtenerIndice("Endogena-Exogena");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(tablaEE);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        formVariablesExogenas->close();
        connect(&actionAn,SIGNAL(triggered()),this,SLOT(slotAn()));
        actionAn.setEnabled(true);

        /*                  Se crea la pestaña endogena-endogena            */
        tabWidget->addTab(new QWidget,"Endogena-Endogena");
        int indiceEndogeno=ObtenerIndice("Endogena-Endogena");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutEndogeno = new QHBoxLayout;
        layoutEndogeno->addWidget(matrizEndogena);
        QWidget *widgetEndogeno = tabWidget->widget(indiceEndogeno);
        widgetEndogeno->setLayout(layoutEndogeno);//Se añade el widget y layout a la pestaña creada

    }
    else if(opcionCuentaExogena==2)//Si se seleccionaron todas las cuentas
    {

        /*****      Se llena la tabla vacia con los valores de la tabla principal ****/
        for(int i=0;i<count-1;i++)
        {
            for(int j=0;j<count-1;j++)
            {
                if(i!=0 && j!=0)
                {
                    QString value = Separador(tablaPPAL->item(i,j),true);
                    double valor=value.toDouble();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                    value = Separador(ValoraInsertar,false);
                    ValoraInsertar->setText(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }
                /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
                else if((i==0 && j>0)||(j==0 && i>0))
                {
                    QString value=tablaPPAL->item(i,j)->text();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }

             }
        }

        QTableWidget *matrizEndogena = new QTableWidget;
        matrizEndogena->setObjectName("MatrizEndogenaEndogena");
        CrearTablaVacia(count,matrizEndogena);
        QTableWidgetItem *ValoraInsertar = new QTableWidgetItem("");
        ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
        matrizEndogena->setItem(0,0,ValoraInsertar);


        clonarTabla(tablaEE,matrizEndogena,count);
        CalcularTotales(matrizEndogena,1);

        setEndogenaExogenaCell(tablaEE,count,0,false);
        CalcularTotales(tablaEE,2);

        //Se agrega la nueva pestaña
        tabWidget->addTab(new QWidget,"Endogena-Exogena");
        int indice=ObtenerIndice("Endogena-Exogena");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(tablaEE);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        formVariablesExogenas->close();
        connect(&actionAn,SIGNAL(triggered()),this,SLOT(slotAn()));
        actionAn.setEnabled(true);

        /*                  Se crea la pestaña endogena-endogena            */
        tabWidget->addTab(new QWidget,"Endogena-Endogena");
        int indiceEndogeno=ObtenerIndice("Endogena-Endogena");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutEndogeno = new QHBoxLayout;
        layoutEndogeno->addWidget(matrizEndogena);
        QWidget *widgetEndogeno = tabWidget->widget(indiceEndogeno);
        widgetEndogeno->setLayout(layoutEndogeno);//Se añade el widget y layout a la pestaña creada


    }
    else
    {
        QMessageBox::warning(this,"Alerta","No Selecciono alguna opción");
    }
    insertremoveRowCol(tablaPPAL,0,true);
    setAccountTitle(tablaPPAL);
}

/***        Slot para calcular el coeficiente tecnico horizontal de la matriz endogena/exogena      ***/
void MainWindow::slotAn()
{
    actionAn.setDisabled(true);
    tabWidget->addTab(new QWidget,"An");
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    QTableWidget *to = findChild<QTableWidget *>("TablaExogenaEndogena");
    QTableWidget *tablaAn = new QTableWidget;
    tablaAn->setObjectName("MatrizAn");
    int count=tw->rowCount();
    CrearTablaVacia(count,tablaAn);//Se crea una tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tablaAn);
    /*****      Se llena la tabla vacia con los valores de la tabla principal ****/

    insertremoveRowCol(to,0, false);
    CalcularAn(tw,tablaAn,to,count,true);//Funcion para calcular el Coeficiente Tecnico Horizontal (An)
    /***            Procedimiento para obtener la matriz con los totales originales para luegos ser usados en An ***/
    int elementos = contarElementosMap();
    count=to->rowCount()-1;
    if(opcionCuentaExogena==1)
    {
        int inicioExogena=count-elementos;
        setEndogenaExogenaCell(to,inicioExogena+1,elementos,true);
    }
    else
    {
        setEndogenaExogenaCell(to,count,0,false);
    }

    int indice=ObtenerIndice("An");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tablaAn);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada

    crearMatrizEndogena(tablaAn);
    connect(&actionLa,SIGNAL(triggered()),this,SLOT(slotLa()));
    actionLa.setEnabled(true);
}

void MainWindow::slotLa()
{
    QTableWidget *tw = findChild<QTableWidget *>("MatrizAn");
    double matrizIdentidad[200][200];
    double matrizResta[200][200];
    crearMatrizIdentidad(tw,matrizIdentidad);
    restarIdentidadAn(tw,matrizIdentidad,matrizResta);
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


void MainWindow::createMatrixCentralWidget()
{
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    QVBoxLayout * layoutLateralWidget = new QVBoxLayout;

    QTableWidget * tableWidget = new QTableWidget(this);
    tableWidget->setObjectName("TablaPrincipal");//Se le asigna nombre al objeto
    QGroupBox * groupBoxAccount = new QGroupBox;
    QPushButton * buttonEnd = new QPushButton;
    buttonEnd->setObjectName("AgregarCuentas");//Se le asigna nombre al objeto
    QPushButton * buttonRestaurar = new QPushButton;
    buttonRestaurar->setObjectName("Restaurar");//Se le asigna nombre al objeto
    QPushButton * buttonFinalizar = new QPushButton;
    buttonFinalizar->setObjectName("Finalizar");//Se le asigna nombre al objeto
    QPushButton * buttonModificar = new QPushButton;
    buttonModificar->setObjectName("Modificar");//Se le asigna nombre al objeto

    populateTable(tableWidget);
    tableWidget->setMaximumHeight(700);

    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tableWidget);

    //tableWidget->setFixedSize(750,750);
    layoutCentralWidget->addWidget(tableWidget);
    //layoutCentralWidget->addStretch();

    QVBoxLayout * layoutAccounts = new QVBoxLayout;

    layoutAccounts->addWidget(new StackWidget(numAccounts, groupBoxAccount));

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
    buttonEnd->setText("Agregar Cuenta");
    buttonEnd->setFixedWidth(130);
    buttonEnd->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    layoutLateralWidget->addWidget(buttonEnd);


    /***********          Nuevo boton para restaurar la tabla             *******/
    buttonRestaurar->setText("Restaurar Titulos");
    buttonRestaurar->setFixedWidth(150);
    buttonRestaurar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    layoutLateralWidget->addWidget(buttonRestaurar);

    buttonModificar->setText("Editar Cuenta Actual");
    buttonModificar->setFixedWidth(180);
    buttonModificar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    layoutLateralWidget->addWidget(buttonModificar);


    buttonFinalizar->setText("Finalizar Carga");
    buttonFinalizar->setFixedWidth(130);
    buttonFinalizar->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    layoutLateralWidget->addWidget(buttonFinalizar);
    layoutLateralWidget->addStretch(6);


    layoutCentralWidget->addLayout(layoutLateralWidget);

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

    matricesMenuBar();//Al terminar la carga de la tabla se ejecuta la accion para el menu de Operaciones
    tabWidget->setCurrentIndex(1);//Se seleciona la pestaña MCS

    actionLoadMatrix.setDisabled(true);

    actionExportMatrix.setEnabled(true);

    /****          Se conectan las acciones para coeficientes tecnicos horizontales y verticales      ****/
    connect(&actionCH, SIGNAL(triggered()), this,SLOT(slotCoeficienteHorizontal()));
    connect(&actionCV, SIGNAL(triggered()), this,SLOT(slotCoeficienteVertical()));
    //Se conecta la accion para la variables exogenas
    connect(&actionVariableExogena,SIGNAL(triggered()),this,SLOT(slotVariableExogena()));
}

void MainWindow::AgregarCuenta()
{
    QMessageBox msBox(QMessageBox::Question,"Agregar cuenta","¿Está seguro que agregar la cuenta?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"Si");
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

        if(nombreCuenta.isEmpty() or nombreCuenta.isNull())
        {
            QMessageBox::warning(this,"Alerta","El nombre de la cuenta esta vacio");
        }
        else
        {
            int cantidad_filas=tw->rowCount();

            if(inicio>cantidad_filas or fin>cantidad_filas)//Se verifica que los valores no excedan el tamaño de la tabla
            {
                QMessageBox::warning(this,"Alerta","Valores mayores al tamaño\n de la tabla");
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
                            QSpinBox *otherEnd = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));
                            int otroFin=otherEnd->text().toInt();
                            if(inicio<otroFin)
                            {
                                centinela=false;
                            }
                        }
                    }
                }

                /*  *****    Se asigna el nombre de la cuenta a las cabecereas de la tabla en el rango(inicio,fin)     *****    */
                if((inicio>2 && fin>2) and (centinela))
                {

                    QTableWidgetItem *ValoraInsertarFila = new QTableWidgetItem(nombreCuenta);
                    ValoraInsertarFila->setTextAlignment(Qt::AlignCenter);
                    ValoraInsertarFila->setFlags(ValoraInsertarFila->flags() ^ Qt::ItemIsEditable);
                    tw->setItem(0,inicio-1,ValoraInsertarFila);
                    QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem(nombreCuenta);
                    ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
                    ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
                    tw->setItem(inicio-1,0,ValoraInsertarColumna);
                    int espacio=(fin-inicio)+1;
                    tw->setSpan(inicio-1,0,espacio,1);
                    tw->setSpan(0,inicio-1,1,espacio);
                    /*****              Se inhabilita el boton de la linea  y los spinbox  *******/
                    le->setEnabled(false);
                    SBStart->setEnabled(false);
                    SBEnd->setEnabled(false);
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

}

void MainWindow::FinalizarCuentas()
{
    QMessageBox msBox(QMessageBox::Question,"Finalizar Carga","¿Está seguro que desea finalizar?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"Si");
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
            QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
            QPushButton *Finalizar = findChild<QPushButton *>("Finalizar");
            Finalizar->setStyleSheet("background-color: gray; color: #fff;"
                                     "font-weight: bold; height: 30px; border: none;"
                                     "border-radius: 5px; margin-top: 40px;");
            Finalizar->setEnabled(false);
            Finalizar->setVisible(false);

            QGroupBox *groupbox = findChild<QGroupBox *>("GrupoCuentas");
            groupbox->setVisible(false);

            insertremoveRowCol(tw,0,false);
            CalcularTotales(tw,1);//Se llama a la funcion que agregue una nueva fila y columna con los totales respectivos
            insertremoveRowCol(tw,0,true);
            setAccountTitle(tw);

            /*       Luego de calcular los totales se habilitan las opciones del menu herramientas       */
            actionCH.setEnabled(true);
            actionCV.setEnabled(true);
            actionVariableExogena.setEnabled(true);
         }
        else
        {
            QMessageBox::warning(this,"Alerta","Debe llenar correctamente y agregar todas las cuentas");
        }
    }
}

void MainWindow::CalcularTotales(QTableWidget *tableWidget,int inicio)//Se calculan los totales por fila/columna
{
    int filas=tableWidget->rowCount();
    int columnas=tableWidget->columnCount();
    /*******       Se inserta la nueva fila y columna para los totales, asi como es texto corespondiente             *****/
    tableWidget->insertRow(filas);
    tableWidget->insertColumn(columnas);
    QTableWidgetItem *FilaTotal = new QTableWidgetItem;
    FilaTotal->setText("Total en Fila");
    FilaTotal->setFlags(FilaTotal->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *ColumnaTotal = new QTableWidgetItem;
    ColumnaTotal->setText("Total en Columna");
    ColumnaTotal->setFlags(ColumnaTotal->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(columnas,inicio-1,FilaTotal);
    tableWidget->setItem(inicio-1,filas,ColumnaTotal);
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
        Valor1->setText(QString::number(SumaFila,'f',2));
        QString value1 = Separador(Valor1,false);
        Valor1->setText(value1);
        Valor1->setFlags(Valor1->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *Valor2 = new QTableWidgetItem;
        Valor2->setText(QString::number(SumaColumna,'f',2));
        QString value2 = Separador(Valor2,false);
        Valor2->setText(value2);
        Valor2->setFlags(Valor2->flags() ^ Qt::ItemIsEditable);
        tableWidget->setItem(filas,i,Valor1);//Inserta en Filas
        tableWidget->setItem(i,filas,Valor2);//Inserta en Columnas
    }

}

void MainWindow::RestaurarCeldas()//Slot que permite restaurar el titulo de las cuentas en las celdas
{
    QMessageBox msBox(QMessageBox::Question,"Restaurar Celdas","¿Desea Restaurar el titulo de todas las celdas?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"Si");
    msBox.setDefaultButton(QMessageBox::Yes);
    if(msBox.exec()==QMessageBox::Yes)
    {
        QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
        insertremoveRowCol(tw,0,false);
        insertremoveRowCol(tw,0,true);
    }
}

void MainWindow::ModificarCuenta()//Slot que permite habilitar la edicion de una cuenta una vez agregada
{
    QMessageBox msBox(QMessageBox::Question,"Modificar Cuenta","¿Desea Modificar la Cuenta Actual?",
                      QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"Si");
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

void MainWindow::loadMatrizExogena()
{

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
            tableWidget->setItem(row, column+1, newItem);
        }
        ++row;

        while (!file.atEnd() and row<=matrixSize)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::fromUtf8(rowVH[row-1].c_str()).
                    toLocal8Bit().constData());
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);//Se coloca como no editable
            tableWidget->setItem(row, 0, newItem);

            QString line = file.readLine();
            /*QStringList strings = line.split(csvSeparator);
            for (int column = 0; column < strings.size(); ++column) {
                QTableWidgetItem *newItem = new QTableWidgetItem(
                        strings.at(column).toLocal8Bit().constData());
                tableWidget->setItem(row, column, newItem);

            }*/

            std::vector<std::string> rowV =
                    csv_read_row(line.toStdString(), csvSeparator);
            for(int column=0, leng=rowV.size();
            column < leng and column<matrixSize; column++) {

                //double value = (double)atof(rowV[column].c_str());

                /*              Aqui se incorporan los valores luego de la coma(,)          */
                QString rowVal = QString::fromUtf8(rowV[column].c_str());
                double value = rowVal.toDouble();



                QTableWidgetItem *newItem = new QTableWidgetItem(
                        numberFormat(value).
                        toLocal8Bit().constData());
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);//Se coloca como no editable
                tableWidget->setItem(row, column+1, newItem);
                matrix[row-1][column] =  atof(rowV[column].c_str());
            }
            ++row;
        }
        file.close();
    }
    //tableWidget->resizeColumnsToContents();
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

    int precision = 2;
    bool controlador = false;
    if(d<0)
    {
        controlador = true;
        d *=-1;
    }


    QString stringNumber = QString::number(d, 'f', precision);
    for(int point = 0, i = (stringNumber.lastIndexOf('.') == -1 ? stringNumber.length() : stringNumber.lastIndexOf('.')); i > 0; --i, ++point)
    {
        if(point != 0 && point % 3 == 0)
        {
            stringNumber.insert(i, '*');
        }
    }
    if(controlador)
    {
        double var = stringNumber.toDouble();
        var *=-1;
        stringNumber = QString::number(var, 'f', precision);
    }
    stringNumber.replace(".", ",");
    stringNumber.replace("*", ".");
    return stringNumber;
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
    return centinela;
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

/***        Funcion que obtiene los inicios/fin de las cuentas y las retorna como entero en una lista ***/
QList<int> MainWindow::ObtenerLimitesCuenta(int contador,int opccion)//Funcion que
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

void MainWindow::CrearTablaVacia(int contador, QTableWidget *tw)//FUncion para crear una tabla vacia
{
    for(int k=0;k<contador-1;k++)
    {
        tw->insertRow(k);
        tw->insertColumn(k);
    }
}

int MainWindow::contarElementosMap()//Funcion para contar los elementos en el map o diccionario
{
    int contador=0;
    foreach(QString key,diccCuentasExogenas.keys())
    {
        contador+=diccCuentasExogenas[key].count();
    }
    return contador;
}

/***    Funcion, que dada un nombre de uan cuenta permite retornar su respectivo indice en la combobox ***/
int MainWindow::retornarIndiceCuenta(QString nombre_cuenta)
{
    for(int i=0;i<numAccounts;i++)
    {
       QLineEdit *newline= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
       if(newline->text()==nombre_cuenta)
       {
            return i;
       }
    }
    return 0;
}

/***        Funcion que permite llenar una lista con los elementos en un intervalo dado(fila o columna)         ***/
QList<QString> MainWindow::llenarLista(QList<QString> lista,QTableWidget *tw,int valor,int opcion)
{
    for(int i=0;i<tw->rowCount();i++)
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
    /*      Titulos para las Cuentas endogenas   */
    QTableWidgetItem *CuentaEndogenafila = new QTableWidgetItem("Cuentas Endogenas");
    CuentaEndogenafila->setFlags(CuentaEndogenafila->flags() ^ Qt::ItemIsEditable);
    CuentaEndogenafila->setTextAlignment(Qt::AlignCenter);
    tw->setItem(0,1,CuentaEndogenafila);
    tw->setSpan(0,1,1,inicioExogena-1);
    QTableWidgetItem *CuentaEndogenaColumna = new QTableWidgetItem;
    if(elementos<12)
    {
        CuentaEndogenaColumna->setText("Cuentas \nExogenas");
    }
    else
    {
        CuentaEndogenaColumna->setText("C\nu\ne\nn\nt\na\ns\n\nE\nn\nd\no\ng\ne\nn\na\ns");
    }
    CuentaEndogenaColumna->setFlags(CuentaEndogenaColumna->flags() ^ Qt::ItemIsEditable);
    tw->setItem(1,0,CuentaEndogenaColumna);
    tw->setSpan(1,0,inicioExogena-1,1);
    if(condicion)//Si tiene cuentas exogenas
    {
        /*      Titulos para las Cuentas exogenas   */
        QTableWidgetItem *CuentaExogenafila = new QTableWidgetItem("Cuentas Exogenas");
        CuentaExogenafila->setFlags(CuentaExogenafila->flags() ^ Qt::ItemIsEditable);
        CuentaExogenafila->setTextAlignment(Qt::AlignCenter);
        tw->setItem(0,inicioExogena,CuentaExogenafila);
        if(elementos>1)
        {
            tw->setSpan(0,inicioExogena,1,elementos);
        }
        QTableWidgetItem *CuentaExogenaColumna = new QTableWidgetItem;
        if(elementos<12)
        {
            CuentaExogenaColumna->setText("Cuenta \nExogena");
        }
        else
        {
            CuentaExogenaColumna->setText("C\nu\ne\nn\nt\na\ns\n\nE\nx\no\ng\ne\nn\na\ns");
        }
        CuentaExogenaColumna->setFlags(CuentaExogenaColumna->flags() ^ Qt::ItemIsEditable);
        tw->setItem(inicioExogena,0,CuentaExogenaColumna);
        if(elementos>1)
        {
            tw->setSpan(inicioExogena,0,elementos,1);
        }
    }
}

void MainWindow::CalcularAn(QTableWidget *tw,QTableWidget *nuevaTabla,QTableWidget *tablaOriginal,int count,bool endogena)//Funcion para calcular el Coeficiente Tecnico Horizontal (An)
{
    for(int i=0;i<count-1;i++)
    {
        double total;
        if(endogena)
        {
            QString value = Separador(tablaOriginal->item(count,i),true);
            value = QString::number(value.toDouble(),'f',2);
            total=value.toDouble();
        }
        else
        {
            QString value = Separador(tw->item(count-1,i),true);
            value = QString::number(value.toDouble(),'f',2);
            total=value.toDouble();
        }
        for(int j=0;j<count-1;j++)
        {
            if(i!=0 && j!=0)
            {
                QString values = Separador(tw->item(j,i),true);
                values = QString::number(values.toDouble(),'f',2);
                double valor=values.toDouble();

                if(total==0)//Se comprueba en caso de que el total sea zero
                {
                    valor=0;
                }
                else
                {
                    valor/=total;//Se divide el valor de la celda entre el total correspondiente

                }
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                QString value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                nuevaTabla->setItem(j,i,ValoraInsertar);
            }
            /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
            else if((i==0 && j>0)||(j==0 && i>0))
            {
                QString value=tw->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
       }

    }
}

void MainWindow::clonarTabla(QTableWidget *tw,QTableWidget *nuevaTabla,int cantidad)
{
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            if(i!=0 && j!=0)
            {
                QString value = Separador(tw->item(i,j),true);
                double valor= value.toDouble();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
            else if((i==0 && j>0)||(j==0 && i>0))
            {
                QString value=tw->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }

         }
    }
}

void MainWindow::crearMatrizEndogena(QTableWidget *tw)
{
    int cantidad=tw->rowCount();
    for(int i=0;i<cantidad;i++)
    {
        for(int j=0;j<cantidad;j++)
        {
            if(i!=0 && j!=0)
            {
                double valor=tw->item(i,j)->text().toDouble();
                MatrizEndogenaEndogena[i-1][j-1]=valor;
            }

         }
    }
}

void MainWindow::crearMatrizIdentidad(QTableWidget *tw,double identidad[200][200])
{
    int cantidad=tw->rowCount();
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            if(i==j)
            {
                identidad[i][j]=1;
            }
            else
            {
                identidad[i][j]=0;
            }

         }
    }
}

void MainWindow::restarIdentidadAn(QTableWidget *tw,double identidad[200][200],double resta[200][200])
{
    int cantidad=tw->rowCount();
    mat A(cantidad,cantidad);
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            //qDebug()<<MatrizEndogenaEndogena[i][j]<<" "<<identidad[i][j];
            resta[i][j] = identidad[i][j]-MatrizEndogenaEndogena[i][j];
            //qDebug()<<"A"<<resta[i][j];
            A.at(i,j) = resta[i][j];
            //qDebug()<<"resta"<<A.at(i,j);

         }
    }

    mat inverse = inv(A);

    QTableWidget *tablaLa = new QTableWidget;
    tablaLa->setObjectName("MatrizLa");
    CrearTablaVacia(cantidad,tablaLa);
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            double value = inverse.at(i,j);
            qDebug()<<"double "<<value;
            QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(value,'f',2));
            ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
            tablaLa->setItem(i,j,ValoraInsertar);

         }
    }
    tabWidget->addTab(new QWidget,"La");
    int indice=ObtenerIndice("La");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tablaLa);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada


    /*mat A;
    A << 1 << 2.2222 << 3 << 4 << endr
     << 2 << 1 << 5 << 6 << endr
     << 3 << 5 << 1 << 7 <<endr
     << 4 << 6 << 7 << 1<<endr;
    //qDebug()<<"here"<<A.at(0,8);
    //qDebug()<<"resta"<<resta[0][8];

    double determinant = det(A);*/
    //qDebug() << isnan(determinant);

   /*mat inverse = inv(A);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            qDebug()<<"inversa"<<inverse.at(i,j);

         }
    }*/




    //qDebug()<<"determinant"<<determinant;
    /*if(determinant < -std::numeric_limits<qreal>::max())
    {
        qDebug()<<"-inf";
    }
    else if(determinant > std::numeric_limits<qreal>::max())
    {
        qDebug()<<"inf";
    }
    else if(determinant != determinant)
    {
        qDebug()<< "nan";
    }*/


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
    for(int i=0;i<numAccounts;i++)
    {
        QLineEdit *le= findChild<QLineEdit *>(QString("linedit %1").arg(i + 1));
        QSpinBox *SBStart = findChild<QSpinBox *>(QString("accountstart %1").arg(i+1));
        QSpinBox *SBEnd = findChild<QSpinBox *>(QString("accountend %1").arg(i+1));

        int inicio=SBStart->value();
        int fin=SBEnd->value();
        QString nombreCuenta=le->text();


        QTableWidgetItem *ValoraInsertarFila = new QTableWidgetItem(nombreCuenta);
        ValoraInsertarFila->setTextAlignment(Qt::AlignCenter);
        ValoraInsertarFila->setFlags(ValoraInsertarFila->flags() ^ Qt::ItemIsEditable);
        tw->setItem(0,inicio-1,ValoraInsertarFila);
        QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem(nombreCuenta);
        ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
        ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
        tw->setItem(inicio-1,0,ValoraInsertarColumna);
        int espacio=(fin-inicio)+1;
        tw->setSpan(inicio-1,0,espacio,1);
        tw->setSpan(0,inicio-1,1,espacio);
    }
}

/*                  Funcion para agregar/quitar columnas y filas                    */
void MainWindow::insertremoveRowCol(QTableWidget *tw, int rowcol, bool opcion)
{
    if(opcion)//Si la opcion es verdadero se agrega
    {
        tw->insertRow(rowcol);
        tw->insertColumn(rowcol);
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
        archivo.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&archivo);
        out << "hola " << "que hace" << "? \n";
        out << "otra linea de prueba";
        archivo.flush();
        archivo.close();
        formExportMatriz->ExportLine->setText("");
        formExportMatriz->close();
    }
}

void MainWindow::slotSearchExport()
{
    QString format = ".txt";

    QString filename = QFileDialog::getSaveFileName(this,
            "Elija el nombre", QDir::homePath(),"*.txt");

    filename +=format;

    formExportMatriz->Exportcb->addItem(filename);

    formExportMatriz->ExportLine->setText(filename);
    qDebug()<< formExportMatriz->ExportLine->text();

}
