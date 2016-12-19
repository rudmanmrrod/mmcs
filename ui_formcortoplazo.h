/********************************************************************************
** Form generated from reading UI file 'formcortoplazo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCORTOPLAZO_H
#define UI_FORMCORTOPLAZO_H

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

class Ui_FormCortoPlazo
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

    void setupUi(QWidget *FormCortoPlazo)
    {
        if (FormCortoPlazo->objectName().isEmpty())
            FormCortoPlazo->setObjectName(QStringLiteral("FormCortoPlazo"));
        FormCortoPlazo->setWindowModality(Qt::ApplicationModal);
        FormCortoPlazo->resize(756, 395);
        gridLayout_2 = new QGridLayout(FormCortoPlazo);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FormCortoPlazo);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 3, Qt::AlignHCenter);

        listAgregar = new QListWidget(FormCortoPlazo);
        new QListWidgetItem(listAgregar);
        new QListWidgetItem(listAgregar);
        new QListWidgetItem(listAgregar);
        new QListWidgetItem(listAgregar);
        new QListWidgetItem(listAgregar);
        listAgregar->setObjectName(QStringLiteral("listAgregar"));

        gridLayout->addWidget(listAgregar, 2, 0, 4, 1);

        pushButton_3 = new QPushButton(FormCortoPlazo);
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

        label_3 = new QLabel(FormCortoPlazo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font-weight:bold;"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        listSeleccionado = new QListWidget(FormCortoPlazo);
        listSeleccionado->setObjectName(QStringLiteral("listSeleccionado"));

        gridLayout->addWidget(listSeleccionado, 2, 2, 4, 1);

        pushButton_2 = new QPushButton(FormCortoPlazo);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 30));
        pushButton_2->setMaximumSize(QSize(150, 30));
        pushButton_2->setStyleSheet(QStringLiteral("font-weight: bold; height: 30px; border: none; border-radius: 5px;"));
        pushButton_2->setFlat(true);

        gridLayout->addWidget(pushButton_2, 4, 1, 1, 1);

        pushButton = new QPushButton(FormCortoPlazo);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(80, 30));
        pushButton->setMaximumSize(QSize(150, 30));
        pushButton->setStyleSheet(QStringLiteral("font-weight: bold; height: 30px; border: none; border-radius: 5px;"));
        pushButton->setFlat(true);

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        label_2 = new QLabel(FormCortoPlazo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font-weight:bold;"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(FormCortoPlazo);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(100, 30));
        pushButton_4->setMaximumSize(QSize(150, 16777215));
        pushButton_4->setStyleSheet(QStringLiteral("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px;"));

        gridLayout->addWidget(pushButton_4, 7, 0, 1, 1, Qt::AlignHCenter);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(FormCortoPlazo);

        QMetaObject::connectSlotsByName(FormCortoPlazo);
    } // setupUi

    void retranslateUi(QWidget *FormCortoPlazo)
    {
        FormCortoPlazo->setWindowTitle(QApplication::translate("FormCortoPlazo", "Evaluar Escenario", 0));
        label->setText(QApplication::translate("FormCortoPlazo", "Seleccione las matrices que desea utilizar", 0));

        const bool __sortingEnabled = listAgregar->isSortingEnabled();
        listAgregar->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listAgregar->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("FormCortoPlazo", "I", 0));
        QListWidgetItem *___qlistwidgetitem1 = listAgregar->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("FormCortoPlazo", "T", 0));
        QListWidgetItem *___qlistwidgetitem2 = listAgregar->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("FormCortoPlazo", "O", 0));
        QListWidgetItem *___qlistwidgetitem3 = listAgregar->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("FormCortoPlazo", "C", 0));
        listAgregar->setSortingEnabled(__sortingEnabled);

        pushButton_3->setText(QApplication::translate("FormCortoPlazo", "Seleccionar", 0));
        label_3->setText(QApplication::translate("FormCortoPlazo", "Matrices:", 0));
        pushButton_2->setText(QApplication::translate("FormCortoPlazo", "<<", 0));
        pushButton->setText(QApplication::translate("FormCortoPlazo", ">>", 0));
        label_2->setText(QApplication::translate("FormCortoPlazo", "Matrices Seleccionadas:", 0));
        pushButton_4->setText(QApplication::translate("FormCortoPlazo", "Cancelar", 0));
    } // retranslateUi

};

namespace Ui {
    class FormCortoPlazo: public Ui_FormCortoPlazo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCORTOPLAZO_H
