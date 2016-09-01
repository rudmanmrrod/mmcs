/**
    @file genericFunctions.cpp
    @brief Serie de funciones genéricas para el Sistema de Matrices de Contabilidad Social
    @date 01/08/2016
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include <genericFunctions.h>


/**
    @brief Función que permite obtener los elementos distintos en una lista
    @author Autor: Rodrigo Boet
    @date Fecha: 01/08/2016
    @param <my_list> Lista para en la que se definirán los elementos distintos
    @return elementos distintos de la lista
*/
int diferent_elements(QStringList my_list)
{
    QStringList elements;
    foreach (QString item, my_list) {
        if(!elements.contains(item))
        {
            elements.append(item);
        }
    }
    return elements.count();
}

/**
    @brief Función que permite agregar un mensaje en el label cuando se selecciona la opción de componentes
    @date 29/07/2016
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @param <row> Recibe la fila de la que se extraeran los datos
    @param <init> Recibe el inicio de la fila de donde extraeran los datos
    @param <end> Recibe el fin de la fila de donde extraeran los datos
    @return <elements> retorna una lista con los elementos
*/
QStringList get_list(QTableWidget *tw, int row, int init, int end)
{
    QStringList elements;
    for(int i=init;i<end;i++)
    {
        elements.append(tw->item(row,i)->text());
    }
    return elements;
}

/**
   @brief Funcion para agregar el span en los titulos de la matriz seleccionada
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla
*/
void titleSeleccionar(QTableWidget *tw)
{
    QStringList CuentaFila;
    QStringList CuentaColumna;
    int fila = tw->rowCount();
    int columna = tw->columnCount();
    /*      Se crea una lista con las veces que se repiten cuentas en filas/columnas*/
    //Fila
    for(int i = 2;i<fila;i++)
    {
        CuentaFila.append(tw->item(i,0)->text());
    }
    //Columna
    for(int j = 2;j<columna;j++)
    {
        CuentaColumna.append(tw->item(0,j)->text());
    }
    /*      Se crea el span tomando en cuenta las veces que se repite una cuenta en las listas      */
    //Fila
    for(int i=2;i<fila-1;i++)
    {
        QString accName=tw->item(i,0)->text();
        if(CuentaFila.contains(accName))
        {
            int contar = CuentaFila.count(accName);
            tw->setSpan(i,0,contar,1);
            CuentaFila.removeAll(accName);
        }
        if(CuentaFila.isEmpty())
        {
            break;
        }
    }
    //Columna
    for(int j=2;j<columna-1;j++)
    {
        QString accName=tw->item(0,j)->text();
        if(CuentaColumna.contains(accName))
        {
            int contar = CuentaColumna.count(accName);
            tw->setSpan(0,j,1,contar);
            CuentaColumna.removeAll(accName);
        }
        if(CuentaColumna.isEmpty())
        {
            break;
        }
    }
}

/**
   @brief Funcion para generar las tablas de comparación entre matrices
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla que se modificará
   @param <tw> Recibe el widget de la tabla de donde se sacan los valores
*/
void crearTablaComparar(QTableWidget *to, QTableWidget *tw)
{
    int count = to->rowCount();
    int col = to->columnCount();
    to->insertColumn(col);
    to->insertColumn(col);
    for(int i=0;i<count;i++)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(tw->item(i,2)->text());
        item1->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *item2 = new QTableWidgetItem(tw->item(i,3)->text());
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        if(i==0)
        {
            QFont font;
            font.setBold(true);
            item1->setFont(font);
            item2->setFont(font);
        }
        to->setItem(i,col,item1);
        to->setItem(i,col+1,item2);
    }
    to->resizeColumnsToContents();
    to->resizeRowsToContents();
}

/**
   @brief Funcion para agregar los estilos de la tabla de encadenamientos
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla
*/
void encadenamientosStyle(QTableWidgetItem *ti)
{
    QFont font;
    font.setBold(true);
    ti->setFont(font);
    ti->setFlags(ti->flags() ^ Qt::ItemIsEditable);
    ti->setTextAlignment(Qt::AlignCenter);
}

/**
   @brief Funcion para agregar un texto en una tabla en los rangos especificados
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla donde se agregrá el texto
   @param <inicio> Recibe desde donde se escribirá el texto
   @param <fin> Recibe hasta donde se escribirá el texto
   @param <texto> Recibe el texto
*/
void tableItem(QTableWidget *tw, int inicio, int fin, QString texto)
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

/**
   @brief Funcion para agregar el estilo de una celda en negrita(letra blanca) con fondo de color azul (Cuenta)
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla en la que se agregarán los estilos
*/
void CellStyle(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(53,140,203));
    ti->setTextColor(Qt::white);
    QFont font;
    font.setBold(true);
    ti->setFont(font);
}

/**
   @brief Funcion para agregar el estilo de una celda con fondo de color gris (Componente)
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla en la que se agregarán los estilos
*/
void CellStyleComponente(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(221,227,230));
}

/**
   @brief Funcion para agregar el estilo de una celda en negrita(letras blancas) con fondo de color gris oscuro (endogéna-exogéna)
   @date 10/10/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla en la que se agregarán los estilos
*/
void CellStyleExEn(QTableWidgetItem *ti)
{
    ti->setBackgroundColor(QColor(110,110,110));
    ti->setTextColor(Qt::white);
    QFont font;
    font.setBold(true);
    ti->setFont(font);
}

/**
   @brief Funcion que escribe en una columna o fila con la lista dada
   @date 10/10/2015
   @author Rodrigo Boet
   @param <lista> Recibe la lista de donde se sacarán los valores
   @param <tw> Recibe el widget de la tabla
   @param <opcion> Recibe la opción (1 para escribir en columna y 0 para la fila)
*/
void insertRowExogena(QList<QString> lista,QTableWidget *tw,int opcion)
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

/**
   @brief Funcion para volver la celda(0,0) no editable
   @date 08/07/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla
*/
void noEditColZero(QTableWidget *tw)
{
    QTableWidgetItem *ValoraInsertar = new QTableWidgetItem;
    ValoraInsertar->setFlags(ValoraInsertar->flags() ^ Qt::ItemIsEditable);
    tw->setItem(0,0,ValoraInsertar);
}

/**
   @brief Funcion estandar para hacer algunas celdas no editables debido a que son dificiles de manipular(por motivos de colocado y borrado dinamico)
   @date 08/07/2015
   @author Rodrigo Boet
   @param <tw> Recibe el widget de la tabla
   @param <inicio> Recibe el inicio
   @param <fin> Recibe el fin
   @param <opcion> Recibe la columna (por defecto 0)
*/
void ItemsNoEditable(QTableWidget *tw,int inicio,int fin,int col)
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

/**
    @brief Función para retornar todos los componentes en una lista
    @date 10/10/2015
    @author Rodrigo Boet
    @param <tw> Recibe el widget de la tabla
    @return <elements> retorna una lista con los elementos
*/
QStringList ObtenerComponentes(QTableWidget *tw)
{
    QStringList MiLista;
    int contador=tw->rowCount();
    for(int i=1;i<contador-1;i++)
    {
        MiLista.append(tw->item(0,i)->text());
    }
    return MiLista;
}


/**
    @brief Funcion que permite llenar una lista con los elementos en un intervalo dado(fila o columna)
    @date 10/10/2015
    @author Rodrigo Boet
    @param <lista> Recibe la lista en la que escribirán los componenentes
    @param <tw> Recibe el widget de la tabla
    @param <valor> Recibe el valor de fila/cloumna
    @param <opcion> Recibe la opción (1 para fila y 0 para columna)
    @return <elements> retorna una lista con los elementos
*/
QList<QString> llenarLista(QList<QString> lista,QTableWidget *tw,int valor,int opcion)
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

/**
    @brief Funcion para crear una tabla cuadrada vacía en un rango dado
    @date 08/07/2015
    @author Rodrigo Boet
    @param <contador> Recibe la dimensión de la tabla
    @param <tw> Recibe el widget de la tabla
*/
void CrearTablaVacia(int contador, QTableWidget *tw)
{
    for(int k=0;k<contador-1;k++)
    {
        tw->insertRow(k);
        tw->insertColumn(k);
    }
}

/**
    @brief Funcion para crear una tabla vacia no cuadrada, específicamente para los encadenamientos
    @date 08/07/2015
    @author Rodrigo Boet
    @param <filas> Recibe la dimensión de las filas
    @param <tw> Recibe el widget de la tabla
    @param <columnas> Recibe la dimensión de las columnas
*/
/*          Funcion para crear una tabla vacia, específicamente para los encadenamientos        */
void crearTablaVaciaEncadenamiento(int filas, QTableWidget *tw,int columnas)
{
    for(int j=0;j<columnas;j++)
    {
        tw->insertColumn(0);
    }
    for(int k=0;k<filas;k++)
    {
        tw->insertRow(k);
    }
}

/**
    @brief Funcion que permite contar los elementos en el map o diccionario
    @date 10/10/2015
    @author Rodrigo Boet
    @param <diccionario> Recibe el diccionario (clave,valor) -> QString y QStringList Respectivamente
    @return <contador> retorna la cantidad de elementos
*/
int contarElementosMap(QMap<QString,QStringList> diccionario)
{
    int contador=0;
    foreach(QString key,diccionario.keys())
    {
        contador+=diccionario[key].count();
    }
    return contador;
}

