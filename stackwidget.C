/**
    Sistema de Manejo de Matrices de Contabilidad Social, desarrollado a partir de Mayo de 2015.
    @file stackencadenamientos.cpp
    @brief Clases y métodos del stack para las cuentas
    @date 20/05/2015
    @author José Ruiz
    @copyright <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU Public License versión 2 (GPLv2)</a>
*/
#include "stackwidget.H"

/**
    @brief Clase principal que realiza la funcionalidad
    @date 20/05/2015
    @author José Ruiz
    @param <accountNumber> Recibe el número de cuentas
    @param <parent> Recibe el widget que será el padre
*/
StackWidget::StackWidget(int accountNumber, QWidget *parent) :
    QWidget(parent)
{
    layoutMain = new QVBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    stackedWidget->setObjectName("StackAccount");

    for (int i = 0;i < accountNumber; ++i)
    {
        comboAccount->addItem(QString("Cuenta %1").arg(i + 1));

        comboAccount->setObjectName(QString("Cuenta %1").arg(i+1));

        AccountWidget * widget = new AccountWidget(i,stackedWidget);

        stackedWidget->addWidget(widget);

        widgetList.append(widget);

    }

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);


    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}

