#ifndef VARIABLEEXOGENAWIDGET_H
#define VARIABLEEXOGENAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>

class VariableExogenaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VariableExogenaWidget(int number, QStringList lista, QWidget *parent = 0);

    QHBoxLayout * layoutAccountConf;

    QListWidget * accounListWidget;

    
signals:
    
public slots:
    
};

#endif // VARIABLEEXOGENAWIDGET_H
