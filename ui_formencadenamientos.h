/********************************************************************************
** Form generated from reading UI file 'formencadenamientos.ui'
**
** Created: Fri Aug 14 12:33:46 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMENCADENAMIENTOS_H
#define UI_FORMENCADENAMIENTOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormEncadenamientos
{
public:

    void setupUi(QWidget *FormEncadenamientos)
    {
        if (FormEncadenamientos->objectName().isEmpty())
            FormEncadenamientos->setObjectName(QString::fromUtf8("FormEncadenamientos"));
        FormEncadenamientos->resize(756, 395);

        retranslateUi(FormEncadenamientos);

        QMetaObject::connectSlotsByName(FormEncadenamientos);
    } // setupUi

    void retranslateUi(QWidget *FormEncadenamientos)
    {
        FormEncadenamientos->setWindowTitle(QApplication::translate("FormEncadenamientos", "Encadenamiento", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormEncadenamientos: public Ui_FormEncadenamientos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMENCADENAMIENTOS_H
