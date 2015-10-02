/*
    realizado por José Ruiz en Mayo de 2015
    modificado por Rodrigo Boet
*/
#include "accountwidget.H"

AccountWidget::AccountWidget(int number,QWidget *parent) :
    QWidget(parent)
{

    layoutAccountConf = new QVBoxLayout;

    this->setLayout(layoutAccountConf);

    labelAccountName = new QLabel(this);
    labelAccountName->setText("Nombre");
    layoutAccountConf->addWidget(labelAccountName);

    lineEditAccountName = new QLineEdit(this);
    lineEditAccountName->setFixedWidth(200);
    lineEditAccountName->setObjectName(QString("linedit %1").arg(number+1));//Nombre para el objeto Nombre de la Cuenta
    layoutAccountConf->addWidget(lineEditAccountName);

    labelAccountStart = new QLabel(this);
    labelAccountStart->setText("Inicio");
    layoutAccountConf->addWidget(labelAccountStart);

    spinBoxAccountStart = new QSpinBox(this);
    spinBoxAccountStart->setFixedWidth(100);
    spinBoxAccountStart->setObjectName(QString("accountstart %1").arg(number+1));//Nombre para el objeto Comienzo de la Cuenta
    layoutAccountConf->addWidget(spinBoxAccountStart);

    labelAccountEnd = new QLabel(this);
    labelAccountEnd->setText("Fin");
    layoutAccountConf->addWidget(labelAccountEnd);

    spinBoxAccountEnd = new QSpinBox(this);
    spinBoxAccountEnd->setFixedWidth(100);
    spinBoxAccountEnd->setObjectName(QString("accountend %1").arg(number+1));//Nombre para el objeto Final de la Cuenta
    layoutAccountConf->addWidget(spinBoxAccountEnd);

}
