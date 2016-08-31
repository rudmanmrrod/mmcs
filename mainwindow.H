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
#include <ui_formcompararmnc.h>
#include <formcompararmnc.h>
#include "ui_formincidenciai.h"
#include <formincidenciai.h>
#include <formpreciosnohomogeneos.h>
#include <formexportreport.h>
#include <ui_formexportreport.h>
#include <genericFunctions.h>

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
    FormMatrixView * formViewMatrix;
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
    void obtenerUiUj(QTableWidget *, QVector<double> &, QVector<double> &);
    void calcularClasificador(QTableWidget *, QVector<double>, QVector<double>, int init = 2);
    void agregarPrimeraCelda(QTableWidget *);

    void calcularSubtotal(QTableWidget *,int inicio, int fin,int exogena);
    void llenarEscenario(QTableWidget *, bool clasico=true);
    void calcularFinEscenario(QTableWidget *);
    QVector<double> obtenerResultadoEscenario(QVector<double>);
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
    void slotClasificarCuentas();

    //Slots para reportes
    void slotEncadenamientoReport();
    void slotGenerarEncadenamientoReport(QString);

    //Slots para exportar
    void slotCloseExport();
    void slotSaveExport();
    void slotSearchExport();

    //Slots para el modelo clásico
    void slotModeloClasico();
    void calcularEscenario(bool clasico = true);
    void finalizarEscenario();

    //Slots para el modelo no clásico
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

    //Slots del menú de ayuda
    void abrirManual();
    void acercaDe();

public:
    MainWindow();
    QString numberFormat(double &);
};

#endif // MAINWINDOW_H
