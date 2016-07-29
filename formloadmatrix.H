#ifndef FORMLOADMATRIX_H
#define FORMLOADMATRIX_H

#include<QtGui>
#include<ui_formLoadMatrix.h>

class FormLoadMatrix : public QWidget
{
    Q_OBJECT


signals:
    void formAccepted(const QString &, int, int);

    void formClosed();

protected:
    void closeEvent(QCloseEvent *);

public:
    FormLoadMatrix(QWidget * parent = 0);
    Ui_FormLoadMatrix ui;

public slots:
    void slotLoadMatrixFile();

    void slotButtonAcceptClicked();

};

#endif // FORMLOADMATRIX_H
