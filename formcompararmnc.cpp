/*
    realizado por Rodrigo Boet Spetiembre/2015
*/
#include "formcompararmnc.h"
#include "ui_formcompararmnc.h"

FormCompararMNC::FormCompararMNC(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormCompararMNC)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

FormCompararMNC::~FormCompararMNC()
{
    delete ui;
}
