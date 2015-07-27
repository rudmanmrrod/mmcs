#include "variableexogenawidget.h"

VariableExogenaWidget::VariableExogenaWidget(int number,QStringList lista,QWidget *parent) :
    QWidget(parent)
{

    layoutAccountConf = new QHBoxLayout;

    this->setLayout(layoutAccountConf);

    accounListWidget = new QListWidget(this);
    accounListWidget->setFixedWidth(350);
    accounListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    accounListWidget->addItems(lista);
    accounListWidget->setObjectName(QString("accountlist %1").arg(number+1));//Nombre para el objeto Nombre de la Cuenta
    layoutAccountConf->addWidget(accounListWidget);

}
