/*
    Creado bajo la Licencia GPL v.2.0 de la Free Software Foundation.
    Autor: Rodrigo Boet
    Fecha: 01/08/2016
*/

#include <genericFunctions.h>

/*
    Función que permite obtener los elementos distintos en una lista
    Autor: Rodrigo Boet
    Fecha: 01/08/2016
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

/*
    Función que permite agregar un mensaje en el label cuando se selecciona la opción de componentes
    Autor: Rodrigo Boet
    Fecha: 29/07/2016
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
