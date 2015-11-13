/********************************************************************************
** Form generated from reading UI file 'formcompararmnc.ui'
**
** Created: Fri Sep 11 10:44:46 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCOMPARARMNC_H
#define UI_FORMCOMPARARMNC_H

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

class Ui_FormCompararMNC
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listMNC;
    QPushButton *verMNC;

    void setupUi(QWidget *FormCompararMNC)
    {
        if (FormCompararMNC->objectName().isEmpty())
            FormCompararMNC->setObjectName(QString::fromUtf8("FormCompararMNC"));
        FormCompararMNC->setWindowModality(Qt::ApplicationModal);
        FormCompararMNC->resize(601, 330);
        horizontalLayout = new QHBoxLayout(FormCompararMNC);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listMNC = new QListWidget(FormCompararMNC);
        listMNC->setObjectName(QString::fromUtf8("listMNC"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(listMNC->sizePolicy().hasHeightForWidth());
        listMNC->setSizePolicy(sizePolicy);
        listMNC->setSelectionMode(QAbstractItemView::ExtendedSelection);

        horizontalLayout->addWidget(listMNC);

        verMNC = new QPushButton(FormCompararMNC);
        verMNC->setObjectName(QString::fromUtf8("verMNC"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(verMNC->sizePolicy().hasHeightForWidth());
        verMNC->setSizePolicy(sizePolicy1);
        verMNC->setMinimumSize(QSize(100, 0));
        verMNC->setStyleSheet(QString::fromUtf8("background-color: #358ccb; color: #fff; font-weight: bold; height: 30px; border: none; border-radius: 5px; "));

        horizontalLayout->addWidget(verMNC);


        retranslateUi(FormCompararMNC);

        QMetaObject::connectSlotsByName(FormCompararMNC);
    } // setupUi

    void retranslateUi(QWidget *FormCompararMNC)
    {
        FormCompararMNC->setWindowTitle(QApplication::translate("FormCompararMNC", "Comparar Resultados", 0, QApplication::UnicodeUTF8));
        verMNC->setText(QApplication::translate("FormCompararMNC", "&Ver", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormCompararMNC: public Ui_FormCompararMNC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCOMPARARMNC_H
