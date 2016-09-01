/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file variableexogenawidget.cpp
    @brief Clases y métodos del widget que permite manipular las variables exógenas
    @date 08/07/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "variableexogenawidget.h"

/**
    @brief Clase principal que realiza la funcionalidad
    @date 08/07/2015
    @author Rodrigo Boet
    @param <number> Recibe el número de widget a tratar
    @param <lista> Recibe la lista con los elementos
    @param <parent> Recibe el widget que será el padre
*/
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
