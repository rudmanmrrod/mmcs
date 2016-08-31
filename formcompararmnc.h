#ifndef FORMCOMPARARMNC_H
#define FORMCOMPARARMNC_H

#include <QtWidgets>

namespace Ui {
class FormCompararMNC;
}

class FormCompararMNC : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormCompararMNC(QWidget *parent = 0);
    Ui::FormCompararMNC *ui;
    ~FormCompararMNC();

};

#endif // FORMCOMPARARMNC_H
