/********************************************************************************
** Form generated from reading UI file 'formpreciosnohomogeneos.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMPRECIOSNOHOMOGENEOS_H
#define UI_FORMPRECIOSNOHOMOGENEOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormPreciosNoHomogeneos
{
public:

    void setupUi(QWidget *FormPreciosNoHomogeneos)
    {
        if (FormPreciosNoHomogeneos->objectName().isEmpty())
            FormPreciosNoHomogeneos->setObjectName(QStringLiteral("FormPreciosNoHomogeneos"));
        FormPreciosNoHomogeneos->setWindowModality(Qt::ApplicationModal);
        FormPreciosNoHomogeneos->resize(635, 350);

        retranslateUi(FormPreciosNoHomogeneos);

        QMetaObject::connectSlotsByName(FormPreciosNoHomogeneos);
    } // setupUi

    void retranslateUi(QWidget *FormPreciosNoHomogeneos)
    {
        FormPreciosNoHomogeneos->setWindowTitle(QApplication::translate("FormPreciosNoHomogeneos", "Modelo de Precios No Homog\303\251neo", 0));
    } // retranslateUi

};

namespace Ui {
    class FormPreciosNoHomogeneos: public Ui_FormPreciosNoHomogeneos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMPRECIOSNOHOMOGENEOS_H
