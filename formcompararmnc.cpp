/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formcompararmnc.cpp
    @brief Clases y métodos del formulario que permite comparar resultados del modelo no clásico
    @date 01/09/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formcompararmnc.h"
#include "ui_formcompararmnc.h"



/**
    @brief Clase principal que inicializa la interfaz
    @date 01/09/2015
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
FormCompararMNC::FormCompararMNC(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormCompararMNC)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

/**
    @brief Método con el destructor de la interfaz gráfica
    @date 01/09/2015
*/
FormCompararMNC::~FormCompararMNC()
{
    delete ui;
}
