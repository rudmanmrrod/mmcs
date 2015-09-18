#ifndef FORMINCIDENCIAI_H
#define FORMINCIDENCIAI_H

#include <QWidget>

namespace Ui {
class FormIncidenciaI;
}

class FormIncidenciaI : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormIncidenciaI(QWidget *parent = 0);
    Ui::FormIncidenciaI *ui;
    ~FormIncidenciaI();
    
};

#endif // FORMINCIDENCIAI_H
