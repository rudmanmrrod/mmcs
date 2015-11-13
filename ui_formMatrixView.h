/********************************************************************************
** Form generated from reading UI file 'formMatrixView.ui'
**
** Created: Mon Jun 22 16:27:52 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMATRIXVIEW_H
#define UI_FORMMATRIXVIEW_H

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

class Ui_FormMatrixView
{
public:
    QTableView *tableView;
    QGroupBox *Cuentas;
    QComboBox *comboBox;
    QStackedWidget *accountsStack;
    QWidget *page;
    QWidget *page_2;
    QPushButton *loadButton;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QWidget *tab_4;

    void setupUi(QWidget *FormMatrixView)
    {
        if (FormMatrixView->objectName().isEmpty())
            FormMatrixView->setObjectName(QString::fromUtf8("FormMatrixView"));
        FormMatrixView->resize(945, 627);
        tableView = new QTableView(FormMatrixView);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(20, 60, 701, 501));
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableView->setShowGrid(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        Cuentas = new QGroupBox(FormMatrixView);
        Cuentas->setObjectName(QString::fromUtf8("Cuentas"));
        Cuentas->setGeometry(QRect(750, 70, 181, 451));
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
        loadButton = new QPushButton(FormMatrixView);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(760, 500, 161, 51));
        tabWidget = new QTabWidget(FormMatrixView);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 941, 581));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        loadButton->raise();
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tabWidget->raise();
        tableView->raise();
        Cuentas->raise();
        loadButton->raise();

        retranslateUi(FormMatrixView);

        QMetaObject::connectSlotsByName(FormMatrixView);
    } // setupUi

    void retranslateUi(QWidget *FormMatrixView)
    {
        FormMatrixView->setWindowTitle(QApplication::translate("FormMatrixView", "MatrixView", 0, QApplication::UnicodeUTF8));
        Cuentas->setTitle(QApplication::translate("FormMatrixView", "Cuentas", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("FormMatrixView", "Finalizar Carga", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("FormMatrixView", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("FormMatrixView", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormMatrixView: public Ui_FormMatrixView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMATRIXVIEW_H
