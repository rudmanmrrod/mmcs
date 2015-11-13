/*
    realizado por Rodrigo Boet Septiembre/2015
*/
#include "stackpreciosnohomogeneos.h"

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
