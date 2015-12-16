#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include <formloadmatrix.H>
#include <formviewmatrix.H>
#include <formvariablesexogenas.h>
#include <formexportmatrix.h>
#include <formencadenamientos.h>
#include <ui_formcompararresultados.h>
#include <formcompararresultados.h>
#include <ui_formcompararmnc.h>
#include <formcompararmnc.h>
#include "ui_formincidenciai.h"
#include <formincidenciai.h>
#include <formpreciosnohomogeneos.h>

#include <sstream>
#include <stackwidget.H>
#include <stackvariablesexogenas.h>
#include <stackencadenamientos.h>
#include <stackpreciosnohomogeneos.h>

#include <QTabWidget>

#include <QMap>
#include <QVector>

#include <Eigen>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMenu menuFile;
    QMenu menuTools;
    QMenu menuViews;
    QMenu menuHelp;

    QMenu CoeficientesTecnicos;
    QMenu Encadenamientos;

    QMenu Modelos;
    QMenu PHClasico;
    QMenu PHClasicoIncidencia;
    QMenu PHNoClasico;
    QMenu PHNoClasicoIncidencia;
    QMenu PreciosNH;
    QMenu PreciosNHIncidencia;

    QAction actionLoadMatrix;
    QAction actionExportMatrix;
    QAction actionQuit;
    QAction actionNewProject;

    QAction actionCH;
    QAction actionCV;
    QAction actionVariableExogena;

    QAction actionEncadenamiento;
    QAction actionClasificarCuentas;

    QAction actionModeloClasico;
    QAction actionCompararResultados;
    QAction actionModeloNoClasico;
    QAction actionCompararResultadosMNC;

    QAction actionPHClasicoIncidencia100;
    QAction actionPHCIncidenciaCuenta;
    QAction actionPHCIncidenciaComponente;

    QAction actionPHNoClasicoIncidencia100;
    QAction actionPHNCIncidenciaCuenta;
    QAction actionPHNCIncidenciaComponente;

    QAction actionPNHIncidencia100;
    QAction actionPNHIncidenciaCuenta;
    QAction actionPNHIncidenciaComponente;

    QAction actionSeleccionarTabla;

    QAction actionManual;
    QAction actionAcercaDe;

    QTableWidget * tableWidget;
    QTabWidget * tabWidget;
    QMap<QString,QStringList> diccCuentasExogenas;
    QMap<int,QVector<QString> > diccCuentasEndogenas;
    QMap<int,QVector<QString> > espacioCuentasExogenas;
    QMap<int, QMap<QString,QStringList> > diccCuentasComponentes;
    QMap<int, QMap<QString,QStringList> > diccCuentasEncadenamientos;
    QMap<QString,double> totalCuentas;

    QStringList ComponentesEndogenos;

    QTableWidget *MatrizExgEnd;

    stackVariablesExogenas *stackVE;
    stackEncadenamientos *stackEncadenamiento;
    StackPreciosNoHomogeneos *stackPNH;

    Eigen::MatrixXd MatrixMa;
    Eigen::MatrixXd MatrixMb;
    Eigen::MatrixXd MatrizMat;
    Eigen::MatrixXd MatrizMbt;


    QString csvFilePath;
    char csvSeparator;
    int numAccounts;
    int matrixSize;
    int precission;

    QString componentePNH;

    double MatrizEndogenaEndogena[200][200];

    int opcionCuentaExogena;
    int opcionVentanaExogena;
    int opcionExportarMatriz;
    int opcionEncadenamientos;
    int opcionCuentaEncadenamientos;
    int opcionMa;
    int opcionMb;
    int opcionFormCompararResultados;
    int opcionFormCompararResultadosMNC;
    int opcionMAT;
    int opcionMBT;
    int opcionPNHT;
    int opcionFormPNH;

    QVector<double> subtotalEnd;
    QVector<double> subtotalExog;
    QVector<double> subtotalExogEnd;
    QVector<double> Vpond;

    int cantidadSelecciones;
    int cantidadEncadenamientos;
    int cantidadEscenarios;
    int cantidadResultados;
    int cantidadMNC;//Cantidad de Modelos No Clasicos
    int cantidadResultadosMNC;
    //Cantidad de resultados de incidencia en modelo de precios homogéneos clásico
    int cantidadPHCindidenciaiCuenta;
    int cantidadPHCindidenciaiComponente;
    //Cantidad de resultados de incidencia en modelo de precios homogéneos no clásico
    int cantidadPHNCindidenciaiCuenta;
    int cantidadPHNCindidenciaiComponente;
    //Cantidad de resultados de incidencia en modelo de precios no homogéneos
    int cantidadPNHincidencia100;
    int cantidadPNHincidenciaiCuenta;
    int cantidadPNHincidenciaiComponente;

    FormLoadMatrix * formLoadMatrix;
    FormViewMatrix * formViewMatrix;
    FormVariablesExogenas * formVariablesExogenas;
    FormExportMatrix * formExportMatriz;
    FormEncadenamientos * formEncadenamientos;
    FormCompararResultados *formCompararResultados;
    FormCompararMNC *formCompararMNC;
    FormIncidenciaI *FI;
    FormPreciosNoHomogeneos * formPreciosNoHomogeneos;

    void initGUI();

    void createCentralWidget();
    void createMatrixCentralWidget();

    void createMenuBar();
    void matricesMenuBar();
    void populateTable(QTableWidget *);

    void CalcularTotales(QTableWidget *, int inicio, bool &);
    bool comprobarNombreCuenta(QString, int indice);
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
    void CalcularAn(QTableWidget *, QTableWidget *, QTableWidget *, int count, bool endogena = false);
    QString Separador(QTableWidgetItem *,bool quitar);
    void ItemsNoEditable(QTableWidget *, int inicio, int fin, int col=0);
    void CellStyle(QTableWidgetItem *);
    void CellStyleComponente(QTableWidgetItem *);
    void CellStyleExEn(QTableWidgetItem *);
    void EndogenaAn();

    void calcularTotalCuentas(QTableWidget *);
    void estimarVectorPonderacion();

    void obtenerCuentaComponentes();
    void crearTablaVaciaEncadenamiento(int filas, QTableWidget *, int columnas=4);
    void crearMatrizEncadenamiento(QTableWidget *, QTableWidget *);
    void crearMatrizEncadenamientoEndogena(QTableWidget *, QTableWidget *);
    void calcularTotalesEncadenamientos(QTableWidget *);
    void encademientosStyle(QTableWidgetItem *);
    void cuentacomponentesEncadenamiento(QTableWidget *, int count);
    void obtenerUiUj(QTableWidget *, QVector<double> &, QVector<double> &);
    void calcularClasificador(QTableWidget *, QVector<double>, QVector<double>, int init = 2);
    void agregarPrimeraCelda(QTableWidget *);

    void calcularSubtotal(QTableWidget *,int inicio, int fin,int exogena);
    void llenarEscenario(QTableWidget *, bool clasico=true);
    void calcularFinEscenario(QTableWidget *);
    QVector<double> obtenerResultadoEscenario(QVector<double>);
    QStringList obtenerNombreResultadoEscenario();
    void crearTablaComparar(QTableWidget *, QTableWidget *);
    void cuentacomponentesResultado(QTableWidget *, int count, bool clasico = true);

    void obtenerMatrizExgEnd();
    void crearMatrizExgEnd(QTableWidget *,QTableWidget *,int elementos,int inicioExogena);
    void calcularMatrizExgEnd(QTableWidget *);
    void ctvMatrizExgEnd(QTableWidget *, QTableWidget *);
    void titlespanMatrizExgEnd(QTableWidget *);
    void estimarMb(QTableWidget *, QTableWidget *);
    void calcularSubtotalEndExg();
    QVector<double> obtenerResultadoEscenarioMNC(QVector<double>);
    void calcularFinEscenarioMNC(QTableWidget *);
    QStringList obtenerNombreResultadoEscenarioMNC();

    void crearMatrizEndogena(QTableWidget *);
    void restarIdentidadAn(QTableWidget *);
    void titleEndogena(QTableWidget *);

    void calcularMaT();
    void calcularPHCIncidencia100(QTableWidget *);
    void calcularPHCIncidenciaI(QTableWidget *, QMap<QString, double>);
    void calcularPHCIncidenciaIComponente(QTableWidget *,QTableWidget *);

    void calcularMbT();
    void calcularMb();
    void calcularPHNCIncidencia100(QTableWidget *);
    void calcularVectorSend(QString componente, QVector<double> &);
    void multiplicarMatricesPNH(QTableWidget *, QVector<double>);
    void calcularPNHIncidencia100(QTableWidget *, Eigen::MatrixXd Diagonal);
    void crearFormularioPNH();
    QStringList obtenerCuentas();

    void titleSeleccionar(QTableWidget *);

    bool ComprobarCuentas();
    int ObtenerIndice(QString );

    QStringList ObtenerNombreCuenta(int contador);
    QList<int> ObtenerLimitesCuenta(int contador,int opccion);
    QStringList ObtenerComponentes(QTableWidget *);
    void CrearTablaVacia(int contador,QTableWidget *);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void slotNuevoProyecto();
    void slotLoadMatrix();
    void slotExportMatrix();
    void slotFormLoadMatrixAccepted(const QString &, int, int);
    void slotFormLoadMatrixClosed();

    void AgregarCuenta();
    void RestaurarCeldas();
    void FinalizarCuentas();
    void ModificarCuenta();
    void slotCoeficienteHorizontal();
    void slotCoeficienteVertical();
    void slotAccChange();

    void slotVariableExogena();
    void slotCloseExogena();
    void slotAgregarExogena();
    void slotFinalizarExogena();
    void slotDeshacerExogena();

    void slotMa();

    void slotEncadenamientos();
    void slotCloseEncadenamiento();
    void slotAgregarEncadenamiento();
    void slotVerEncadenamiento();
    void slotClasificarCuentas();

    void slotCloseExport();
    void slotSaveExport();
    void slotSearchExport();

    void slotModeloClasico();
    void calcularEscenario(bool clasico = true);
    void finalizarEscenario();

    void slotModeloNoClasico();
    void calcularEscenarioNC();
    void finalizarEscenarioNC();

    void slotCompararResultadosMNC();
    void slotVerResultadoMNC();

    void slotPHCIncidencia100();
    void slotPHCIncidenciaiCuenta();
    void slotCalcularPHCIncidenciaiCuenta();
    void slotPHCIncidenciaiComponente();
    void slotCalcularPHCIncidenciaiComponente();

    void slotCompararResultados();
    void slotVerResultado();

    void slotPHNCIncidencia100();
    void slotPHNCIncidenciaiCuenta();
    void slotCalcularPHNCIncidenciaiCuenta();
    void slotPHNCIncidenciaiComponente();
    void slotCalcularPHNCIncidenciaiComponente();

    void slotPNHIncudencia100();
    void slotCloseformPNH();
    void slotSelectPNH();
    void slotPNHIncidenciaiCuenta();
    void slotPNHIncidenciaiComponente();
    void slotSelectPNHi();
    void slotCalcularPNHIncidenciaiCuenta();
    void slotSelectPNHic();
    void slotCalcularPNHIncidenciaiComponente();

    void slotSeleccionarTabla();

    void abrirManual();
    void acercaDe();

public:
    MainWindow();
    QString numberFormat(double &);

    int contarElementosMap(QMap<QString, QStringList> diccionario);
};

#endif // MAINWINDOW_H
