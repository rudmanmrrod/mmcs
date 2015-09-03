#include "formcompararresultados.h"
#include "ui_formcompararresultados.h"

FormCompararResultados::FormCompararResultados(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormCompararResultados)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

FormCompararResultados::~FormCompararResultados()
{
    delete ui;
}
