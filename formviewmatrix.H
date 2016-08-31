#ifndef FORMVIEWMATRIX_H
#define FORMVIEWMATRIX_H

#include <QtWidgets>

namespace Ui {
class FormMatrixView;
}

class FormMatrixView : public QWidget
{
    Q_OBJECT

public:
    explicit FormMatrixView(QWidget *parent = 0);
    Ui::FormMatrixView *ui;

};

#endif // FORMVIEWMATRIX_H
