/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file formexportreport.cpp
    @brief Clases y métodos del formulario que permite generar reportes en pdf
    @date 31/08/2016
    @author Rodrigo Boet
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "formexportreport.h"
#include "ui_formexportreport.h"

/**
    @brief Clase principal que inicializa la interfaz
    @date 31/08/2016
    @author Rodrigo Boet
    @param <parent> Recibe el widget que será el padre
*/
FormExportReport::FormExportReport(QWidget *parent) :
    QWidget(parent,Qt::Tool),
    ui(new Ui::FormExportReport)
{
    ui->setupUi(this);

    int x = parent->pos().x() + parent->width()/2 - this->width()/2;
    int y = parent->pos().y() + parent->height()/2 - this->height()/2;
    this->move(x, y);

    connect(ui->ButtonCancelar,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->ButtonCargar,SIGNAL(clicked()),this,SLOT(slotLoad()));
    connect(ui->ButtonGenerar,SIGNAL(clicked()),this,SLOT(slotClicked()));
}

/**
    @brief Método con el destructor de la interfaz gráfica
    @date 31/08/2016
*/
FormExportReport::~FormExportReport()
{
    delete ui;
}

/**
    @brief Método que permite mostrar el diálogo para seleccionar el nombre del reporte
    @date 31/08/2016
    @author Rodrigo Boet
*/
void FormExportReport::slotLoad()
{
    QString format = ".pdf";

    QString filename = QFileDialog::getSaveFileName(this,
            "Elija el nombre del reporte", QDir::homePath(),"*.pdf");

    filename.remove(format);

    filename +=format;

    ui->lineEdit->setText(filename);
}

/**
    @brief Método que valida al darle clic en generar y que emite una SIGNAL
    @date 31/08/2016
    @author Rodrigo Boet
*/
void FormExportReport::slotClicked()
{
    QString filename= ui->lineEdit->text();
    if(filename.isEmpty())
    {
        QMessageBox::critical(this, "Faltan datos",
                              "Debe seleccionar un archivo");
        return;
    }
    emit formAccepted(filename);
    close();
}
