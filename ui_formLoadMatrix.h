/********************************************************************************
** Form generated from reading UI file 'formLoadMatrix.ui'
**
** Created: Mon Aug 10 09:45:07 2015
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
#include <QtGui/QComboBox>
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
    QPushButton *buttonOpen;
    QLineEdit *editYear;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_3;
    QSpinBox *spinNumber;
    QPushButton *buttonSearch;
    QPushButton *buttonCancel;
    QLineEdit *editFilePath;
    QLabel *label;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QComboBox *comboSeparator;
    QLineEdit *editCountry;

    void setupUi(QWidget *FormLoadMatrix)
    {
        if (FormLoadMatrix->objectName().isEmpty())
            FormLoadMatrix->setObjectName(QString::fromUtf8("FormLoadMatrix"));
        FormLoadMatrix->setWindowModality(Qt::ApplicationModal);
        FormLoadMatrix->resize(635, 332);
        verticalLayout = new QVBoxLayout(FormLoadMatrix);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonOpen = new QPushButton(FormLoadMatrix);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));

        gridLayout->addWidget(buttonOpen, 13, 6, 1, 1);

        editYear = new QLineEdit(FormLoadMatrix);
        editYear->setObjectName(QString::fromUtf8("editYear"));

        gridLayout->addWidget(editYear, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 11, 1, 1, 1);

        line = new QFrame(FormLoadMatrix);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 6, 0, 1, 7);

        label_2 = new QLabel(FormLoadMatrix);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Aero Matics"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 8, 0, 1, 2);

        label_6 = new QLabel(FormLoadMatrix);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 3, 1, 1);

        label_5 = new QLabel(FormLoadMatrix);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font1;
        font1.setPointSize(10);
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_3 = new QLabel(FormLoadMatrix);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spinNumber = new QSpinBox(FormLoadMatrix);
        spinNumber->setObjectName(QString::fromUtf8("spinNumber"));
        spinNumber->setMinimum(1);

        gridLayout->addWidget(spinNumber, 2, 1, 1, 1);

        buttonSearch = new QPushButton(FormLoadMatrix);
        buttonSearch->setObjectName(QString::fromUtf8("buttonSearch"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("img/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSearch->setIcon(icon);
        buttonSearch->setFlat(true);

        gridLayout->addWidget(buttonSearch, 10, 6, 1, 1);

        buttonCancel = new QPushButton(FormLoadMatrix);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        gridLayout->addWidget(buttonCancel, 13, 4, 1, 1);

        editFilePath = new QLineEdit(FormLoadMatrix);
        editFilePath->setObjectName(QString::fromUtf8("editFilePath"));
        editFilePath->setReadOnly(true);

        gridLayout->addWidget(editFilePath, 10, 1, 1, 5);

        label = new QLabel(FormLoadMatrix);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        label_7 = new QLabel(FormLoadMatrix);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        gridLayout->addWidget(label_7, 10, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 7, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 5, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 9, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        label_4 = new QLabel(FormLoadMatrix);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 3, 1, 1);

        comboSeparator = new QComboBox(FormLoadMatrix);
        comboSeparator->setObjectName(QString::fromUtf8("comboSeparator"));
        comboSeparator->setEditable(false);

        gridLayout->addWidget(comboSeparator, 2, 4, 1, 2);

        editCountry = new QLineEdit(FormLoadMatrix);
        editCountry->setObjectName(QString::fromUtf8("editCountry"));

        gridLayout->addWidget(editCountry, 4, 4, 1, 3);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(FormLoadMatrix);

        QMetaObject::connectSlotsByName(FormLoadMatrix);
    } // setupUi

    void retranslateUi(QWidget *FormLoadMatrix)
    {
        FormLoadMatrix->setWindowTitle(QApplication::translate("FormLoadMatrix", "Cargar Matriz", 0, QApplication::UnicodeUTF8));
        buttonOpen->setText(QApplication::translate("FormLoadMatrix", "A&brir", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormLoadMatrix", "2.- Cargar Matriz", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FormLoadMatrix", "Pa\303\255s:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FormLoadMatrix", "A\303\261o:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Cuentas:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonSearch->setToolTip(QApplication::translate("FormLoadMatrix", "Examinar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonSearch->setText(QString());
        buttonCancel->setText(QApplication::translate("FormLoadMatrix", "&Cancelar", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormLoadMatrix", "1.- Estructura de la Matriz", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FormLoadMatrix", "Archivo:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FormLoadMatrix", "Separador:", 0, QApplication::UnicodeUTF8));
        comboSeparator->clear();
        comboSeparator->insertItems(0, QStringList()
         << QApplication::translate("FormLoadMatrix", ",", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormLoadMatrix", ";", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormLoadMatrix", "|", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class FormLoadMatrix: public Ui_FormLoadMatrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADMATRIX_H
