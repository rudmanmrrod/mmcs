/********************************************************************************
** Form generated from reading UI file 'formLoadMatrix.ui'
**
** Created: Fri Sep 25 11:00:03 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOADMATRIX_H
#define UI_FORMLOADMATRIX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormLoadMatrix
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QPushButton *buttonOpen;
    QLabel *label_4;
    QSpinBox *spinBox;
    QFrame *line;
    QSpinBox *spinNumber;
    QLabel *label_3;
    QLineEdit *editFilePath;
    QPushButton *buttonSearch;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_7;
    QPushButton *buttonCancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FormLoadMatrix)
    {
        if (FormLoadMatrix->objectName().isEmpty())
            FormLoadMatrix->setObjectName(QString::fromUtf8("FormLoadMatrix"));
        FormLoadMatrix->setWindowModality(Qt::ApplicationModal);
        FormLoadMatrix->resize(607, 303);
        verticalLayout = new QVBoxLayout(FormLoadMatrix);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 2);

        label_2 = new QLabel(FormLoadMatrix);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Aero Matics"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 5, 0, 1, 2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 6, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 1);

        label = new QLabel(FormLoadMatrix);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        buttonOpen = new QPushButton(FormLoadMatrix);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));

        gridLayout->addWidget(buttonOpen, 10, 6, 1, 1);

        label_4 = new QLabel(FormLoadMatrix);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 4, 1, 2);

        spinBox = new QSpinBox(FormLoadMatrix);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(3);
        spinBox->setMaximum(15);

        gridLayout->addWidget(spinBox, 2, 6, 1, 1);

        line = new QFrame(FormLoadMatrix);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 7);

        spinNumber = new QSpinBox(FormLoadMatrix);
        spinNumber->setObjectName(QString::fromUtf8("spinNumber"));
        spinNumber->setMinimum(2);

        gridLayout->addWidget(spinNumber, 2, 1, 1, 1);

        label_3 = new QLabel(FormLoadMatrix);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setPointSize(10);
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        editFilePath = new QLineEdit(FormLoadMatrix);
        editFilePath->setObjectName(QString::fromUtf8("editFilePath"));
        editFilePath->setReadOnly(true);

        gridLayout->addWidget(editFilePath, 7, 1, 1, 5);

        buttonSearch = new QPushButton(FormLoadMatrix);
        buttonSearch->setObjectName(QString::fromUtf8("buttonSearch"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("img/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSearch->setIcon(icon);
        buttonSearch->setFlat(true);

        gridLayout->addWidget(buttonSearch, 7, 6, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 1, 1, 1, 1);

        label_7 = new QLabel(FormLoadMatrix);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        buttonCancel = new QPushButton(FormLoadMatrix);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        gridLayout->addWidget(buttonCancel, 10, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 8, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(FormLoadMatrix);

        QMetaObject::connectSlotsByName(FormLoadMatrix);
    } // setupUi

    void retranslateUi(QWidget *FormLoadMatrix)
    {
        FormLoadMatrix->setWindowTitle(QApplication::translate("FormLoadMatrix", "Cargar Matriz", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormLoadMatrix", "2.- Cargar Matriz", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormLoadMatrix", "1.- Estructura de la Matriz", 0, QApplication::UnicodeUTF8));
        buttonOpen->setText(QApplication::translate("FormLoadMatrix", "A&brir", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Decimales", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Cuentas:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonSearch->setToolTip(QApplication::translate("FormLoadMatrix", "Examinar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonSearch->setText(QString());
        label_7->setText(QApplication::translate("FormLoadMatrix", "Archivo:", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("FormLoadMatrix", "&Cancelar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormLoadMatrix: public Ui_FormLoadMatrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADMATRIX_H
