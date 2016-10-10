#ifndef FORMCARGANDO_H
#define FORMCARGANDO_H

#include <QWidget>
#include <QtGui>

namespace Ui {
class FormCargando;
}

class FormCargando : public QWidget
{
    Q_OBJECT

public:
    explicit FormCargando(QWidget *parent = 0);
    ~FormCargando();

private:
    Ui::FormCargando *ui;
};

#endif // FORMCARGANDO_H
