/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created: Mon Jun 22 16:40:39 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWIdget
{
public:
    QWidget *tab;
    QTableView *tableView;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QGroupBox *Cuentas;
    QComboBox *comboBox;
    QStackedWidget *accountsStack;
    QWidget *page;
    QWidget *page_2;
    QSpacerItem *verticalSpacer;
    QPushButton *loadButton;
    QWidget *tab1;

    void setupUi(QTabWidget *MainWIdget)
    {
        if (MainWIdget->objectName().isEmpty())
            MainWIdget->setObjectName(QString::fromUtf8("MainWIdget"));
        MainWIdget->resize(925, 574);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 20, 701, 501));
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableView->setShowGrid(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        widget = new QWidget(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(tab);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(740, 30, 161, 461));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Cuentas = new QGroupBox(widget1);
        Cuentas->setObjectName(QString::fromUtf8("Cuentas"));
        Cuentas->setAutoFillBackground(false);
        Cuentas->setFlat(false);
        Cuentas->setCheckable(false);
        comboBox = new QComboBox(Cuentas);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 30, 161, 27));
        accountsStack = new QStackedWidget(Cuentas);
        accountsStack->setObjectName(QString::fromUtf8("accountsStack"));
        accountsStack->setGeometry(QRect(10, 60, 133, 49));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        accountsStack->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        accountsStack->addWidget(page_2);
        comboBox->raise();
        accountsStack->raise();

        verticalLayout->addWidget(Cuentas);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        loadButton = new QPushButton(widget1);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        verticalLayout->addWidget(loadButton);

        MainWIdget->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        MainWIdget->addTab(tab1, QString());

        retranslateUi(MainWIdget);

        QMetaObject::connectSlotsByName(MainWIdget);
    } // setupUi

    void retranslateUi(QTabWidget *MainWIdget)
    {
        MainWIdget->setWindowTitle(QApplication::translate("MainWIdget", "TabWidget", 0, QApplication::UnicodeUTF8));
        Cuentas->setTitle(QApplication::translate("MainWIdget", "Cuentas", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("MainWIdget", "Finalizar Carga", 0, QApplication::UnicodeUTF8));
        MainWIdget->setTabText(MainWIdget->indexOf(tab), QApplication::translate("MainWIdget", "Tab 1", 0, QApplication::UnicodeUTF8));
        MainWIdget->setTabText(MainWIdget->indexOf(tab1), QApplication::translate("MainWIdget", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWIdget: public Ui_MainWIdget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
