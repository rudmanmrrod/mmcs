#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <formloadmatrix.H>
#include <formviewmatrix.H>
#include <sstream>
#include <stackwidget.H>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMenu menuFile;
    QMenu menuTools;
    QMenu menuViews;
    QMenu menuHelp;
    QAction actionLoadMatrix;
    QAction actionExportMatrix;
    QAction actionQuit;
    QTableWidget * tableWidget;

    QString csvFilePath;
    char csvSeparator;
    int numAccounts;
    int matrixSize;
    double  matrix[100][100];

    FormLoadMatrix * formLoadMatrix;
    FormViewMatrix * formViewMatrix;

    void initGUI();

    void createCentralWidget();
    void createMatrixCentralWidget();

    void createMenuBar();
    void populateTable(QTableWidget *);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void slotLoadMatrix();
    void slotExportMatrix();
    void slotFormLoadMatrixAccepted(const QString &, int, char);
    void slotFormLoadMatrixClosed();

public:
    MainWindow();
    std::vector<std::string> csv_read_row(std::string , char);
    std::vector<std::string> csv_read_row(std::istream &, char);
    QString numberFormat(double &);
};

#endif // MAINWINDOW_H
