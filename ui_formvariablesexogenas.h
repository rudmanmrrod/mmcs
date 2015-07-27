/********************************************************************************
** Form generated from reading UI file 'formvariablesexogenas.ui'
**
** Created: Fri Jul 3 17:13:17 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMVARIABLESEXOGENAS_H
#define UI_FORMVARIABLESEXOGENAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormVariablesExogenas
{
public:

    void setupUi(QWidget *FormVariablesExogenas)
    {
        if (FormVariablesExogenas->objectName().isEmpty())
            FormVariablesExogenas->setObjectName(QString::fromUtf8("FormVariablesExogenas"));
        FormVariablesExogenas->setWindowModality(Qt::ApplicationModal);
        FormVariablesExogenas->resize(766, 378);

        retranslateUi(FormVariablesExogenas);

        QMetaObject::connectSlotsByName(FormVariablesExogenas);
    } // setupUi

    void retranslateUi(QWidget *FormVariablesExogenas)
    {
        FormVariablesExogenas->setWindowTitle(QApplication::translate("FormVariablesExogenas", "Defina Variables Ex\303\263genas", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormVariablesExogenas: public Ui_FormVariablesExogenas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMVARIABLESEXOGENAS_H
