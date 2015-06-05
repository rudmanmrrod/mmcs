#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include <QList>
#include <QComboBox>
#include <accountwidget.H>

class StackWidget : public QWidget
{
Q_OBJECT

    QStackedWidget * stackedWidget;

    QList<QWidget *> widgetList;

    QVBoxLayout * layoutMain;

    QComboBox * comboAccount;


public:
    StackWidget(int accountNumber, QWidget *parent = 0);

signals:

public slots:

};

#endif // STACKWIDGET_H
