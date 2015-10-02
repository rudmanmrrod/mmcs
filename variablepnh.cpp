/*
    realizado por Rodrigo Boet Septiembre/2015
*/
#include "variablepnh.h"

variablePNH::variablePNH(int number, QStringList lista, QWidget *parent):
    QWidget(parent)
{
    layoutAccountConf = new QHBoxLayout;

    this->setLayout(layoutAccountConf);

    accounListWidget = new QListWidget(this);
    accounListWidget->setFixedWidth(350);
    accounListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    accounListWidget->addItems(lista);
    accounListWidget->setObjectName(QString("accountlistPNH %1").arg(number+1));//Nombre para el objeto Nombre de la Cuenta
    layoutAccountConf->addWidget(accounListWidget);
}
