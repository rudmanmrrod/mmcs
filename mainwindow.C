#include "mainwindow.H"
#include "accountwidget.H"
#include "stackvariablesexogenas.h"
#include "formexportmatrix.h"
#include <stackencadenamientos.h>
#include <QDebug>

#include <Eigen>

using namespace Eigen;

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
void MainWindow::closeEvent(QCloseEvent * event)
{
    QMessageBox msBox(QMessageBox::Question,"Alerta","¿Desea Salir?", QMessageBox::Yes | QMessageBox::No,this);
    msBox.setButtonText(QMessageBox::Yes,"&Si");
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

    actionLa.setText("Multiplicadores de &Leontief");
    actionLa.setDisabled(true);
    EndoExo.addAction(&actionLa);

    OpMatrices.addMenu(&EndoExo);

    actionEncadenamiento.setText("E&ncadenamientos");
    actionEncadenamiento.setDisabled(true);
    OpMatrices.addAction(&actionEncadenamiento);


    menuBar()->addMenu(&OpMatrices);
}

MainWindow::MainWindow()
    : actionLoadMatrix(this), actionExportMatrix(this), actionQuit(this),actionCH(this), actionCV(this),
      actionVariableExogena(this),actionLa(this),actionEncadenamiento(this), formLoadMatrix(0)
{
    tabWidget = new QTabWidget;

    /*    Opcion de la cuenta exogena, 0 para decir que nos se selecciono ninguna, 1 que se seleccionaron algunas
                                    y 2 para decir que se seleccionaron todas*/
    opcionCuentaExogena = 0;
    opcionVentanaExogena = 0;
    opcionExportarMatriz = 0;
    opcionEncadenamientos = 0;
    cantidadEncadenamientos = 1;

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

    CalcularAn(tw,CT_VerticalTW,new QTableWidget,count,false);//Funcion para calcular el Coeficiente Tecnico Horizontal (An)


    insertremoveRowCol(CT_VerticalTW,0,true);
    insertremoveRowCol(CT_VerticalTW,0,false);
    setAccountTitle(CT_VerticalTW);
    int indice=ObtenerIndice("CT_Vertical");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(CT_VerticalTW);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada

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
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
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
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                    value = Separador(ValoraInsertar,false);
                    ValoraInsertar->setText(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                    tablaEE->setItem(i,j,ValoraInsertar);
                }
                /****           En este else se llenan las celdas con fila y columna 0, es decir las que tienen nombre *****/
                else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
                {
                    QString value=tablaPPAL->item(i,j)->text();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
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


        clonarTabla(tablaEE,matrizEndogena,inicioExogena);
        CalcularTotales(matrizEndogena,2);

        CalcularTotales(tablaEE,2);
        setEndogenaExogenaCell(tablaEE,inicioExogena,elementos,true);

        //Se crea la nueva pestaña
        tabWidget->addTab(new QWidget,"Tipo de Variable");
        int indice=ObtenerIndice("Tipo de Variable");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(tablaEE);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        formVariablesExogenas->close();
        //Se activa la opcion de los multiplicadores de leontief
        connect(&actionLa,SIGNAL(triggered()),this,SLOT(slotLa()));
        actionLa.setEnabled(true);
        connect(&actionEncadenamiento,SIGNAL(triggered()),this,SLOT(slotEncadenamientos()));

        /*                  Se crea la pestaña endogena-endogena            */
        tabWidget->addTab(new QWidget,"Endogena-Endogena");
        int indiceEndogeno=ObtenerIndice("Endogena-Endogena");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutEndogeno = new QHBoxLayout;
        layoutEndogeno->addWidget(matrizEndogena);
        QWidget *widgetEndogeno = tabWidget->widget(indiceEndogeno);
        widgetEndogeno->setLayout(layoutEndogeno);//Se añade el widget y layout a la pestaña creada

        crearDiccionario(tablaEE);
        crearDiccionario(tablaEE,false);
        //Se juntan y alinean las cuentas
        spanEndogenaCell(tablaEE,3,1);
        spanExogenaCell(tablaEE,1);
        spanEndogenaCell(matrizEndogena,2,0,false);

        obtenerCuentaComponentes();//Se guardan las cuentas/componentes

    }
    else if(opcionCuentaExogena==2)//Si se seleccionaron todas las cuentas
    {

        /*****      Se llena la tabla vacia con los valores de la tabla principal ****/
        for(int i=0;i<count-1;i++)
        {
            for(int j=0;j<count-1;j++)
            {
                if(i>=2 && j>=2)
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
                else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
                {
                    QString value=tablaPPAL->item(i,j)->text();
                    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
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

        CalcularTotales(tablaEE,2);
        setEndogenaExogenaCell(tablaEE,2,count-2,false);

        //Se agrega la nueva pestaña
        tabWidget->addTab(new QWidget,"Tipo de Variable");
        int indice=ObtenerIndice("Tipo de Variable");//Se obtiene el indice de la pestaña
        QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
        layoutCentralWidget->addWidget(tablaEE);
        QWidget *widget = tabWidget->widget(indice);
        widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
        formVariablesExogenas->close();


        //Se juntan los espacios referentes a las cuentas
        crearDiccionario(tablaEE);
        spanEndogenaCell(tablaEE,3,1);

    }
    else
    {
        QMessageBox::warning(this,"Alerta","No Agregó ninguna cuenta");
    }
}

/***        Slot para calcular el coeficiente tecnico vertical de la matriz endogena/exogena      ***/
void MainWindow::EndogenaAn()
{
    tabWidget->addTab(new QWidget,"An");
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    QTableWidget *to = findChild<QTableWidget *>("TablaExogenaEndogena");
    QTableWidget *tablaAn = new QTableWidget;
    tablaAn->setObjectName("MatrizAn");
    int count=tw->rowCount();
    CrearTablaVacia(count,tablaAn);//Se crea una tabla vacia
    /* ****     Se coloca como no editable la celda(0,0)    ***** */
    noEditColZero(tablaAn);

    insertremoveRowCol(to,0, false);
    if(opcionCuentaExogena==1)
    {
        CalcularAn(tw,tablaAn,to,count,true);//Funcion para calcular el Coeficiente Tecnico Horizontal (An)
    }
    else
    {
        CalcularAn(tw,tablaAn,to,count,false);
    }
    /*          Se colocan los titulos de cuenta endoge/exogena en la tabla endogena-exogena(Tipo de Variable)*/
    count=to->rowCount()-1;
    if(opcionCuentaExogena==1)
    {
        int elementos = contarElementosMap(diccCuentasExogenas);
        int inicioExogena=count-elementos;
        setEndogenaExogenaCell(to,inicioExogena+1,elementos,true);
    }
    else
    {
        count = tw->rowCount();
        setEndogenaExogenaCell(to,count,0,false);
    }

    int indice=ObtenerIndice("An");//Se obtiene el indice de la pestaña
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    layoutCentralWidget->addWidget(tablaAn);
    QWidget *widget = tabWidget->widget(indice);
    widget->setLayout(layoutCentralWidget);//Se añade el widget y layout a la pestaña creada
    spanEndogenaCell(tablaAn,2,0,false);//Se juntan los espacios de las cuentas
    crearMatrizEndogena(tablaAn);
}

void MainWindow::slotLa()
{
    EndogenaAn();
    QTableWidget *tw = findChild<QTableWidget *>("MatrizAn");
    restarIdentidadAn(tw);
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
                        tw->setItem(0,i,ValoraInsertarFila);
                        QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem(nombreCuenta);
                        ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
                        ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
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
            QTableWidget *tw = findChild<QTableWidget *>("TablaPrincipal");
            QPushButton *Finalizar = findChild<QPushButton *>("Finalizar");
            Finalizar->setStyleSheet("background-color: gray; color: #fff;"
                                     "font-weight: bold; height: 30px; border: none;"
                                     "border-radius: 5px; margin-top: 40px;");
            Finalizar->setEnabled(false);
            Finalizar->setVisible(false);

            QGroupBox *groupbox = findChild<QGroupBox *>("GrupoCuentas");
            groupbox->setVisible(false);

            CalcularTotales(tw,2);//Se llama a la funcion que agregue una nueva fila y columna con los totales respectivos
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
        Valor1->setText(QString::number(SumaFila,'f',2));
        QString value1 = Separador(Valor1,false);
        Valor1->setText(value1);
        Valor1->setFlags(Valor1->flags() ^ Qt::ItemIsEditable);
        CellStyle(Valor1);//Estilo de la Celda
        QTableWidgetItem *Valor2 = new QTableWidgetItem;
        Valor2->setText(QString::number(SumaColumna,'f',2));
        QString value2 = Separador(Valor2,false);
        Valor2->setText(value2);
        Valor2->setFlags(Valor2->flags() ^ Qt::ItemIsEditable);
        CellStyle(Valor2);//Estilo de la Celda
        tableWidget->setItem(filas,i,Valor1);//Inserta en Filas
        tableWidget->setItem(i,filas,Valor2);//Inserta en Columnas
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

int MainWindow::contarElementosMap(QMap<QString,QStringList> diccionario)//Funcion para contar los elementos en el map o diccionario
{
    int contador=0;
    foreach(QString key,diccionario.keys())
    {
        contador+=diccionario[key].count();
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
                    value = QString::number(value.toDouble(),'f',2);
                    total=value.toDouble();
                }
                else
                {
                    value = Separador(tw->item(count-1,i),true);
                    value = QString::number(value.toDouble(),'f',2);
                    total=value.toDouble();
                }
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
            else if(((i==0 && j>1)||(j==0 && i>1))or((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=tw->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
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
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(valor,'f',2));
                value = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
                nuevaTabla->setItem(i,j,ValoraInsertar);
            }
            else if(((i==0 && j>1)||(j==0 && i>1)) or ((i==1 && j>1)||(j==1 && i>1)))
            {
                QString value=tw->item(i,j)->text();
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(value);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
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

void MainWindow::restarIdentidadAn(QTableWidget *tw)
{
    int cantidad=tw->rowCount()-1;
    MatrixXd A(cantidad-1,cantidad-1);
    MatrixXd b(cantidad-1,cantidad-1);
    MatrixXd ident = MatrixXd::Identity(cantidad-1,cantidad-1);
    for(int i=0;i<cantidad-1;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            A(i,j) = ident(i,j)-MatrizEndogenaEndogena[i][j];
         }
    }

    double determinant = A.determinant();
    b = A.inverse();
    if(determinant==0)
    {
        QMessageBox::critical(this,"Alerta","El determinante es Nulo");
        actionLa.setDisabled(true);
        int indice=ObtenerIndice("An");//Se obtiene el indice de la pestaña
        tabWidget->widget(indice)->setDisabled(true);

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
                double value = b(i,j);
                QTableWidgetItem *ValoraInsertar = new QTableWidgetItem(QString::number(value,'f',2));
                QString valor = Separador(ValoraInsertar,false);
                ValoraInsertar->setText(valor);
                ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
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
        //Se activa la opcion para los encadenamientos
        actionEncadenamiento.setEnabled(true);
        actionLa.setDisabled(true);
    }
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
                tw->setItem(i,j,fila);
                QTableWidgetItem *columna = new QTableWidgetItem(item);
                columna->setFlags(columna->flags() ^ Qt::ItemIsEditable);
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
            tw->setItem(0,i,ValoraInsertarFila);
            QTableWidgetItem *ValoraInsertarColumna = new QTableWidgetItem(nombreCuenta);
            ValoraInsertarColumna->setTextAlignment(Qt::AlignCenter);
            ValoraInsertarColumna->setFlags(ValoraInsertarColumna->flags() ^ Qt::ItemIsEditable);
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

/*          Funcion para agregar el estilo de una celda en negrita con fondo de color azul        */
void MainWindow::CellStyle(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(53,140,203));
    ti->setTextColor(Qt::white);
    QFont font;
    font.setBold(true);
    ti->setFont(font);
}

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
    int inicioExogena;
    if(opcionCuentaExogena==1)
    {
        inicioExogena=count-elementos;
    }
    else
    {
        inicioExogena=count;
    }
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
    int inicioExogena;
    if(opcionCuentaExogena==1)
    {
        inicioExogena=count-elementos;
    }
    else
    {
        inicioExogena=3;
    }
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
    else
    {
        inicioExogena=count;
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
    int inicioExogena;
    if(opcionCuentaExogena==1)
    {
        inicioExogena=count-elementos;
    }
    else
    {
        inicioExogena=count;
    }
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
        diccCuentasComponentes.insert(diccCuentasEndogenas[key][0],list);
    }
    QStringList lista;
    QTableWidget *tw = findChild<QTableWidget *>("MatrizEndogenaEndogena");
    int count = tw->rowCount();
    foreach(QString key,diccCuentasComponentes.keys())
    {
        for(int i=2;i<count-1;i++)
        {
            QString accTitle = tw->item(i,0)->text();
            if(accTitle==key)
            {
                lista.append(tw->item(i,1)->text());
            }
        }
        diccCuentasComponentes[key].append(lista);
        lista.clear();
    }
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
            diccCuentasEncadenamientos.insert(nombre_cuenta,componentes_cuenta);
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

/*          Funcion para crear una tabla vacia, específicamente para los encadenamientos        */
void MainWindow::crearTablaVaciaEncadenamiento(int contador, QTableWidget *tw)
{
    for(int j=0;j<3;j++)
    {
        tw->insertColumn(0);
    }
    for(int k=0;k<contador;k++)
    {
        tw->insertRow(k);
    }
}

/*          Funcion para crear la tabla con los encadenamientos         */
void MainWindow::crearMatrizEncadenamiento(QTableWidget *tw,QTableWidget *enTable)
{
    int countEndogena = tw->rowCount();
    int elementos = contarElementosMap(diccCuentasEncadenamientos);
    crearTablaVaciaEncadenamiento(elementos,enTable);
    int columna=0;
    foreach(QString key,diccCuentasEncadenamientos.keys())
    {
        for(int j=2;j<countEndogena;j++)
        {
            QString titulo =tw->item(0,j)->text();
            QString componente = tw->item(1,j)->text();
            double sumaColumna = 0;
            double sumaFila = 0;
            if(titulo==key)
            {
                foreach(QString valor,diccCuentasEncadenamientos[key])
                {
                    if(componente==valor)
                    {
                        for(int k=2;k<countEndogena;k++)
                        {
                            double EncadenamientoAtras = tw->item(k,j)->text().toDouble();//Suma Columna(Encadenamiento hacia atras)
                            sumaColumna+=EncadenamientoAtras;
                            double EncadenamientoAdelante = tw->item(j,k)->text().toDouble();//Suma Fila(Encadenamiento hacia adelante)
                            sumaFila+=EncadenamientoAdelante;
                        }
                        //Titulo basado en cuenta/componente
                        QTableWidgetItem *title = new QTableWidgetItem;
                        QFont font;
                        font.setBold(true);
                        title->setFont(font);
                        title->setText(QString("Cuenta: %1\nComponente: %2").arg(key,valor));
                        title->setFlags(title->flags() ^ Qt::ItemIsEditable);
                        enTable->setItem(columna,0,title);
                        //Elementos del encadenamiento hacia atras
                        QTableWidgetItem *valorAtras = new QTableWidgetItem(QString::number(sumaColumna,'f',2));
                        QString value = Separador(valorAtras,false);
                        valorAtras->setText(value);
                        valorAtras->setFlags(valorAtras->flags() ^ Qt::ItemIsEditable);
                        valorAtras->setTextAlignment(Qt::AlignCenter);
                        enTable->setItem(columna,1,valorAtras);
                        //Elementos del encadenamiento hacia adelante
                        QTableWidgetItem *valorAdelante = new QTableWidgetItem(QString::number(sumaFila,'f',2));
                        value = Separador(valorAdelante,false);
                        valorAdelante->setText(value);
                        valorAdelante->setFlags(valorAdelante->flags() ^ Qt::ItemIsEditable);
                        valorAdelante->setTextAlignment(Qt::AlignCenter);
                        enTable->setItem(columna,2,valorAdelante);
                        columna++;
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
    enTable->setItem(0,1,encAtras);
    enTable->setItem(0,2,encAdelante);
    noEditColZero(enTable);
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
        //Titulo basado en cuenta/componente
        QString cuenta = tw->item(0,i)->text();
        QString componente = tw->item(1,i)->text();
        QTableWidgetItem *title = new QTableWidgetItem;
        QFont font;
        font.setBold(true);
        title->setFont(font);
        title->setText(QString("Cuenta: %1\nComponente: %2").arg(cuenta,componente));
        title->setFlags(title->flags() ^ Qt::ItemIsEditable);
        enTable->setItem(columna,0,title);
        //Elementos del encadenamiento hacia atras
        QTableWidgetItem *valorAtras = new QTableWidgetItem(QString::number(sumaColumna,'f',2));
        QString value = Separador(valorAtras,false);
        valorAtras->setText(value);
        valorAtras->setFlags(valorAtras->flags() ^ Qt::ItemIsEditable);
        valorAtras->setTextAlignment(Qt::AlignCenter);
        enTable->setItem(columna,1,valorAtras);
        //Elementos del encadenamiento hacia adelante
        QTableWidgetItem *valorAdelante = new QTableWidgetItem(QString::number(sumaFila,'f',2));
        value = Separador(valorAdelante,false);
        valorAdelante->setText(value);
        valorAdelante->setFlags(valorAdelante->flags() ^ Qt::ItemIsEditable);
        valorAdelante->setTextAlignment(Qt::AlignCenter);
        enTable->setItem(columna,2,valorAdelante);
        columna++;
    }
    //Se agregan los titulos
    enTable->insertRow(0);
    QTableWidgetItem *encAtras = new QTableWidgetItem("Encadenamiento Parcial\nhacia atrás");
    encademientosStyle(encAtras);
    QTableWidgetItem *encAdelante = new QTableWidgetItem("Encadenamiento Parcial\nhacia adelante");
    encademientosStyle(encAdelante);
    enTable->setItem(0,1,encAtras);
    enTable->setItem(0,2,encAdelante);
    noEditColZero(enTable);
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
    double sumaAdelante=0;
    double sumaAtras=0;
    //Se realizan los calculos
    for(int i=1;i<count;i++)
    {
        QString stringAtras = Separador(tw->item(i,1),true);
        double itemAtras = stringAtras.toDouble();
        sumaAtras+=itemAtras;
        QString stringAdelante = Separador(tw->item(i,2),true);
        double itemAdelante = stringAdelante.toDouble();
        sumaAdelante+=itemAdelante;
    }
    //Se inserta la fila donde iran los totales
    tw->insertRow(count);
    //Se insertan las celdas con los respectivos valores totales
    QTableWidgetItem *titulo = new QTableWidgetItem("Encadenamiento Parcial, Total");
    encademientosStyle(titulo);
    tw->setItem(count,0,titulo);
    QTableWidgetItem *totalAtras = new QTableWidgetItem(QString::number(sumaAtras,'f',2));
    QString value = Separador(totalAtras,false);
    totalAtras->setText(value);
    encademientosStyle(totalAtras);
    QTableWidgetItem *totalAdelante = new QTableWidgetItem(QString::number(sumaAdelante,'f',2));
    value = Separador(totalAdelante,false);
    totalAdelante->setText(value);
    encademientosStyle(totalAdelante);
    tw->setItem(count,1,totalAtras);
    tw->setItem(count,2,totalAdelante);
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
