#include "encadenamientoswidget.h"

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
