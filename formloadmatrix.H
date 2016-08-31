#ifndef FORMLOADMATRIX_H
#define FORMLOADMATRIX_H

#include <QtWidgets>

namespace Ui {
class FormLoadMatrix;
}

class FormLoadMatrix : public QWidget
{
    Q_OBJECT


signals:
    void formAccepted(const QString &, int, int);

    void formClosed();

protected:
    void closeEvent(QCloseEvent *);

public:
    explicit FormLoadMatrix(QWidget * parent = 0);
    Ui::FormLoadMatrix *ui;

public slots:
    void slotLoadMatrixFile();

    void slotButtonAcceptClicked();

};

#endif // FORMLOADMATRIX_H
