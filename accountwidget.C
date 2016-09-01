/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file accountwidget.cpp
    @brief Clases y métodos del widget que permite manipular las cuentas
    @date 10/05/2015
    @author José Ruiz
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "accountwidget.H"

/**
    @brief Clase principal que realiza la funcionalidad
    @date 10/05/2015
    @author José Ruiz
    @param <number> Recibe el número de widget a tratar
    @param <parent> Recibe el widget que será el padre
*/
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
    spinBoxAccountStart->setMaximum(9999);
    layoutAccountConf->addWidget(spinBoxAccountStart);

    labelAccountEnd = new QLabel(this);
    labelAccountEnd->setText("Fin");
    layoutAccountConf->addWidget(labelAccountEnd);

    spinBoxAccountEnd = new QSpinBox(this);
    spinBoxAccountEnd->setFixedWidth(100);
    spinBoxAccountEnd->setObjectName(QString("accountend %1").arg(number+1));//Nombre para el objeto Final de la Cuenta
    spinBoxAccountEnd->setMaximum(9999);
    layoutAccountConf->addWidget(spinBoxAccountEnd);

}
