/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file stackpreciosnohomogeneos.cpp
    @brief Clases y métodos del stack para los precios no homógeneos
    @date 07/09/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "stackpreciosnohomogeneos.h"

/**
    @brief Clase principal que realiza la funcionalidad
    @date 07/09/2015
    @author Rodrigo Boet
    @param <Cuentas> Recibe un mapa con las cuenta,componentes como llave,valor
    @param <parent> Recibe el widget que será el padre
*/
StackPreciosNoHomogeneos::StackPreciosNoHomogeneos(QMap<QString,QStringList> Cuentas,QWidget *parent):
    QWidget(parent)
{
    layoutMain = new QHBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    int i = 0;
    foreach(QString key, Cuentas.keys())
    {

        comboAccount->addItem(key);

        comboAccount->setObjectName(QString("CuentaPBH %1").arg(i + 1));

        varPNH = new variablePNH(i,Cuentas[key],stackedWidget);

        stackedWidget->addWidget(varPNH);

        widgetList.append(varPNH);

        i++;
    }

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);

    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}
