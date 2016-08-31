#ifndef FORMEXPORTREPORT_H
#define FORMEXPORTREPORT_H

#include <QtWidgets>

namespace Ui {
class FormExportReport;
}

class FormExportReport : public QWidget
{
    Q_OBJECT

public:
    explicit FormExportReport(QWidget *parent = 0);
    Ui::FormExportReport *ui;
    ~FormExportReport();
signals:
    void formAccepted(QString);

public slots:
    void slotLoad();
    void slotClicked();

private:

};

#endif // FORMEXPORTREPORT_H
