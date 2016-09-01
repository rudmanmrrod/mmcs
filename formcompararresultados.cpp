/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formcompararresultados.cpp
    @brief Clases y métodos del formulario que permite generar comparar resultados
    @date 15/09/2015
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formcompararresultados.h"
#include "ui_formcompararresultados.h"

/**
    @brief Clase principal que inicializa la interfaz
    @date 15/09/2015
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
FormCompararResultados::FormCompararResultados(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormCompararResultados)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);
}

/**
    @brief Método con el destructor de la interfaz gráfica
    @date 15/09/2015
*/
FormCompararResultados::~FormCompararResultados()
{
    delete ui;
}
