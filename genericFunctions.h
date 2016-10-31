#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H

#include <QtWidgets>
#include <Eigen>

//Funciones de tipo void
void titleSeleccionar(QTableWidget *);
void crearTablaComparar(QTableWidget *to, QTableWidget *tw);
void encadenamientosStyle(QTableWidgetItem *);
void tableItem(QTableWidget *tw, int inicio, int fin, QString texto);
void CellStyle(QTableWidgetItem *);
void CellStyleComponente(QTableWidgetItem *);
void CellStyleExEn(QTableWidgetItem *);
void insertRowExogena(QList<QString> lista, QTableWidget *, int opcion, bool center, int init);
void noEditColZero(QTableWidget *);
void ItemsNoEditable(QTableWidget *, int inicio, int fin, int col=0);
void CrearTablaVacia(int contador, QTableWidget *);
void crearTablaVaciaEncadenamiento(int filas, QTableWidget *,int columnas=4);
void RowColNoEditable(QTableWidget *tw,int inicio,int fin,int item, bool fila);
void appendElements(QVector<double>,QVector<double>&);

//Funciones de tipo Lista
QList<QString> llenarLista(QList<QString> lista,QTableWidget *tw,int valor,int opcion);
QStringList get_list(QTableWidget *tw, int row, int init, int end);
QStringList ObtenerComponentes(QTableWidget *);

//Funciones de tipo QVector
QVector<double> extractDiagonal(Eigen::MatrixXd Matrix);

//Funciones de tipo Entero
int diferent_elements(QStringList my_list);
int contarElementosMap(QMap<QString,QStringList> diccionario);

//Funciones de tipo double
double sumElements(QVector<double>);

//Funciones de tipo Eigen
Eigen::MatrixXd extractSubMatriz(QTableWidget *tw, QString nombre_fila, QString nombre_columna, Eigen::MatrixXd Matrix);

//Funciones de tipo bool
bool validarDiagonal(QVector<double>);


#endif // GENERICFUNCTIONS_H
