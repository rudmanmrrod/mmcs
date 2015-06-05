#include "accountwidget.H"

AccountWidget::AccountWidget(QWidget *parent) :
    QWidget(parent)
{

    layoutAccountConf = new QVBoxLayout;

    this->setLayout(layoutAccountConf);

    labelAccountName = new QLabel(this);
    labelAccountName->setText("Nombre");
    layoutAccountConf->addWidget(labelAccountName);

    lineEditAccountName = new QLineEdit(this);
    lineEditAccountName->setFixedWidth(200);
    layoutAccountConf->addWidget(lineEditAccountName);

    labelAccountStart = new QLabel(this);
    labelAccountStart->setText("Inicio");
    layoutAccountConf->addWidget(labelAccountStart);

    spinBoxAccountStart = new QSpinBox(this);
    spinBoxAccountStart->setFixedWidth(100);
    layoutAccountConf->addWidget(spinBoxAccountStart);

    labelAccountEnd = new QLabel(this);
    labelAccountEnd->setText("Fin");
    layoutAccountConf->addWidget(labelAccountEnd);

    spinBoxAccountEnd = new QSpinBox(this);
    spinBoxAccountEnd->setFixedWidth(100);
    layoutAccountConf->addWidget(spinBoxAccountEnd);

}
