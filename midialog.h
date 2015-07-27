#ifndef MIDIALOG_H
#define MIDIALOG_H

#include <QDialog>

namespace Ui {
class miDialog;
}

class miDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit miDialog(QWidget *parent = 0);
    ~miDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::miDialog *ui;
};

#endif // MIDIALOG_H
