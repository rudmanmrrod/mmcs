#ifndef VARIABLEPNH_H
#define VARIABLEPNH_H

#include <QtGui>

class variablePNH : public QWidget
{
    Q_OBJECT
public:
    variablePNH(int number, QStringList lista, QWidget *parent = 0);

    QHBoxLayout * layoutAccountConf;

    QListWidget * accounListWidget;

signals:

public slots:
};

#endif // VARIABLEPNH_H
