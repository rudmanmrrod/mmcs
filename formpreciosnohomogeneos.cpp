#include "formpreciosnohomogeneos.h"
#include "ui_formpreciosnohomogeneos.h"

FormPreciosNoHomogeneos::FormPreciosNoHomogeneos(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormPreciosNoHomogeneos)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

FormPreciosNoHomogeneos::~FormPreciosNoHomogeneos()
{
    delete ui;
}
