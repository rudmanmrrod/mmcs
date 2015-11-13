/*
    realizado por Rodrigo Boet Julio/2015
*/
#include "formvariablesexogenas.h"
#include "ui_formvariablesexogenas.h"

FormVariablesExogenas::FormVariablesExogenas(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormVariablesExogenas)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

FormVariablesExogenas::~FormVariablesExogenas()
{
    delete ui;
}
