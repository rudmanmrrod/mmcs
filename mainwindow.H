#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include <formloadmatrix.H>
#include <formviewmatrix.H>
#include <formvariablesexogenas.h>
#include <formexportmatrix.h>
#include <formencadenamientos.h>
#include <ui_formcompararresultados.h>
#include <formcompararresultados.h>

#include <sstream>
#include <stackwidget.H>
#include <stackvariablesexogenas.h>
#include <stackencadenamientos.h>

#include <QTabWidget>

#include <QMap>
#include <QVector>


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
    QAction actionCTVEndEx;
    QAction actionLa;

    QAction actionEncadenamiento;    
    QAction actionModeloClasico;
    QAction actionCompararResultados;


    QTableWidget * tableWidget;
    QTabWidget * tabWidget;
    QMap<QString,QStringList> diccCuentasExogenas;
    QMap<int,QVector<QString> > diccCuentasEndogenas;
    QMap<int,QVector<QString> > espacioCuentasExogenas;
    QMap<QString,QStringList> diccCuentasComponentes;
    QMap<QString,QStringList> diccCuentasEncadenamientos;

    stackVariablesExogenas *stackVE;
    stackEncadenamientos *stackEncadenamiento;


    QString csvFilePath;
    char csvSeparator;
    int numAccounts;
    int matrixSize;
    double  matrix[100][100];

    double MatrizEndogenaEndogena[200][200];

    int opcionCuentaExogena;
    int opcionVentanaExogena;
    int opcionExportarMatriz;
    int opcionCTEndogena;
    int opcionEncadenamientos;
    int opcionCuentaEncadenamientos;
    int opcionMa;
    int opcionFormCompararResultados;

    QVector<double> subtotalEnd;
    QVector<double> subtotalExog;

    int cantidadEncadenamientos;
    int cantidadEscenarios;
    int cantidadResultados;

    FormLoadMatrix * formLoadMatrix;
    FormViewMatrix * formViewMatrix;
    FormVariablesExogenas * formVariablesExogenas;
    FormExportMatrix * formExportMatriz;
    FormEncadenamientos * formEncadenamientos;
    FormCompararResultados *formCompararResultados;

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
    void crearDiccionario(QTableWidget *, bool endogena=true);
    QStringList obtenerCuentasEndogenas(QTableWidget *,QStringList);
    QStringList obtenerCuentasExogenas(QTableWidget *,QStringList );
    void spanEndogenaCell(QTableWidget *, int inicio, int celda, bool endex=true);
    void spanExogenaCell(QTableWidget *,int celda);
    void tableItem(QTableWidget *, int inicio, int fin, QString texto);

    QList<QString> llenarLista(QList<QString>, QTableWidget *, int valor, int opcion);
    void insertRowExogena(QList<QString>, QTableWidget *, int opcion);
    void setEndogenaExogenaCell(QTableWidget *, int inicioExogena, int elementos,bool condicion);
    void CalcularAn(QTableWidget *, QTableWidget *, QTableWidget *, int count, bool endogena);
    QString Separador(QTableWidgetItem *,bool quitar);
    void ItemsNoEditable(QTableWidget *, int inicio, int fin, int col=0);
    void CellStyle(QTableWidgetItem *);
    void EndogenaAn();

    void obtenerCuentaComponentes();
    void crearTablaVaciaEncadenamiento(int contador, QTableWidget *,int filas=4);
    void crearMatrizEncadenamiento(QTableWidget *, QTableWidget *);
    void crearMatrizEncadenamientoEndogena(QTableWidget *, QTableWidget *);
    void calcularTotalesEncadenamientos(QTableWidget *);
    void encademientosStyle(QTableWidgetItem *);

    void calcularSubtotal(QTableWidget *, int inicio, int fin, int exogena);
    void llenarEscenario(QTableWidget *);
    void calcularFinEscenario(QTableWidget *);
    QVector<double> obtenerResultadoEscenario(QVector<double>);
    QStringList obtenerNombreResultadoEscenario();
    void crearTablaComparar(QTableWidget *, QTableWidget *);
    void cuentacomponentesResultado(QTableWidget *, int count);
    void validar();

    void crearMatrizEndogena(QTableWidget *);
    void restarIdentidadAn(QTableWidget *);
    void titleEndogena(QTableWidget *);

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
    void slotCTVEndogena();

    void slotMa();

    void slotEncadenamientos();
    void slotCloseEncadenamiento();
    void slotAgregarEncadenamiento();
    void slotVerEncadenamiento();

    void slotCloseExport();
    void slotSaveExport();
    void slotSearchExport();

    void slotModeloClasico();
    void calcularEscenario();
    void finalizarEscenario();

    void slotCompararResultados();
    void slotVerResultado();

public:
    MainWindow();
    std::vector<std::string> csv_read_row(std::string , char);
    std::vector<std::string> csv_read_row(std::istream &, char);
    QString numberFormat(double &);

    int contarElementosMap(QMap<QString, QStringList> diccionario);
    int retornarIndiceCuenta(QString nombre_cuenta);
};

#endif // MAINWINDOW_H
