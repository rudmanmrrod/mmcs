#include "formcargando.h"
#include "ui_formcargando.h"

FormCargando::FormCargando(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormCargando)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
    //ui->label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QMovie *movie = new QMovie(":/imgs/mmcsload.gif");
    ui->label->setMovie(movie);
    movie->start();

}

FormCargando::~FormCargando()
{
    delete ui;
}
