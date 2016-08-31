/*
    realizado por José Ruiz Mayo/2015
*/
#include "formviewmatrix.H"
#include "ui_formViewMatrix.h"


FormMatrixView::FormMatrixView(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormMatrixView)
{
    ui->setupUi(this);
}

