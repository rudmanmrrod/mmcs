/********************************************************************************
** Form generated from reading UI file 'formcompararresultados.ui'
**
** Created: Fri Sep 4 09:56:44 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCOMPARARRESULTADOS_H
#define UI_FORMCOMPARARRESULTADOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

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
            FormCompararResultados->setObjectName(QString::fromUtf8("FormCompararResultados"));
        FormCompararResultados->setWindowModality(Qt::ApplicationModal);
        FormCompararResultados->resize(569, 301);
        horizontalLayout = new QHBoxLayout(FormCompararResultados);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        resultadosListWidget = new QListWidget(FormCompararResultados);
        resultadosListWidget->setObjectName(QString::fromUtf8("resultadosListWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resultadosListWidget->sizePolicy().hasHeightForWidth());
        resultadosListWidget->setSizePolicy(sizePolicy);
        resultadosListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        horizontalLayout->addWidget(resultadosListWidget);

        buttonVerResultados = new QPushButton(FormCompararResultados);
        buttonVerResultados->setObjectName(QString::fromUtf8("buttonVerResultados"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonVerResultados->sizePolicy().hasHeightForWidth());
        buttonVerResultados->setSizePolicy(sizePolicy1);
        buttonVerResultados->setMinimumSize(QSize(100, 0));
        buttonVerResultados->setStyleSheet(QString::fromUtf8("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px; margin-top: 40px;\n"
""));

        horizontalLayout->addWidget(buttonVerResultados);


        retranslateUi(FormCompararResultados);

        QMetaObject::connectSlotsByName(FormCompararResultados);
    } // setupUi

    void retranslateUi(QWidget *FormCompararResultados)
    {
        FormCompararResultados->setWindowTitle(QApplication::translate("FormCompararResultados", "Comparar Resultados", 0, QApplication::UnicodeUTF8));
        buttonVerResultados->setText(QApplication::translate("FormCompararResultados", "&Ver", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormCompararResultados: public Ui_FormCompararResultados {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCOMPARARRESULTADOS_H
