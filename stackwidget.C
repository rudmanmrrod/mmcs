#include "stackwidget.H"

StackWidget::StackWidget(int accountNumber, QWidget *parent) :
    QWidget(parent)
{
    layoutMain = new QVBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    for (int i = 0;i < accountNumber; ++i)
    {
        comboAccount->addItem(QString("Cuenta %1").arg(i + 1));

        AccountWidget * widget = new AccountWidget(stackedWidget);

        stackedWidget->addWidget(widget);

        widgetList.append(widget);

    }

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);

    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}

