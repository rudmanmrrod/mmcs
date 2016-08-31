#ifndef FORMEXPORTMATRIX_H
#define FORMEXPORTMATRIX_H

#include <QtWidgets>

namespace Ui {
class FormExportMatrix;
}

class FormExportMatrix : public QWidget
{
    Q_OBJECT

    
public:
    QLineEdit *MatrixName;
    QLineEdit *ExportLine;
    explicit FormExportMatrix(QWidget *parent = 0);
    ~FormExportMatrix();
    
private:
    Ui::FormExportMatrix *ui;
};

#endif // FORMEXPORTMATRIX_H
