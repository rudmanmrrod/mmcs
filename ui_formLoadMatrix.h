/********************************************************************************
** Form generated from reading UI file 'formLoadMatrix.ui'
**
** Created: Tue Jul 7 10:52:32 2015
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormLoadMatrix
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinNumber;
    QLabel *label_4;
    QComboBox *comboSeparator;
    QLabel *label_5;
    QLineEdit *editYear;
    QLabel *label_6;
    QLineEdit *editCountry;
    QFrame *line;
    QLabel *label_7;
    QLineEdit *editFilePath;
    QPushButton *buttonSearch;
    QPushButton *buttonCancel;
    QPushButton *buttonOpen;

    void setupUi(QWidget *FormLoadMatrix)
    {
        if (FormLoadMatrix->objectName().isEmpty())
            FormLoadMatrix->setObjectName(QString::fromUtf8("FormLoadMatrix"));
        FormLoadMatrix->setWindowModality(Qt::ApplicationModal);
        FormLoadMatrix->resize(635, 332);
        label = new QLabel(FormLoadMatrix);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 20, 251, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Aero Matics"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label_2 = new QLabel(FormLoadMatrix);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 180, 171, 31));
        label_2->setFont(font);
        label_3 = new QLabel(FormLoadMatrix);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 70, 141, 17));
        QFont font1;
        font1.setPointSize(10);
        label_3->setFont(font1);
        spinNumber = new QSpinBox(FormLoadMatrix);
        spinNumber->setObjectName(QString::fromUtf8("spinNumber"));
        spinNumber->setGeometry(QRect(210, 60, 101, 27));
        spinNumber->setMinimum(1);
        label_4 = new QLabel(FormLoadMatrix);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(390, 70, 81, 17));
        comboSeparator = new QComboBox(FormLoadMatrix);
        comboSeparator->setObjectName(QString::fromUtf8("comboSeparator"));
        comboSeparator->setGeometry(QRect(470, 60, 131, 27));
        comboSeparator->setEditable(false);
        label_5 = new QLabel(FormLoadMatrix);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 120, 131, 17));
        label_5->setFont(font1);
        editYear = new QLineEdit(FormLoadMatrix);
        editYear->setObjectName(QString::fromUtf8("editYear"));
        editYear->setGeometry(QRect(210, 110, 101, 27));
        label_6 = new QLabel(FormLoadMatrix);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(390, 120, 71, 17));
        editCountry = new QLineEdit(FormLoadMatrix);
        editCountry->setObjectName(QString::fromUtf8("editCountry"));
        editCountry->setGeometry(QRect(470, 110, 131, 27));
        line = new QFrame(FormLoadMatrix);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 160, 631, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(FormLoadMatrix);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 230, 91, 17));
        label_7->setFont(font1);
        editFilePath = new QLineEdit(FormLoadMatrix);
        editFilePath->setObjectName(QString::fromUtf8("editFilePath"));
        editFilePath->setGeometry(QRect(130, 220, 351, 27));
        editFilePath->setReadOnly(true);
        buttonSearch = new QPushButton(FormLoadMatrix);
        buttonSearch->setObjectName(QString::fromUtf8("buttonSearch"));
        buttonSearch->setGeometry(QRect(480, 220, 41, 27));
        QIcon icon;
        icon.addFile(QString::fromUtf8("img/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSearch->setIcon(icon);
        buttonSearch->setFlat(true);
        buttonCancel = new QPushButton(FormLoadMatrix);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(410, 280, 92, 27));
        buttonOpen = new QPushButton(FormLoadMatrix);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));
        buttonOpen->setGeometry(QRect(510, 280, 92, 27));

        retranslateUi(FormLoadMatrix);

        QMetaObject::connectSlotsByName(FormLoadMatrix);
    } // setupUi

    void retranslateUi(QWidget *FormLoadMatrix)
    {
        FormLoadMatrix->setWindowTitle(QApplication::translate("FormLoadMatrix", "Cargar Matriz", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormLoadMatrix", "1.- Estructura de la Matriz", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormLoadMatrix", "2.- Cargar Matriz", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Cuentas:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FormLoadMatrix", "Separador:", 0, QApplication::UnicodeUTF8));
        comboSeparator->clear();
        comboSeparator->insertItems(0, QStringList()
         << QApplication::translate("FormLoadMatrix", ",", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormLoadMatrix", ";", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormLoadMatrix", "|", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("FormLoadMatrix", "A\303\261o:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FormLoadMatrix", "Pa\303\255s:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FormLoadMatrix", "Archivo:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonSearch->setToolTip(QApplication::translate("FormLoadMatrix", "Examinar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonSearch->setText(QString());
        buttonCancel->setText(QApplication::translate("FormLoadMatrix", "&Cancelar", 0, QApplication::UnicodeUTF8));
        buttonOpen->setText(QApplication::translate("FormLoadMatrix", "A&brir", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormLoadMatrix: public Ui_FormLoadMatrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADMATRIX_H
