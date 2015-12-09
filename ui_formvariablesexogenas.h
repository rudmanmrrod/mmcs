/********************************************************************************
** Form generated from reading UI file 'formvariablesexogenas.ui'
**
** Created: Thu Aug 6 16:13:25 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMVARIABLESEXOGENAS_H
#define UI_FORMVARIABLESEXOGENAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormVariablesExogenas
{
public:

    void setupUi(QWidget *FormVariablesExogenas)
    {
        if (FormVariablesExogenas->objectName().isEmpty())
            FormVariablesExogenas->setObjectName(QString::fromUtf8("FormVariablesExogenas"));
        FormVariablesExogenas->setWindowModality(Qt::ApplicationModal);
        FormVariablesExogenas->resize(697, 345);

        retranslateUi(FormVariablesExogenas);

        QMetaObject::connectSlotsByName(FormVariablesExogenas);
    } // setupUi

    void retranslateUi(QWidget *FormVariablesExogenas)
    {
        FormVariablesExogenas->setWindowTitle(QApplication::translate("FormVariablesExogenas", "Defina Variables Ex\303\263genas", 0));
    } // retranslateUi

};

namespace Ui {
    class FormVariablesExogenas: public Ui_FormVariablesExogenas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMVARIABLESEXOGENAS_H
