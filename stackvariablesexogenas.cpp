#include "stackvariablesexogenas.h"
#include <QDebug>


stackVariablesExogenas::stackVariablesExogenas(QStringList Lista,QStringList Componentes,QList<int> inicio,
                                               QList<int> fin,QWidget *parent,int contar) :
    QWidget(parent)
{
    layoutMain = new QHBoxLayout;

    comboAccount = new QComboBox(this);

    stackedWidget = new QStackedWidget(this);

    QStringList nuevosComponentes;


    for (int i = 0;i < contar; ++i)
    {
        comboAccount->addItem(QString(Lista[i]));

        comboAccount->setObjectName(QString("CuentaExogena %1").arg(i + 1));

        nuevosComponentes = generarComponentes(Componentes,inicio[i],fin[i]);

        veWidget = new VariableExogenaWidget(i,nuevosComponentes,stackedWidget);

        stackedWidget->addWidget(veWidget);

        widgetList.append(veWidget);

    }

    //Aqui se agrega el apartado para todas las cuentas
    comboAccount->addItem("Todas las Cuentas");
    comboAccount->setObjectName(QString("CuentaExogenaFinal"));
    nuevosComponentes.clear();
    VariableExogenaWidget * widget = new VariableExogenaWidget(contar,nuevosComponentes,stackedWidget);
    widget->accounListWidget->setVisible(false);
    stackedWidget->addWidget(widget);
    widgetList.append(widget);

    layoutMain->addWidget(comboAccount);
    layoutMain->addWidget(stackedWidget);


    setLayout(layoutMain);

    connect(comboAccount, SIGNAL(activated(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}

QStringList stackVariablesExogenas::generarComponentes(QStringList Componentes, int inicio, int fin)
{
    QStringList mylista;
    inicio-=3;
    fin-=3;
    for(int i=inicio;i<=fin;i++)
    {
        mylista.append(Componentes[i]);
    }
    return mylista;
}
