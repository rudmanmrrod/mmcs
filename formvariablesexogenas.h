#ifndef FORMVARIABLESEXOGENAS_H
#define FORMVARIABLESEXOGENAS_H

#include <QtWidgets>

namespace Ui {
class FormVariablesExogenas;
}

class FormVariablesExogenas : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormVariablesExogenas(QWidget *parent = 0);
    ~FormVariablesExogenas();

private:
    Ui::FormVariablesExogenas *ui;
};

#endif // FORMVARIABLESEXOGENAS_H
