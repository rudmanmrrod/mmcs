#ifndef FORMLOADMATRIX_H
#define FORMLOADMATRIX_H

#include<QtGui>
#include<ui_formLoadMatrix.h>

class FormLoadMatrix : public QWidget
{
    Q_OBJECT

    Ui_FormLoadMatrix ui;

signals:
    void formAccepted(const QString &, int, int);

    void formClosed();

protected:
    void closeEvent(QCloseEvent *);

public:
    FormLoadMatrix(QWidget * parent = 0);

public slots:
    void slotLoadMatrixFile();

    void slotButtonAcceptClicked();

};

#endif // FORMLOADMATRIX_H
