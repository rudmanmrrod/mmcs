/********************************************************************************
** Form generated from reading UI file 'formViewMatrix.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMVIEWMATRIX_H
#define UI_FORMVIEWMATRIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

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
            FormMatrixView->setObjectName(QStringLiteral("FormMatrixView"));
        FormMatrixView->resize(945, 627);
        tableView = new QTableView(FormMatrixView);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(20, 60, 701, 501));
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableView->setShowGrid(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        Cuentas = new QGroupBox(FormMatrixView);
        Cuentas->setObjectName(QStringLiteral("Cuentas"));
        Cuentas->setGeometry(QRect(750, 70, 181, 451));
        Cuentas->setAutoFillBackground(false);
        Cuentas->setFlat(false);
        Cuentas->setCheckable(false);
        comboBox = new QComboBox(Cuentas);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 30, 161, 27));
        accountsStack = new QStackedWidget(Cuentas);
        accountsStack->setObjectName(QStringLiteral("accountsStack"));
        accountsStack->setGeometry(QRect(10, 60, 133, 49));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        accountsStack->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        accountsStack->addWidget(page_2);
        loadButton = new QPushButton(FormMatrixView);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(760, 500, 161, 51));
        tabWidget = new QTabWidget(FormMatrixView);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 941, 581));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tabWidget->raise();
        tableView->raise();
        Cuentas->raise();
        loadButton->raise();

        retranslateUi(FormMatrixView);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormMatrixView);
    } // setupUi

    void retranslateUi(QWidget *FormMatrixView)
    {
        FormMatrixView->setWindowTitle(QApplication::translate("FormMatrixView", "MatrixView", 0));
        Cuentas->setTitle(QApplication::translate("FormMatrixView", "Cuentas", 0));
        loadButton->setText(QApplication::translate("FormMatrixView", "Finalizar Carga", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("FormMatrixView", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("FormMatrixView", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class FormMatrixView: public Ui_FormMatrixView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMVIEWMATRIX_H
