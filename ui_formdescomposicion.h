/********************************************************************************
** Form generated from reading UI file 'formdescomposicion.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDESCOMPOSICION_H
#define UI_FORMDESCOMPOSICION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormDescomposicion
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listAgregar;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QListWidget *listSeleccionado;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_4;

    void setupUi(QWidget *FormDescomposicion)
    {
        if (FormDescomposicion->objectName().isEmpty())
            FormDescomposicion->setObjectName(QStringLiteral("FormDescomposicion"));
        FormDescomposicion->setWindowModality(Qt::ApplicationModal);
        FormDescomposicion->resize(756, 395);
        gridLayout_2 = new QGridLayout(FormDescomposicion);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FormDescomposicion);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 3, Qt::AlignHCenter);

        listAgregar = new QListWidget(FormDescomposicion);
        listAgregar->setObjectName(QStringLiteral("listAgregar"));

        gridLayout->addWidget(listAgregar, 2, 0, 4, 1);

        pushButton_3 = new QPushButton(FormDescomposicion);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(100, 30));
        pushButton_3->setMaximumSize(QSize(150, 16777215));
        pushButton_3->setStyleSheet(QStringLiteral("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px;"));
        pushButton_3->setDefault(false);

        gridLayout->addWidget(pushButton_3, 7, 2, 1, 1, Qt::AlignHCenter);

        label_3 = new QLabel(FormDescomposicion);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font-weight:bold;"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        listSeleccionado = new QListWidget(FormDescomposicion);
        listSeleccionado->setObjectName(QStringLiteral("listSeleccionado"));

        gridLayout->addWidget(listSeleccionado, 2, 2, 4, 1);

        pushButton_2 = new QPushButton(FormDescomposicion);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 30));
        pushButton_2->setMaximumSize(QSize(150, 30));
        pushButton_2->setStyleSheet(QStringLiteral("font-weight: bold; height: 30px; border: none; border-radius: 5px;"));
        pushButton_2->setFlat(true);

        gridLayout->addWidget(pushButton_2, 4, 1, 1, 1);

        pushButton = new QPushButton(FormDescomposicion);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(80, 30));
        pushButton->setMaximumSize(QSize(150, 30));
        pushButton->setStyleSheet(QStringLiteral("font-weight: bold; height: 30px; border: none; border-radius: 5px;"));
        pushButton->setFlat(true);

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        label_2 = new QLabel(FormDescomposicion);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font-weight:bold;"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(FormDescomposicion);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(100, 30));
        pushButton_4->setMaximumSize(QSize(150, 16777215));
        pushButton_4->setStyleSheet(QStringLiteral("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px;"));

        gridLayout->addWidget(pushButton_4, 7, 0, 1, 1, Qt::AlignHCenter);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(FormDescomposicion);

        QMetaObject::connectSlotsByName(FormDescomposicion);
    } // setupUi

    void retranslateUi(QWidget *FormDescomposicion)
    {
        FormDescomposicion->setWindowTitle(QApplication::translate("FormDescomposicion", "Descomposici\303\263n", 0));
        label->setText(QApplication::translate("FormDescomposicion", "Seleccione las dos (2) cuentas correspondientes con Actividad y Producto", 0));
        pushButton_3->setText(QApplication::translate("FormDescomposicion", "Seleccionar", 0));
        label_3->setText(QApplication::translate("FormDescomposicion", "Cuentas:", 0));
        pushButton_2->setText(QApplication::translate("FormDescomposicion", "<<", 0));
        pushButton->setText(QApplication::translate("FormDescomposicion", ">>", 0));
        label_2->setText(QApplication::translate("FormDescomposicion", "Cuentas Seleccionadas:", 0));
        pushButton_4->setText(QApplication::translate("FormDescomposicion", "Cancelar", 0));
    } // retranslateUi

};

namespace Ui {
    class FormDescomposicion: public Ui_FormDescomposicion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDESCOMPOSICION_H
