#ifndef FORMCORTOPLAZO_H
#define FORMCORTOPLAZO_H

#include <QtWidgets>
#include "ui_formcortoplazo.h"

namespace Ui {
class FormCortoPlazo;
}

class FormCortoPlazo : public QWidget
{
    Q_OBJECT

public:
    explicit FormCortoPlazo(QWidget *parent = 0);
    Ui::FormCortoPlazo *ui;
    ~FormCortoPlazo();

private slots:
    void slotAgregar(QListWidgetItem *);
    void slotDeseleccionar(QListWidgetItem *);

private:

};

#endif // FORMCORTOPLAZO_H
