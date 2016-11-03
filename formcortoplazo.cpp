/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formdescomposicion.cpp
    @brief Clases y métodos del formulario que permite estimar los impactos a corto plazo (evaluar escenarios)
    @date 03/11/2016
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formcortoplazo.h"
#include "ui_formcortoplazo.h"

/**
    @brief Clase principal que inicializa la interfaz
    @date 03/11/2016
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
FormCortoPlazo::FormCortoPlazo(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormCortoPlazo)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);

    connect(ui->listAgregar,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(slotAgregar(QListWidgetItem*)));
    connect(ui->listSeleccionado,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(slotDeseleccionar(QListWidgetItem*)));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(close()));
}

/**
    @brief Método con el destructor de la interfaz gráfica
    @date 03/11/2016
*/
FormCortoPlazo::~FormCortoPlazo()
{
    delete ui;
}

/**
    @brief Método para agregar items al darle doble click
    @date 27/09/2016
    @param <item> Recibe el item que se le dio doble click
*/
void FormCortoPlazo::slotAgregar(QListWidgetItem *item)
{
    QString text = item->text();
    QList<QListWidgetItem *> items = ui->listSeleccionado->findItems(text,Qt::MatchExactly);
    if(items.size() == 0)
    {
        ui->listSeleccionado->addItem(text);
    }

}

/**
    @brief Método para eliminar items al darle doble click
    @date 27/09/2016
    @param <item> Recibe el item que se le dio doble click
*/
void FormCortoPlazo::slotDeseleccionar(QListWidgetItem *item)
{
    item->~QListWidgetItem();
}

