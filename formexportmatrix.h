#ifndef FORMEXPORTMATRIX_H
#define FORMEXPORTMATRIX_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class FormExportMatrix;
}

class FormExportMatrix : public QWidget
{
    Q_OBJECT

    
public:
    QLineEdit *ExportLine;
    QComboBox *Exportcb;
    explicit FormExportMatrix(QWidget *parent = 0);
    ~FormExportMatrix();
    
private:
    Ui::FormExportMatrix *ui;
};

#endif // FORMEXPORTMATRIX_H
