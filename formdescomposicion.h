#ifndef FORMDESCOMPOSICION_H
#define FORMDESCOMPOSICION_H

#include <QtWidgets>
#include "ui_formdescomposicion.h"

namespace Ui {
class FormDescomposicion;
}

class FormDescomposicion : public QWidget
{
    Q_OBJECT

public:
    explicit FormDescomposicion(QWidget *parent = 0);
    Ui::FormDescomposicion *ui;
    ~FormDescomposicion();

private slots:
    void slotAgregar(QListWidgetItem *);
    void slotDeseleccionar(QListWidgetItem *);

private:

};



#endif // FORMDESCOMPOSICION_H
