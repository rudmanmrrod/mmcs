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
    void formAccepted(QString,bool);

public slots:
    void slotLoad();
    void slotClicked();
    void slotLoadGraphic();
    void slotClickedGraphic();
private:

};

#endif // FORMEXPORTREPORT_H
