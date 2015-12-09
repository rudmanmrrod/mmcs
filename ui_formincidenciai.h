/********************************************************************************
** Form generated from reading UI file 'formincidenciai.ui'
**
** Created: Fri Sep 18 09:48:23 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMINCIDENCIAI_H
#define UI_FORMINCIDENCIAI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormIncidenciaI
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *TableIncidencia;
    QPushButton *CalcularIncidencia;

    void setupUi(QWidget *FormIncidenciaI)
    {
        if (FormIncidenciaI->objectName().isEmpty())
            FormIncidenciaI->setObjectName(QString::fromUtf8("FormIncidenciaI"));
        FormIncidenciaI->setWindowModality(Qt::ApplicationModal);
        FormIncidenciaI->resize(559, 230);
        horizontalLayout = new QHBoxLayout(FormIncidenciaI);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        TableIncidencia = new QTableWidget(FormIncidenciaI);
        TableIncidencia->setObjectName(QString::fromUtf8("TableIncidencia"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TableIncidencia->sizePolicy().hasHeightForWidth());
        TableIncidencia->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(TableIncidencia);

        CalcularIncidencia = new QPushButton(FormIncidenciaI);
        CalcularIncidencia->setObjectName(QString::fromUtf8("CalcularIncidencia"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(CalcularIncidencia->sizePolicy().hasHeightForWidth());
        CalcularIncidencia->setSizePolicy(sizePolicy1);
        CalcularIncidencia->setMinimumSize(QSize(100, 0));
        CalcularIncidencia->setStyleSheet(QString::fromUtf8("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px; "));

        horizontalLayout->addWidget(CalcularIncidencia);


        retranslateUi(FormIncidenciaI);

        QMetaObject::connectSlotsByName(FormIncidenciaI);
    } // setupUi

    void retranslateUi(QWidget *FormIncidenciaI)
    {
        FormIncidenciaI->setWindowTitle(QApplication::translate("FormIncidenciaI", "Seleccione la Variaci\303\263n", 0));
        CalcularIncidencia->setText(QApplication::translate("FormIncidenciaI", "&Calcular", 0));
    } // retranslateUi

};

namespace Ui {
    class FormIncidenciaI: public Ui_FormIncidenciaI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMINCIDENCIAI_H
