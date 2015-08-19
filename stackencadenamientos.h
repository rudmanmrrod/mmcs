#ifndef STACKENCADENAMIENTOS_H
#define STACKENCADENAMIENTOS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QList>
#include <QComboBox>
#include <encadenamientoswidget.h>


class stackEncadenamientos : public QWidget
{
    Q_OBJECT
public:
    explicit stackEncadenamientos(QMap<QString,QStringList> Cuentas,QWidget *parent = 0);

    QStackedWidget * stackedWidget;
    QList<QWidget *> widgetList;
    QHBoxLayout * layoutMain;
    QComboBox * comboAccount;
    EncadenamientosWidget *encadenamientosWidget;
    
signals:
    
public slots:
    
};

#endif // STACKENCADENAMIENTOS_H
