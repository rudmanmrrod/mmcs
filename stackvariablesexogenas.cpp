/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file stackvariablesexogenas.cpp
    @brief Clases y métodos del stack para las variables exógenas
    @date 15/07/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "stackvariablesexogenas.h"

/**
    @brief Clase principal que realiza la funcionalidad
    @date 15/07/2015
    @author Rodrigo Boet
    @param <Lista> Recibe una lista con los titulos
    @param <Componentes> Recibe una lista con los componentes
    @param <inicio> Recibe una lista con el inicio del componente <i>
    @param <fin> Recibe una lista con el fin del componente <i>
    @param <parent> Recibe el widget que será el padre
    @param <contar> Recibe el limite de las iteraciones
*/
stackVariablesExogenas::stackVariablesExogenas(QStringList Lista,QStringList Componentes,QList<int> inicio,
                                               QList<int> fin,QWidget *parent,int contar) :
    QWidget(parent)
{
    layoutMain = new QHBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    QStringList nuevosComponentes;


    for (int i = 0;i < contar; ++i)
    {
        comboAccount->addItem(QString(Lista[i]));

        comboAccount->setObjectName(QString("CuentaExogena %1").arg(i + 1));

        nuevosComponentes = generarComponentes(Componentes,inicio[i],fin[i]);

        veWidget = new VariableExogenaWidget(i,nuevosComponentes,stackedWidget);

        stackedWidget->addWidget(veWidget);

        widgetList.append(veWidget);

    }

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);

    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}

/**
    @brief Método que obtiene los componentes de una lista
    @date 15/07/2015
    @author Rodrigo Boet
    @param <Componentes> Recibe la lista de los componentes
    @param <inicio> Recibe el inicio del componente en la lista
    @param <fin> Recibe el fin del componente en la lista
*/
QStringList stackVariablesExogenas::generarComponentes(QStringList Componentes, int inicio, int fin)
{
    QStringList mylista;
    inicio-=3;
    fin-=3;
    for(int i=inicio;i<=fin;i++)
    {
        mylista.append(Componentes[i]);
    }
    return mylista;
}
