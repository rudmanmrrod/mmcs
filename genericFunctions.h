#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H

#include <QtWidgets>

//Funciones de tipo void
void titleSeleccionar(QTableWidget *);
void crearTablaComparar(QTableWidget *to, QTableWidget *tw);
void encadenamientosStyle(QTableWidgetItem *);
void tableItem(QTableWidget *tw, int inicio, int fin, QString texto);
void CellStyle(QTableWidgetItem *);
void CellStyleComponente(QTableWidgetItem *);
void CellStyleExEn(QTableWidgetItem *);
void insertRowExogena(QList<QString> lista,QTableWidget *,int opcion);
void noEditColZero(QTableWidget *);
void ItemsNoEditable(QTableWidget *, int inicio, int fin, int col=0);
void CrearTablaVacia(int contador, QTableWidget *);
void crearTablaVaciaEncadenamiento(int filas, QTableWidget *,int columnas=4);
//Funciones de tipo Lista
QList<QString> llenarLista(QList<QString> lista,QTableWidget *tw,int valor,int opcion);
QStringList get_list(QTableWidget *tw, int row, int init, int end);
QStringList ObtenerComponentes(QTableWidget *);
//Funciones de tipo Entero
int diferent_elements(QStringList my_list);
int contarElementosMap(QMap<QString,QStringList> diccionario);


#endif // GENERICFUNCTIONS_H
