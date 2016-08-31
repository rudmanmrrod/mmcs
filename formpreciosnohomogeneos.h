#ifndef FORMPRECIOSNOHOMOGENEOS_H
#define FORMPRECIOSNOHOMOGENEOS_H

#include <QtWidgets>

namespace Ui {
class FormPreciosNoHomogeneos;
}

class FormPreciosNoHomogeneos : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormPreciosNoHomogeneos(QWidget *parent = 0);
    ~FormPreciosNoHomogeneos();
    
private:
    Ui::FormPreciosNoHomogeneos *ui;
};

#endif // FORMPRECIOSNOHOMOGENEOS_H
