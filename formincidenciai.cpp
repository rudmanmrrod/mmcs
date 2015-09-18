#include "formincidenciai.h"
#include "ui_formincidenciai.h"

FormIncidenciaI::FormIncidenciaI(QWidget *parent) :
    QWidget(parent, Qt::Tool),
    ui(new Ui::FormIncidenciaI)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);

}

FormIncidenciaI::~FormIncidenciaI()
{
    delete ui;
}