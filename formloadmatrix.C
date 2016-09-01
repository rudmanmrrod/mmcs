/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formloadmatrix.c
    @brief Clases y métodos del formulario que permite generar cargar la matriz
    @date 01/05/2015
    @author José Ruiz
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formloadmatrix.H"
#include "ui_formLoadMatrix.h"

/**
    @brief Método que permite cerrar el formulario
    @date 01/05/2015
    @author José Ruiz
*/
void FormLoadMatrix::closeEvent(QCloseEvent *)
{
    emit formClosed();
}

/**
    @brief Clase principal que inicializa la interfaz
    @date 01/05/2015
    @author José Ruiz
    @param <parent> Recibe el widget que será el padre
*/
FormLoadMatrix::FormLoadMatrix(QWidget * parent)
    : QWidget(parent, Qt::Tool),
      ui(new Ui::FormLoadMatrix)
{
    ui->setupUi(this);
    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);

    connect(ui->buttonSearch, SIGNAL(clicked()),this,SLOT(slotLoadMatrixFile()));
    connect(ui->buttonCancel, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->buttonOpen, SIGNAL(clicked()), this,
            SLOT(slotButtonAcceptClicked()));

}

/**
    @brief Método que permite generar el diálogo para cargar un archivo
    @date 01/05/2015
    @author José Ruiz
*/
void FormLoadMatrix::slotLoadMatrixFile() {
    QString filename = QFileDialog::getOpenFileName(this,
            "Seleccione archivo de Matriz", QDir::homePath(),"*.csv");

    if(filename.isEmpty()) return;
    ui->editFilePath->setText(filename);
}

/**
    @brief Método que valida al pulsar el boton cargar y emite una SIGNAL
    @date 01/05/2015
    @author José Ruiz
*/
void FormLoadMatrix::slotButtonAcceptClicked()
{
    if (ui->editFilePath->text().isEmpty())
    {
        QMessageBox::critical(this, "Faltan datos",
                              "Debe seleccionar un archivo");

        ui->editFilePath->setFocus();
        return;
    }
    else if(!ui->radioAccount->isChecked() and !ui->radioComponent->isChecked()){
        QMessageBox::critical(this, "Faltan datos",
                              "Debe seleccionar si cargará cuentas y componentes o sólo componentes");
        ui->editFilePath->setFocus();
        return;
    }

    emit formAccepted(ui->editFilePath->text(), ui->spinNumber->value(),ui->spinBox->value());

    close();
}
