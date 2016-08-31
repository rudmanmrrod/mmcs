#ifndef FORMCOMPARARRESULTADOS_H
#define FORMCOMPARARRESULTADOS_H

#include <QtWidgets>

namespace Ui {
class FormCompararResultados;
}

class FormCompararResultados : public QWidget
{
    Q_OBJECT

public:
    explicit FormCompararResultados(QWidget *parent = 0);
    Ui::FormCompararResultados *ui;
    ~FormCompararResultados();

};

#endif // FORMCOMPARARRESULTADOS_H
