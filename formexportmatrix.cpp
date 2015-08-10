#include "formexportmatrix.h"
#include "ui_formexportmatrix.h"

FormExportMatrix::FormExportMatrix(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormExportMatrix)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

FormExportMatrix::~FormExportMatrix()
{
    delete ui;
}
