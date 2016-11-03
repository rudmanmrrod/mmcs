#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include <formloadmatrix.H>
#include <ui_formLoadMatrix.h>
#include <formviewmatrix.H>
#include <formvariablesexogenas.h>
#include <formexportmatrix.h>
#include <formencadenamientos.h>
#include <ui_formcompararresultados.h>
#include <formcompararresultados.h>
//Formulario para comparar el modelo no clasico
#include <ui_formcompararmnc.h>
#include <formcompararmnc.h>
//Formulario de incidencias
#include "ui_formincidenciai.h"
#include <formincidenciai.h>
#include <formpreciosnohomogeneos.h>
//Formulario para exportar reporte
#include <formexportreport.h>
#include <ui_formexportreport.h>
#include "accountwidget.H"
//Formulario de descomposicon
#include <formdescomposicion.h>
#include <ui_formdescomposicion.h>
//Formulario de Impacto a Corto Plazo
#include <formcortoplazo.h>
#include <ui_formcortoplazo.h>
//Formulario de Carga
#include <formcargando.h>

//Funciones genericas
#include <genericFunctions.h>
//Librería de gráficos
#include <qcustomplot.h>
#include <sstream>
#include <stackwidget.H>
#include <stackvariablesexogenas.h>
#include <stackencadenamientos.h>
#include <stackpreciosnohomogeneos.h>

#include <QTabWidget>

#include <QMap>
#include <QVector>
#include <QPrinter>

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
    QMenu Descomposicion;

    //Acciones principales
    QAction actionLoadMatrix;
    QAction actionExportMatrix;
    QAction actionQuit;
    QAction actionNewProject;

    //Acciones del menú de coeficientes
    QAction actionCH;
    QAction actionCV;
    QAction actionVariableExogena;
    QAction actionEncadenamiento;

    //Acciones del Modelo clásico y no clásico
    QAction actionModeloClasico;
    QAction actionCompararResultados;
    QAction actionModeloNoClasico;
    QAction actionCompararResultadosMNC;

    //Acciones de precios homógeneos por módelo clásico
    QAction actionPHClasicoIncidencia100;
    QAction actionPHCIncidenciaCuenta;
    QAction actionPHCIncidenciaComponente;

    //Acciones de precios homógeneos por módelo no clásico
    QAction actionPHNoClasicoIncidencia100;
    QAction actionPHNCIncidenciaCuenta;
    QAction actionPHNCIncidenciaComponente;

    //Acciones de precios no homógeneos
    QAction actionPNHIncidencia100;
    QAction actionPNHIncidenciaCuenta;
    QAction actionPNHIncidenciaComponente;

    //Acción para la descomposición
    QAction actionDescomposicion;
    QAction actionCortoPlazo;

    QAction actionSeleccionarTabla;

    //Acciones del manú de ayuda
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

    //Matriz con la tabla principal
    Eigen::MatrixXd PrincipalTable;
    //Tabla de Exogenas y Endogenas
    Eigen::MatrixXd EndogenasyExogenas;
    //Tabla del sector B (exogena/endogena)
    Eigen::MatrixXd ExoEndo;
    //Matriz del Coeficiente Técnico
    Eigen::MatrixXd An;
    Eigen::MatrixXd MBn;
    //Matrices de los múltiplicadores de lontief
    Eigen::MatrixXd MatrixMa;
    Eigen::MatrixXd MatrixMb;
    Eigen::MatrixXd MatrizMat;
    Eigen::MatrixXd MatrizMbt;
    //Matrices para la descomposicion
    Eigen::MatrixXd A0;
    Eigen::MatrixXd M1;
    Eigen::MatrixXd M2;
    Eigen::MatrixXd M3;
    Eigen::MatrixXd T;
    Eigen::MatrixXd O;
    Eigen::MatrixXd C;

    double total_ma;

    QString csvFilePath;
    char csvSeparator;
    int numAccounts;
    int matrixSize;
    int precission;

    QString componentePNH;

    Eigen::MatrixXd MatrizEndogenaEndogena;

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
    //Son los vectores que almacenrán los totales del vectorFila y vectorColumna para An
    QVector<double> vFila;
    QVector<double> vColumna;

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
    //Cantidad de impactos a corto plazo
    int cantidadImpactos;

    FormLoadMatrix * formLoadMatrix;
    FormMatrixView * formViewMatrix;
    FormVariablesExogenas * formVariablesExogenas;
    FormExportMatrix * formExportMatriz;
    FormEncadenamientos * formEncadenamientos;
    FormCompararResultados *formCompararResultados;
    FormCompararMNC *formCompararMNC;
    FormIncidenciaI *FI;
    FormPreciosNoHomogeneos * formPreciosNoHomogeneos;
    FormDescomposicion *formdescomposicion;
    FormCortoPlazo *formcortoplazo;

    void initGUI();

    void createCentralWidget();
    void createMatrixCentralWidget();
    void loadsAccounts(QTableWidget *);
    void hideStackedWidget();

    void createMenuBar();
    void matricesMenuBar();
    void populateTable(QTableWidget *);

    void CalcularTotales(QTableWidget *, int inicio, bool &);
    void TotalPrincipalTable(QTableWidget *, Eigen::MatrixXd & , int init);
    bool comprobarNombreCuenta(QString, int indice);
    void clonarTabla(QTableWidget *,QTableWidget *, int cantidad);
    void setAccountTitle(QTableWidget *);
    void insertremoveRowCol(QTableWidget *, int rowcol, bool opcion);
    void crearDiccionario(QTableWidget *, bool endogena=true);
    QStringList obtenerCuentasEndogenas(QTableWidget *,QStringList);
    QStringList obtenerCuentasExogenas(QTableWidget *,QStringList );
    void spanEndogenaCell(QTableWidget *, int inicio, int celda, bool endex=true);
    void spanExogenaCell(QTableWidget *,int celda);

    void TotalEndoExoTable(int elementos, int cantidad);

    void setEndogenaExogenaCell(QTableWidget *, int inicioExogena, int elementos,bool condicion);
    void CalcularAn(QTableWidget *, QTableWidget *, QTableWidget *, int count, bool endogena = false);
    QString Separador(QTableWidgetItem *,bool quitar);
    void EndogenaAn();

    void calcularTotalCuentas(QTableWidget *);
    void estimarVectorPonderacion();

    void obtenerCuentaComponentes();
    void crearMatrizEncadenamiento(QTableWidget *, QTableWidget *);
    void crearMatrizEncadenamientoEndogena(QTableWidget *, QTableWidget *, Eigen::MatrixXd Matrix);
    void calcularTotalesEncadenamientos(QTableWidget *);
    void cuentacomponentesEncadenamiento(QTableWidget *, int count);

    void calcularSubtotal(QTableWidget *,int inicio, int fin,int exogena);
    void llenarEscenario(QTableWidget *, int clasico=0);
    void calcularFinEscenario(QTableWidget *, QString, Eigen::MatrixXd matrix);
    QVector<double> obtenerResultadoEscenario(QVector<double>, QString, Eigen::MatrixXd matrix);
    QStringList obtenerNombreResultadoEscenario();
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

    //Función estimar los vectores fila y columna para la clasificación en los encadenamientos
    void estimarVIFVC();
    //Función para estimar la clasificación de las cuentas por CW o Rassmusen
    void estimarClasificador(double &, double &, int index, double total = 0);
    //Función para determinar los clasificadores
    void determinarClasificador(QTableWidget *, int index_table, int element, double total = 0);

    //Función para validar la cuenta producto/actividad
    bool validarDescomposicion(QStringList);

    //Funciones referentes a la descomposicion
    void calcularA0(QVector<double>);
    void calcularAuxiliares();
    void calcularMatricesDescomposicion();
    //Funciones referentes al impacto a corto plazo
    Eigen::MatrixXd obtenerMatriz(QString);

    //Funcion para crear una nueva pestaña
    void createTab(QString , QTableWidget *,bool current=false);

    bool ComprobarCuentas();
    int ObtenerIndice(QString );

    QStringList ObtenerNombreCuenta(int contador);
    QList<int> ObtenerLimitesCuenta(int contador,int opccion);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void slotNuevoProyecto();
    void slotLoadMatrix();
    void slotExportMatrix();

    void slotFormLoadMatrixAccepted(const QString &, int, int);
    void slotFormLoadMatrixClosed();
    void slotOnlyaccount();
    void slotOnlycomponent();

    void AgregarCuenta();
    void RestaurarCeldas();
    void FinalizarCuentas();
    void ModificarCuenta();
    void slotCoeficienteHorizontal();
    void slotCoeficienteVertical();
    void slotAccChange();

    //Slots para las variables exógenas
    void slotVariableExogena();
    void slotCloseExogena();
    void slotAgregarExogena();
    void slotFinalizarExogena();
    void slotDeshacerExogena();

    void slotMa();

    //Slots para encadenamientos
    void slotEncadenamientos();
    void slotCloseEncadenamiento();
    void slotAgregarEncadenamiento();
    void slotVerEncadenamiento();

    //Slots para reportes
    void slotEncadenamientoReport();
    void slotGenerarEncadenamientoReport(QString,bool);

    //Slots para gráfico
    void slotEncadenamientoGraphic();

    //Slots para exportar
    void slotCloseExport();
    void slotSaveExport();
    void slotSearchExport();

    //Slots para el modelo clásico
    void slotModeloClasico();
    void calcularEscenario(int clasico = 0);
    void finalizarEscenario();

    //Slots para el modelo no clásico
    void slotModeloNoClasico();
    void calcularEscenarioNC();
    void finalizarEscenarioNC();

    //Slot para descomposicion
    void slotDescomposicion();
    void slotAgregarDescomposicion();
    void slotCortoPlazoForm();
    void slotAgregarCortoPlazo();
    void calcularEscenarioImpacto();
    void finalizarImpacto();

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

    //Slots del menú de ayuda
    void abrirManual();
    void acercaDe();

public:
    MainWindow();
    QString numberFormat(double &);
};

#endif // MAINWINDOW_H
