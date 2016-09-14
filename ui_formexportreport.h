/********************************************************************************
** Form generated from reading UI file 'formexportreport.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMEXPORTREPORT_H
#define UI_FORMEXPORTREPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormExportReport
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QPushButton *ButtonGenerar;
    QLineEdit *lineEdit;
    QPushButton *ButtonCancelar;
    QPushButton *ButtonCargar;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;

    void setupUi(QWidget *FormExportReport)
    {
        if (FormExportReport->objectName().isEmpty())
            FormExportReport->setObjectName(QStringLiteral("FormExportReport"));
        FormExportReport->setWindowModality(Qt::WindowModal);
        FormExportReport->resize(728, 354);
        gridLayout_2 = new QGridLayout(FormExportReport);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FormExportReport);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        label_2 = new QLabel(FormExportReport);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        ButtonGenerar = new QPushButton(FormExportReport);
        ButtonGenerar->setObjectName(QStringLiteral("ButtonGenerar"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ButtonGenerar->sizePolicy().hasHeightForWidth());
        ButtonGenerar->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(ButtonGenerar, 6, 2, 1, 1);

        lineEdit = new QLineEdit(FormExportReport);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 3, 1, 1, 4);

        ButtonCancelar = new QPushButton(FormExportReport);
        ButtonCancelar->setObjectName(QStringLiteral("ButtonCancelar"));
        sizePolicy2.setHeightForWidth(ButtonCancelar->sizePolicy().hasHeightForWidth());
        ButtonCancelar->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(ButtonCancelar, 6, 4, 1, 1);

        ButtonCargar = new QPushButton(FormExportReport);
        ButtonCargar->setObjectName(QStringLiteral("ButtonCargar"));
        sizePolicy2.setHeightForWidth(ButtonCargar->sizePolicy().hasHeightForWidth());
        ButtonCargar->setSizePolicy(sizePolicy2);
        QIcon icon;
        icon.addFile(QStringLiteral(":/imgs/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonCargar->setIcon(icon);
        ButtonCargar->setFlat(true);

        gridLayout->addWidget(ButtonCargar, 3, 5, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        label_3 = new QLabel(FormExportReport);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QLatin1String("font-weight: bold;\n"
"color: #358ccb;\n"
""));

        gridLayout->addWidget(label_3, 2, 1, 1, 4);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(FormExportReport);

        QMetaObject::connectSlotsByName(FormExportReport);
    } // setupUi

    void retranslateUi(QWidget *FormExportReport)
    {
        FormExportReport->setWindowTitle(QApplication::translate("FormExportReport", "Exportar Reporte", 0));
        label->setText(QApplication::translate("FormExportReport", "Guardar Reporte", 0));
        label_2->setText(QApplication::translate("FormExportReport", "Archivo:", 0));
        ButtonGenerar->setText(QApplication::translate("FormExportReport", "Generar", 0));
        ButtonCancelar->setText(QApplication::translate("FormExportReport", "Cancelar", 0));
        ButtonCargar->setText(QString());
        label_3->setText(QApplication::translate("FormExportReport", "Seleccione la ruta para guardar el reporte.", 0));
    } // retranslateUi

};

namespace Ui {
    class FormExportReport: public Ui_FormExportReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMEXPORTREPORT_H
