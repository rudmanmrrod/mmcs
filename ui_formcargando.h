/********************************************************************************
** Form generated from reading UI file 'formcargando.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCARGANDO_H
#define UI_FORMCARGANDO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormCargando
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *FormCargando)
    {
        if (FormCargando->objectName().isEmpty())
            FormCargando->setObjectName(QStringLiteral("FormCargando"));
        FormCargando->setWindowModality(Qt::ApplicationModal);
        FormCargando->setEnabled(true);
        FormCargando->resize(170, 51);
        gridLayout_2 = new QGridLayout(FormCargando);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FormCargando);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1, Qt::AlignHCenter);

        label_2 = new QLabel(FormCargando);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("color: #358ccb; font-weight: bold;"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(FormCargando);

        QMetaObject::connectSlotsByName(FormCargando);
    } // setupUi

    void retranslateUi(QWidget *FormCargando)
    {
        FormCargando->setWindowTitle(QApplication::translate("FormCargando", "Cargando..", 0));
        label->setText(QApplication::translate("FormCargando", "TextLabel", 0));
        label_2->setText(QApplication::translate("FormCargando", "Cargando...", 0));
    } // retranslateUi

};

namespace Ui {
    class FormCargando: public Ui_FormCargando {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCARGANDO_H
