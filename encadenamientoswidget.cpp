/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file encadenamientoswidget.cpp
    @brief Clases y métodos del widget que permite generar los encadenamientos
    @date 15/07/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "encadenamientoswidget.h"


/**
    @brief Clases principal que inicializa la interfaz
    @date 15/07/2015
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
EncadenamientosWidget::EncadenamientosWidget(int number, QStringList lista, QWidget *parent) :
    QWidget(parent)
{
    layoutEncadenamientos = new QHBoxLayout;
    this->setLayout(layoutEncadenamientos);

    encadenamientosListWidget = new QListWidget(this);
    encadenamientosListWidget->setFixedWidth(350);
    encadenamientosListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    encadenamientosListWidget->addItems(lista);
    encadenamientosListWidget->setObjectName(QString("encadenamientosAccList %1").arg(number+1));
    layoutEncadenamientos->addWidget(encadenamientosListWidget);
}
