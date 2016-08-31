#ifndef ENCADENAMIENTOSWIDGET_H
#define ENCADENAMIENTOSWIDGET_H

#include <QtWidgets>


class EncadenamientosWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EncadenamientosWidget(int number,QStringList lista,QWidget *parent = 0);
    QHBoxLayout * layoutEncadenamientos;
    QListWidget * encadenamientosListWidget;
    
signals:
    
public slots:
    
};

#endif // ENCADENAMIENTOSWIDGET_H
