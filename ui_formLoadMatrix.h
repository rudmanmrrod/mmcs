/********************************************************************************
** Form generated from reading UI file 'formLoadMatrix.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOADMATRIX_H
#define UI_FORMLOADMATRIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QPushButton *buttonCancel;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;
    QRadioButton *radioAccount;
    QRadioButton *radioComponent;
    QLabel *label_info;

    void setupUi(QWidget *FormLoadMatrix)
    {
        if (FormLoadMatrix->objectName().isEmpty())
            FormLoadMatrix->setObjectName(QStringLiteral("FormLoadMatrix"));
        FormLoadMatrix->setWindowModality(Qt::ApplicationModal);
        FormLoadMatrix->resize(642, 304);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FormLoadMatrix->sizePolicy().hasHeightForWidth());
        FormLoadMatrix->setSizePolicy(sizePolicy);
        FormLoadMatrix->setMinimumSize(QSize(600, 300));
        verticalLayout = new QVBoxLayout(FormLoadMatrix);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 2);

        label_2 = new QLabel(FormLoadMatrix);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QStringLiteral("Aero Matics"));
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
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        buttonOpen = new QPushButton(FormLoadMatrix);
        buttonOpen->setObjectName(QStringLiteral("buttonOpen"));

        gridLayout->addWidget(buttonOpen, 11, 6, 1, 1);

        label_4 = new QLabel(FormLoadMatrix);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 4, 1, 2);

        spinBox = new QSpinBox(FormLoadMatrix);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(3);
        spinBox->setMaximum(15);

        gridLayout->addWidget(spinBox, 2, 6, 1, 1);

        line = new QFrame(FormLoadMatrix);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 7);

        spinNumber = new QSpinBox(FormLoadMatrix);
        spinNumber->setObjectName(QStringLiteral("spinNumber"));
        spinNumber->setMinimum(2);

        gridLayout->addWidget(spinNumber, 2, 1, 1, 1);

        label_3 = new QLabel(FormLoadMatrix);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font1;
        font1.setPointSize(10);
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        editFilePath = new QLineEdit(FormLoadMatrix);
        editFilePath->setObjectName(QStringLiteral("editFilePath"));
        editFilePath->setReadOnly(true);

        gridLayout->addWidget(editFilePath, 7, 1, 1, 5);

        buttonSearch = new QPushButton(FormLoadMatrix);
        buttonSearch->setObjectName(QStringLiteral("buttonSearch"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/imgs/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSearch->setIcon(icon);
        buttonSearch->setFlat(true);

        gridLayout->addWidget(buttonSearch, 7, 6, 1, 1);

        buttonCancel = new QPushButton(FormLoadMatrix);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));

        gridLayout->addWidget(buttonCancel, 11, 4, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 1, 1, 1, 1);

        label_7 = new QLabel(FormLoadMatrix);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 8, 1, 1, 1);

        radioAccount = new QRadioButton(FormLoadMatrix);
        radioAccount->setObjectName(QStringLiteral("radioAccount"));

        gridLayout->addWidget(radioAccount, 10, 0, 1, 1);

        radioComponent = new QRadioButton(FormLoadMatrix);
        radioComponent->setObjectName(QStringLiteral("radioComponent"));

        gridLayout->addWidget(radioComponent, 10, 2, 1, 1);

        label_info = new QLabel(FormLoadMatrix);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setStyleSheet(QLatin1String("font-weight: bold;\n"
"color: #358ccb;\n"
""));

        gridLayout->addWidget(label_info, 9, 0, 1, 7);


        verticalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(spinNumber, spinBox);
        QWidget::setTabOrder(spinBox, editFilePath);
        QWidget::setTabOrder(editFilePath, buttonSearch);
        QWidget::setTabOrder(buttonSearch, radioAccount);
        QWidget::setTabOrder(radioAccount, radioComponent);
        QWidget::setTabOrder(radioComponent, buttonCancel);
        QWidget::setTabOrder(buttonCancel, buttonOpen);

        retranslateUi(FormLoadMatrix);

        QMetaObject::connectSlotsByName(FormLoadMatrix);
    } // setupUi

    void retranslateUi(QWidget *FormLoadMatrix)
    {
        FormLoadMatrix->setWindowTitle(QApplication::translate("FormLoadMatrix", "Cargar Matriz", 0));
        label_2->setText(QApplication::translate("FormLoadMatrix", "2.- Cargar Matriz", 0));
        label->setText(QApplication::translate("FormLoadMatrix", "1.- Estructura de la Matriz", 0));
        buttonOpen->setText(QApplication::translate("FormLoadMatrix", "A&brir", 0));
        label_4->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Decimales", 0));
        label_3->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Cuentas:", 0));
#ifndef QT_NO_TOOLTIP
        buttonSearch->setToolTip(QApplication::translate("FormLoadMatrix", "Examinar", 0));
#endif // QT_NO_TOOLTIP
        buttonSearch->setText(QString());
        buttonCancel->setText(QApplication::translate("FormLoadMatrix", "&Cancelar", 0));
        label_7->setText(QApplication::translate("FormLoadMatrix", "Archivo:", 0));
        radioAccount->setText(QApplication::translate("FormLoadMatrix", "Con Cuentas", 0));
        radioComponent->setText(QApplication::translate("FormLoadMatrix", "Componentes", 0));
        label_info->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FormLoadMatrix: public Ui_FormLoadMatrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADMATRIX_H
