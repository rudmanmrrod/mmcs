/*
    realizado por Rodrigo Boet Agosto/2015
*/
#include "formencadenamientos.h"
#include "ui_formencadenamientos.h"

FormEncadenamientos::FormEncadenamientos(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormEncadenamientos)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

FormEncadenamientos::~FormEncadenamientos()
{
    delete ui;
}
