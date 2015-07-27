/********************************************************************************
** Form generated from reading UI file 'tabwidget.ui'
**
** Created: Mon Jun 22 16:27:52 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABWIDGET_H
#define UI_TABWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabWidget
{
public:
    QWidget *tab;
    QTableView *tableView;
    QPushButton *loadButton;
    QGroupBox *Cuentas;
    QComboBox *comboBox;
    QStackedWidget *accountsStack;
    QWidget *page;
    QWidget *page_2;
    QWidget *tab1;

    void setupUi(QTabWidget *TabWidget)
    {
        if (TabWidget->objectName().isEmpty())
            TabWidget->setObjectName(QString::fromUtf8("TabWidget"));
        TabWidget->resize(918, 565);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 10, 701, 501));
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableView->setShowGrid(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        loadButton = new QPushButton(tab);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(730, 460, 161, 51));
        Cuentas = new QGroupBox(tab);
        Cuentas->setObjectName(QString::fromUtf8("Cuentas"));
        Cuentas->setGeometry(QRect(720, 30, 181, 451));
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
        TabWidget->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        TabWidget->addTab(tab1, QString());

        retranslateUi(TabWidget);

        TabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TabWidget);
    } // setupUi

    void retranslateUi(QTabWidget *TabWidget)
    {
        TabWidget->setWindowTitle(QApplication::translate("TabWidget", "TabWidget", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("TabWidget", "Finalizar Carga", 0, QApplication::UnicodeUTF8));
        Cuentas->setTitle(QApplication::translate("TabWidget", "Cuentas", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(tab), QApplication::translate("TabWidget", "Tab 1", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(tab1), QApplication::translate("TabWidget", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TabWidget: public Ui_TabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABWIDGET_H
