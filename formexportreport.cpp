#include "formexportreport.h"
#include "ui_formexportreport.h"

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

FormExportReport::~FormExportReport()
{
    delete ui;
}

void FormExportReport::slotLoad()
{
    QString format = ".pdf";

    QString filename = QFileDialog::getSaveFileName(this,
            "Elija el nombre del reporte", QDir::homePath(),"*.pdf");

    filename.remove(format);

    filename +=format;

    ui->lineEdit->setText(filename);
}

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
