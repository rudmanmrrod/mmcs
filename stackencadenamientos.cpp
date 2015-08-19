#include "stackencadenamientos.h"

stackEncadenamientos::stackEncadenamientos(QMap<QString,QStringList> Cuentas, QWidget *parent):
    QWidget(parent)
{
    layoutMain = new QHBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    QStringList Componentes;

    int i= 0;
    foreach(QString key,Cuentas.keys())
    {
        comboAccount->addItem(QString(key));

        comboAccount->setObjectName(QString("CuentaExogena %1").arg(i+1));

        Componentes = Cuentas[key];

        encadenamientosWidget = new EncadenamientosWidget(i,Componentes,stackedWidget);

        stackedWidget->addWidget(encadenamientosWidget);

        widgetList.append(encadenamientosWidget);

        i++;

    }

    comboAccount->addItem("Sub-Matriz Endógena-Endógena");
    comboAccount->setObjectName(QString("SubMatrizEndogenaEndogena"));
    Componentes.clear();
    encadenamientosWidget = new EncadenamientosWidget(i,Componentes,stackedWidget);
    encadenamientosWidget->encadenamientosListWidget->setVisible(false);
    stackedWidget->addWidget(encadenamientosWidget);
    widgetList.append(encadenamientosWidget);

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);


    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}
