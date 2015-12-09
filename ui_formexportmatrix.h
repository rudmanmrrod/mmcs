/********************************************************************************
** Form generated from reading UI file 'formexportmatrix.ui'
**
** Created: Thu Aug 6 16:23:38 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMEXPORTMATRIX_H
#define UI_FORMEXPORTMATRIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormExportMatrix
{
public:

    void setupUi(QWidget *FormExportMatrix)
    {
        if (FormExportMatrix->objectName().isEmpty())
            FormExportMatrix->setObjectName(QString::fromUtf8("FormExportMatrix"));
        FormExportMatrix->setWindowModality(Qt::ApplicationModal);
        FormExportMatrix->resize(650, 336);

        retranslateUi(FormExportMatrix);

        QMetaObject::connectSlotsByName(FormExportMatrix);
    } // setupUi

    void retranslateUi(QWidget *FormExportMatrix)
    {
        FormExportMatrix->setWindowTitle(QApplication::translate("FormExportMatrix", "Exportar Matriz", 0));
    } // retranslateUi

};

namespace Ui {
    class FormExportMatrix: public Ui_FormExportMatrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMEXPORTMATRIX_H
