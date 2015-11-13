#ifndef STACKPRECIOSNOHOMOGENEOS_H
#define STACKPRECIOSNOHOMOGENEOS_H

#include <QtGui>
#include <QStringList>
#include <variablepnh.h>

class StackPreciosNoHomogeneos : public QWidget
{
    Q_OBJECT
public:
    StackPreciosNoHomogeneos(QMap<QString,QStringList> Cuentas, QWidget *parent=0);

    QStackedWidget * stackedWidget;

    QList<QWidget *> widgetList;

    QHBoxLayout * layoutMain;

    QComboBox * comboAccount;

    variablePNH *varPNH;

signals:

public slots:
};

#endif // STACKPRECIOSNOHOMOGENEOS_H
