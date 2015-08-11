#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <formloadmatrix.H>
#include <formviewmatrix.H>
#include <formvariablesexogenas.h>
#include <sstream>
#include <stackwidget.H>
#include <QTabWidget>
#include <stackvariablesexogenas.h>
#include <QMap>
#include <formexportmatrix.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMenu menuFile;
    QMenu OpMatrices;
    QMenu menuTools;
    QMenu menuViews;
    QMenu menuHelp;
    QMenu EndoExo;

    QAction actionLoadMatrix;
    QAction actionExportMatrix;
    QAction actionQuit;

    QAction actionCH;
    QAction actionCV;
    QAction actionVariableExogena;
    QAction actionLa;
    QAction actionEncadenamiento;    


    QTableWidget * tableWidget;
    QTabWidget * tabWidget;
    QMap<QString,QStringList> diccCuentasExogenas;

    stackVariablesExogenas *stackVE;


    QString csvFilePath;
    char csvSeparator;
    int numAccounts;
    int matrixSize;
    double  matrix[100][100];

    int opcionCuentaExogena;
    int opcionVentanaExogena;
    int opcionExportarMatriz;
    int opcionCTEndogena;

    FormLoadMatrix * formLoadMatrix;
    FormViewMatrix * formViewMatrix;
    FormVariablesExogenas * formVariablesExogenas;
    FormExportMatrix * formExportMatriz;


    void initGUI();

    void createCentralWidget();
    void createMatrixCentralWidget();

    void createMenuBar();
    void matricesMenuBar();
    void populateTable(QTableWidget *);
    void CalcularTotales(QTableWidget *, int inicio);
    void loadMatrizExogena();
    void clonarTabla(QTableWidget *,QTableWidget *, int cantidad);
    void noEditColZero(QTableWidget *);
    void setAccountTitle(QTableWidget *);
    void insertremoveRowCol(QTableWidget *, int rowcol, bool opcion);

    double MatrizEndogenaEndogena[200][200];


    QList<QString> llenarLista(QList<QString>, QTableWidget *, int valor, int opcion);
    void insertRowExogena(QList<QString>, QTableWidget *, int opcion);
    void setEndogenaExogenaCell(QTableWidget *, int inicioExogena, int elementos,bool condicion);
    void CalcularAn(QTableWidget *, QTableWidget *, QTableWidget *, int count, bool endogena);
    QString Separador(QTableWidgetItem *,bool quitar);
    void ItemsNoEditable(QTableWidget *, int inicio, int fin);
    void CellStyle(QTableWidgetItem *);
    void EndogenaAn();

    void crearMatrizEndogena(QTableWidget *);
    void crearMatrizIdentidad(QTableWidget *,double identidad[200][200]);
    void restarIdentidadAn(QTableWidget *tw,double identidad[200][200],double resta[200][200]);

    bool ComprobarCuentas();
    int ObtenerIndice(QString );

    QStringList ObtenerNombreCuenta(int contador);
    QList<int> ObtenerLimitesCuenta(int contador,int opccion);
    QStringList ObtenerComponentes(QTableWidget *);
    void CrearTablaVacia(int contador,QTableWidget *);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void slotLoadMatrix();
    void slotExportMatrix();
    void slotFormLoadMatrixAccepted(const QString &, int, char);
    void slotFormLoadMatrixClosed();

    void AgregarCuenta();
    void RestaurarCeldas();
    void FinalizarCuentas();
    void ModificarCuenta();
    void slotCoeficienteHorizontal();
    void slotCoeficienteVertical();

    void slotVariableExogena();
    void slotCloseExogena();
    void slotAgregarExogena();
    void slotFinalizarExogena();
    void slotDeshacerExogena();
    void slotLa();

    void slotCloseExport();
    void slotSaveExport();
    void slotSearchExport();

public:
    MainWindow();
    std::vector<std::string> csv_read_row(std::string , char);
    std::vector<std::string> csv_read_row(std::istream &, char);
    QString numberFormat(double &);

    int contarElementosMap();
    int retornarIndiceCuenta(QString nombre_cuenta);
};

#endif // MAINWINDOW_H
