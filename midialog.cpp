#include "midialog.h"
#include "ui_midialog.h"

miDialog::miDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::miDialog)
{
    ui->setupUi(this);
}

miDialog::~miDialog()
{
    delete ui;
}

void miDialog::on_pushButton_clicked()
{

}
