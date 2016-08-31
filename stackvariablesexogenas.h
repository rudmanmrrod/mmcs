#ifndef STACKVARIABLESEXOGENAS_H
#define STACKVARIABLESEXOGENAS_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtWidgets>
#include <QStackedWidget>
#include <QList>
#include <QComboBox>
#include <variableexogenawidget.h>

class stackVariablesExogenas : public QWidget
{
    Q_OBJECT
public:
    stackVariablesExogenas(QStringList Lista, QStringList Componentes,QList<int> inicio,QList<int> fin, QWidget *parent = 0, int contar = 0);

    QStackedWidget * stackedWidget;

    QList<QWidget *> widgetList;

    QHBoxLayout * layoutMain;

    QComboBox * comboAccount;

    VariableExogenaWidget *veWidget;

    QStringList generarComponentes(QStringList Componentes, int inicio, int fin);
    
signals:
    
public slots:
    
};

#endif // STACKVARIABLESEXOGENAS_H
