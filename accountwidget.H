#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>

class AccountWidget : public QWidget
{
Q_OBJECT
public:
    explicit AccountWidget(int number=0, QWidget *parent = 0);


    QVBoxLayout * layoutAccountConf;

    QLabel * labelAccountName;

    QLineEdit * lineEditAccountName;

    QLabel * labelAccountStart;

    QSpinBox * spinBoxAccountStart;

    QLabel *labelAccountEnd;

    QSpinBox * spinBoxAccountEnd;


signals:

public slots:

};

#endif // ACCOUNTWIDGET_H
