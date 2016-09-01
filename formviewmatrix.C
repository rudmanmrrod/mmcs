/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formviewmatrix.c
    @brief Clases y métodos del formulario que permite visualizar la matriz principal
    @date 01/05/2015
    @author José Ruiz
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formviewmatrix.H"
#include "ui_formViewMatrix.h"

/**
    @brief Clase principal que inicializa la interfaz
    @date 01/05/2015
    @author José Ruiz
    @param <parent> Recibe el widget que será el padre
*/
FormMatrixView::FormMatrixView(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormMatrixView)
{
    ui->setupUi(this);
}

