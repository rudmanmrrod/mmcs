/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formdescomposicion.cpp
    @brief Clases y métodos del formulario que permite hacer la descomposicion
    @date 27/09/2016
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formdescomposicion.h"
#include <qdebug.h>

/**
    @brief Clase principal que inicializa la interfaz
    @date 27/09/2016
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
FormDescomposicion::FormDescomposicion(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormDescomposicion)
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
    @date 27/09/2016
*/
FormDescomposicion::~FormDescomposicion()
{
    delete ui;
}


/**
    @brief Método para agregar items al darle doble click
    @date 27/09/2016
    @param <item> Recibe el item que se le dio doble click
*/
void FormDescomposicion::slotAgregar(QListWidgetItem *item)
{
    if(ui->listSeleccionado->count()>=2)
    {
        QMessageBox::information(this,"Info","No se pueden seleccionar más\n de dos(2) cuentas.");
    }
    else
    {
        QString text = item->text();
        QList<QListWidgetItem *> items = ui->listSeleccionado->findItems(text,Qt::MatchExactly);
        if(items.size() == 0)
        {
            ui->listSeleccionado->addItem(text);
        }
    }
}

/**
    @brief Método para eliminar items al darle doble click
    @date 27/09/2016
    @param <item> Recibe el item que se le dio doble click
*/
void FormDescomposicion::slotDeseleccionar(QListWidgetItem *item)
{
    item->~QListWidgetItem();
}
