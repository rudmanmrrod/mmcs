#ifndef FORMENCADENAMIENTOS_H
#define FORMENCADENAMIENTOS_H

#include <QtWidgets>

namespace Ui {
class FormEncadenamientos;
}

class FormEncadenamientos : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormEncadenamientos(QWidget *parent = 0);
    ~FormEncadenamientos();
    
private:
    Ui::FormEncadenamientos *ui;
};

#endif // FORMENCADENAMIENTOS_H
