/********************************************************************************
** Form generated from reading UI file 'midialog.ui'
**
** Created: Mon Jun 22 11:08:01 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIDIALOG_H
#define UI_MIDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_miDialog
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *miDialog)
    {
        if (miDialog->objectName().isEmpty())
            miDialog->setObjectName(QString::fromUtf8("miDialog"));
        miDialog->resize(400, 300);
        pushButton = new QPushButton(miDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 250, 95, 31));

        retranslateUi(miDialog);

        QMetaObject::connectSlotsByName(miDialog);
    } // setupUi

    void retranslateUi(QDialog *miDialog)
    {
        miDialog->setWindowTitle(QApplication::translate("miDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("miDialog", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class miDialog: public Ui_miDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIDIALOG_H
