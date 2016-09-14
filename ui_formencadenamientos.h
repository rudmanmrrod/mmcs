/********************************************************************************
** Form generated from reading UI file 'formencadenamientos.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMENCADENAMIENTOS_H
#define UI_FORMENCADENAMIENTOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormEncadenamientos
{
public:

    void setupUi(QWidget *FormEncadenamientos)
    {
        if (FormEncadenamientos->objectName().isEmpty())
            FormEncadenamientos->setObjectName(QStringLiteral("FormEncadenamientos"));
        FormEncadenamientos->setWindowModality(Qt::ApplicationModal);
        FormEncadenamientos->resize(756, 395);

        retranslateUi(FormEncadenamientos);

        QMetaObject::connectSlotsByName(FormEncadenamientos);
    } // setupUi

    void retranslateUi(QWidget *FormEncadenamientos)
    {
        FormEncadenamientos->setWindowTitle(QApplication::translate("FormEncadenamientos", "Encadenamiento", 0));
    } // retranslateUi

};

namespace Ui {
    class FormEncadenamientos: public Ui_FormEncadenamientos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMENCADENAMIENTOS_H
