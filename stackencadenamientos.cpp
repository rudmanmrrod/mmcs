/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file stackencadenamientos.cpp
    @brief Clases y métodos del stack para los encadenamientos
    @date 15/08/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "stackencadenamientos.h"

/**
    @brief Clase principal que realiza la funcionalidad
    @date 15/08/2015
    @author Rodrigo Boet
    @param <Cuentas> Recibe un mapa con las nombre,cuentas como llave,valor
    @param <parent> Recibe el widget que será el padre
*/
stackEncadenamientos::stackEncadenamientos(QMap<int, QMap<QString, QStringList> > Cuentas, QWidget *parent):
    QWidget(parent)
{
    layoutMain = new QHBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    QStringList Componentes;

    int i= 0;
    foreach(int key,Cuentas.keys())
    {
        foreach (QString name, Cuentas[key].keys())
        {
            comboAccount->addItem(QString(name));

            comboAccount->setObjectName(QString("CuentaExogena %1").arg(i+1));

            Componentes = Cuentas[key][name];

            encadenamientosWidget = new EncadenamientosWidget(i,Componentes,stackedWidget);

            stackedWidget->addWidget(encadenamientosWidget);

            widgetList.append(encadenamientosWidget);

            i++;
        }
    }

    comboAccount->addItem("Sub-Matriz Endógena-Endógena");
    comboAccount->setObjectName(QString("SubMatrizEndogenaEndogena"));
    Componentes.clear();
    encadenamientosWidget = new EncadenamientosWidget(i,Componentes,stackedWidget);
    encadenamientosWidget->encadenamientosListWidget->setVisible(false);
    stackedWidget->addWidget(encadenamientosWidget);
    widgetList.append(encadenamientosWidget);

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);


    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}
