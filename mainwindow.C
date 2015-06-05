#include "mainwindow.H"
void MainWindow::slotLoadMatrix()
{
    formLoadMatrix = new  FormLoadMatrix(this);
    formLoadMatrix->show();
    connect(formLoadMatrix, SIGNAL(formAccepted(QString,int,char)),
            this, SLOT(slotFormLoadMatrixAccepted(QString,int,char)));
}
void MainWindow::slotExportMatrix()
{
    QMessageBox::warning(this,"Warning", "Opcion en desarrollo",
                         QMessageBox::Ok);
}
void MainWindow::closeEvent(QCloseEvent * event)
{
    if(QMessageBox::question(this, "Warning", "Are you sure?",
                             QMessageBox::Yes | QMessageBox::No) ==
       QMessageBox::No)
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

    QWidget * widget = new QWidget;
    widget->setLayout(layoutCentralWidget);
    setCentralWidget(widget);
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

MainWindow::MainWindow()
    : actionLoadMatrix(this), actionExportMatrix(this), actionQuit(this),
    formLoadMatrix(0)
{
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

    //QMessageBox::information(this, "Información", msg);
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



void MainWindow::createMatrixCentralWidget()
{
    QHBoxLayout * layoutCentralWidget = new QHBoxLayout;
    QVBoxLayout * layoutLateralWidget = new QVBoxLayout;

    QTableWidget * tableWidget = new QTableWidget(this);
    QGroupBox * groupBoxAccount = new QGroupBox;
    QPushButton * buttonEnd = new QPushButton;

    populateTable(tableWidget);

    layoutCentralWidget->addWidget(tableWidget);
    //layoutCentralWidget->addStretch();

    QVBoxLayout * layoutAccounts = new QVBoxLayout;

    layoutAccounts->addWidget(new StackWidget(numAccounts, groupBoxAccount));

    groupBoxAccount->setFixedWidth(220);
    groupBoxAccount->setLayout(layoutAccounts);;
    groupBoxAccount->setTitle("Cuentas");
    groupBoxAccount->setStyleSheet("QGroupBox {border: 1px solid gray; "
                     "border-radius: 3px; margin-top: 0.5em;} "
                     "QGroupBox::title { subcontrol-origin: margin; "
                     "left: 10px; padding: 0 3px 0 3px; } ");



    layoutLateralWidget->addStretch(1);
    layoutLateralWidget->addWidget(groupBoxAccount);
    buttonEnd->setText("Finalizar Carga");
    buttonEnd->setFixedWidth(130);
    buttonEnd->setStyleSheet("background-color: #358ccb; color: #fff;"
                             "font-weight: bold; height: 30px; border: none;"
                             "border-radius: 5px; margin-top: 40px;");
    layoutLateralWidget->addWidget(buttonEnd);
    layoutLateralWidget->addStretch(6);

    layoutCentralWidget->addLayout(layoutLateralWidget);



    //QWidget * widgetLateral = new QWidget;
    //widgetLateral->setLayout(layoutLateralWidget);
    //layoutCentralWidget->addWidget(widgetLateral,1,0);




    QWidget * widget = new QWidget;
    widget->setLayout(layoutCentralWidget);
    setCentralWidget(widget);
}

void MainWindow::populateTable(QTableWidget * tableWidget) {


    QFile file(csvFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int row = 0;
        QString lineHead = file.readLine();
        std::vector<std::string> rowVH =
                csv_read_row(lineHead.toStdString(), csvSeparator);

        matrixSize = rowVH.size();
        tableWidget->setRowCount(matrixSize+1);
        tableWidget->setColumnCount(matrixSize+1);

        for(int column=0; column<matrixSize; column++) {
            QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::fromUtf8(rowVH[column].c_str()).
                    toLocal8Bit().constData());
            tableWidget->setItem(row, column+1, newItem);
        }
        ++row;

        while (!file.atEnd() and row<=matrixSize)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::fromUtf8(rowVH[row-1].c_str()).
                    toLocal8Bit().constData());
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

                double value = (double)atof(rowV[column].c_str());

                QTableWidgetItem *newItem = new QTableWidgetItem(
                        numberFormat(value).
                        toLocal8Bit().constData());

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
    std::stringstream ss(line);
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

    QString stringNumber = QString::number(d, 'f', precision);
    for(int point = 0, i = (stringNumber.lastIndexOf('.') == -1 ? stringNumber.length() : stringNumber.lastIndexOf('.')); i > 0; --i, ++point)
    {
        if(point != 0 && point % 3 == 0)
        {
            stringNumber.insert(i, '*');
        }
    }
    stringNumber.replace(".", ",");
    stringNumber.replace("*", ".");
    return stringNumber;
}
