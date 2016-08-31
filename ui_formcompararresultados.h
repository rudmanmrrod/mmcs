/********************************************************************************
** Form generated from reading UI file 'formcompararresultados.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCOMPARARRESULTADOS_H
#define UI_FORMCOMPARARRESULTADOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormCompararResultados
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *resultadosListWidget;
    QPushButton *buttonVerResultados;

    void setupUi(QWidget *FormCompararResultados)
    {
        if (FormCompararResultados->objectName().isEmpty())
            FormCompararResultados->setObjectName(QStringLiteral("FormCompararResultados"));
        FormCompararResultados->setWindowModality(Qt::ApplicationModal);
        FormCompararResultados->resize(569, 301);
        horizontalLayout = new QHBoxLayout(FormCompararResultados);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        resultadosListWidget = new QListWidget(FormCompararResultados);
        resultadosListWidget->setObjectName(QStringLiteral("resultadosListWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resultadosListWidget->sizePolicy().hasHeightForWidth());
        resultadosListWidget->setSizePolicy(sizePolicy);
        resultadosListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        horizontalLayout->addWidget(resultadosListWidget);

        buttonVerResultados = new QPushButton(FormCompararResultados);
        buttonVerResultados->setObjectName(QStringLiteral("buttonVerResultados"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonVerResultados->sizePolicy().hasHeightForWidth());
        buttonVerResultados->setSizePolicy(sizePolicy1);
        buttonVerResultados->setMinimumSize(QSize(100, 0));
        buttonVerResultados->setStyleSheet(QLatin1String("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px;\n"
""));

        horizontalLayout->addWidget(buttonVerResultados);


        retranslateUi(FormCompararResultados);

        QMetaObject::connectSlotsByName(FormCompararResultados);
    } // setupUi

    void retranslateUi(QWidget *FormCompararResultados)
    {
        FormCompararResultados->setWindowTitle(QApplication::translate("FormCompararResultados", "Comparar Resultados", 0));
        buttonVerResultados->setText(QApplication::translate("FormCompararResultados", "&Ver", 0));
    } // retranslateUi

};

namespace Ui {
    class FormCompararResultados: public Ui_FormCompararResultados {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCOMPARARRESULTADOS_H
