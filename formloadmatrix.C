#include "formloadmatrix.H"
#include "ui_formLoadMatrix.h"

void FormLoadMatrix::closeEvent(QCloseEvent *)
{
    emit formClosed();
}

FormLoadMatrix::FormLoadMatrix(QWidget * parent)
    : QWidget(parent, Qt::Tool)
{
    ui.setupUi(this);

    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);

    connect(ui.buttonSearch, SIGNAL(clicked()),this,SLOT(slotLoadMatrixFile()));
    connect(ui.buttonCancel, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui.buttonOpen, SIGNAL(clicked()), this,
            SLOT(slotButtonAcceptClicked()));

}

void FormLoadMatrix::slotLoadMatrixFile() {
    QString filename = QFileDialog::getOpenFileName(this,
            "Seleccione archivo de Matriz", QDir::homePath(),"*.csv");

    if(filename.isEmpty()) return;
    ui.editFilePath->setText(filename);
}

void FormLoadMatrix::slotButtonAcceptClicked()
{
    if (ui.editFilePath->text().isEmpty())
    {
        QMessageBox::critical(this, "Faltan datos",
                              "Debe seleccionar un archivo");

        ui.editFilePath->setFocus();
        return;
    }

    emit formAccepted(ui.editFilePath->text(), ui.spinNumber->value(),ui.spinBox->value());

    close();
}
