/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formencadenamientos.cpp
    @brief Clases y métodos del formulario que permite generar los encadenamientos
    @date 05/08/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formencadenamientos.h"
#include "ui_formencadenamientos.h"

/**
    @brief Clase principal que inicializa la interfaz
    @date 05/08/2015
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
FormEncadenamientos::FormEncadenamientos(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormEncadenamientos)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

/**
    @brief Método con el destructor de la interfaz gráfica
    @date 05/08/2015
*/
FormEncadenamientos::~FormEncadenamientos()
{
    delete ui;
}
