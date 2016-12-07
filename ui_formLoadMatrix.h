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
    QRadioButton *radioComponent;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QRadioButton *radioAccount;
    QPushButton *buttonCancel;
    QLabel *label_3;
    QLabel *label_info;
    QFrame *line;
    QLabel *label_4;
    QLineEdit *editFilePath;
    QSpinBox *spinNumber;
    QPushButton *buttonOpen;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonSearch;
    QLabel *label_7;
    QSpinBox *spinBox;
    QLabel *label;

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
        radioComponent = new QRadioButton(FormLoadMatrix);
        radioComponent->setObjectName(QStringLiteral("radioComponent"));

        gridLayout->addWidget(radioComponent, 8, 2, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 1, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 4, 0, 1, 1);

        radioAccount = new QRadioButton(FormLoadMatrix);
        radioAccount->setObjectName(QStringLiteral("radioAccount"));

        gridLayout->addWidget(radioAccount, 8, 0, 1, 1);

        buttonCancel = new QPushButton(FormLoadMatrix);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));

        gridLayout->addWidget(buttonCancel, 9, 3, 1, 1);

        label_3 = new QLabel(FormLoadMatrix);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_info = new QLabel(FormLoadMatrix);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setStyleSheet(QLatin1String("font-weight: bold;\n"
"color: #358ccb;\n"
""));

        gridLayout->addWidget(label_info, 7, 0, 1, 6);

        line = new QFrame(FormLoadMatrix);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 6);

        label_4 = new QLabel(FormLoadMatrix);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 3, 1, 2);

        editFilePath = new QLineEdit(FormLoadMatrix);
        editFilePath->setObjectName(QStringLiteral("editFilePath"));
        editFilePath->setReadOnly(true);

        gridLayout->addWidget(editFilePath, 5, 1, 1, 4);

        spinNumber = new QSpinBox(FormLoadMatrix);
        spinNumber->setObjectName(QStringLiteral("spinNumber"));
        spinNumber->setMinimum(2);

        gridLayout->addWidget(spinNumber, 2, 1, 1, 1);

        buttonOpen = new QPushButton(FormLoadMatrix);
        buttonOpen->setObjectName(QStringLiteral("buttonOpen"));

        gridLayout->addWidget(buttonOpen, 9, 5, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 1, 1, 1);

        buttonSearch = new QPushButton(FormLoadMatrix);
        buttonSearch->setObjectName(QStringLiteral("buttonSearch"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/imgs/folder_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSearch->setIcon(icon);
        buttonSearch->setFlat(true);

        gridLayout->addWidget(buttonSearch, 5, 5, 1, 1);

        label_7 = new QLabel(FormLoadMatrix);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        spinBox = new QSpinBox(FormLoadMatrix);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(3);
        spinBox->setMaximum(15);

        gridLayout->addWidget(spinBox, 2, 5, 1, 1);

        label = new QLabel(FormLoadMatrix);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("Aero Matics"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 3);


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
        radioComponent->setText(QApplication::translate("FormLoadMatrix", "Sub-Cuentas", 0));
        radioAccount->setText(QApplication::translate("FormLoadMatrix", "Con Cuentas", 0));
        buttonCancel->setText(QApplication::translate("FormLoadMatrix", "&Cancelar", 0));
        label_3->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Cuentas:", 0));
        label_info->setText(QString());
        label_4->setText(QApplication::translate("FormLoadMatrix", "N\303\272mero de Decimales", 0));
        buttonOpen->setText(QApplication::translate("FormLoadMatrix", "A&brir", 0));
#ifndef QT_NO_TOOLTIP
        buttonSearch->setToolTip(QApplication::translate("FormLoadMatrix", "Examinar", 0));
#endif // QT_NO_TOOLTIP
        buttonSearch->setText(QString());
        label_7->setText(QApplication::translate("FormLoadMatrix", "Archivo:", 0));
        label->setText(QApplication::translate("FormLoadMatrix", "Definir Par\303\241metros de la Matriz", 0));
    } // retranslateUi

};

namespace Ui {
    class FormLoadMatrix: public Ui_FormLoadMatrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADMATRIX_H
