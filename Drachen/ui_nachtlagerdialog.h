/********************************************************************************
** Form generated from reading UI file 'nachtlagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NACHTLAGERDIALOG_H
#define UI_NACHTLAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NachtlagerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelOrt;
    QLineEdit *lineEditOrt;
    QLabel *labelAbfahrt;
    QLineEdit *lineEditAbfahrt;
    QLabel *labelAnkunft;
    QLineEdit *lineEditAnkunft;
    QLabel *labelPreis;
    QDoubleSpinBox *doubleSpinBoxPreis;
    QLabel *labelUnterkunft;
    QComboBox *comboBoxUnterkunft;
    QLabel *labelRuhelevel;
    QDoubleSpinBox *doubleSpinBoxRuhelevel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NachtlagerDialog)
    {
        if (NachtlagerDialog->objectName().isEmpty())
            NachtlagerDialog->setObjectName("NachtlagerDialog");
        NachtlagerDialog->resize(362, 322);
        verticalLayout = new QVBoxLayout(NachtlagerDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelOrt = new QLabel(NachtlagerDialog);
        labelOrt->setObjectName("labelOrt");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelOrt);

        lineEditOrt = new QLineEdit(NachtlagerDialog);
        lineEditOrt->setObjectName("lineEditOrt");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditOrt);

        labelAbfahrt = new QLabel(NachtlagerDialog);
        labelAbfahrt->setObjectName("labelAbfahrt");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelAbfahrt);

        lineEditAbfahrt = new QLineEdit(NachtlagerDialog);
        lineEditAbfahrt->setObjectName("lineEditAbfahrt");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditAbfahrt);

        labelAnkunft = new QLabel(NachtlagerDialog);
        labelAnkunft->setObjectName("labelAnkunft");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelAnkunft);

        lineEditAnkunft = new QLineEdit(NachtlagerDialog);
        lineEditAnkunft->setObjectName("lineEditAnkunft");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditAnkunft);

        labelPreis = new QLabel(NachtlagerDialog);
        labelPreis->setObjectName("labelPreis");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelPreis);

        doubleSpinBoxPreis = new QDoubleSpinBox(NachtlagerDialog);
        doubleSpinBoxPreis->setObjectName("doubleSpinBoxPreis");
        doubleSpinBoxPreis->setDecimals(2);
        doubleSpinBoxPreis->setMaximum(10000.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, doubleSpinBoxPreis);

        labelUnterkunft = new QLabel(NachtlagerDialog);
        labelUnterkunft->setObjectName("labelUnterkunft");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelUnterkunft);

        comboBoxUnterkunft = new QComboBox(NachtlagerDialog);
        comboBoxUnterkunft->addItem(QString());
        comboBoxUnterkunft->addItem(QString());
        comboBoxUnterkunft->addItem(QString());
        comboBoxUnterkunft->setObjectName("comboBoxUnterkunft");

        formLayout->setWidget(4, QFormLayout::FieldRole, comboBoxUnterkunft);

        labelRuhelevel = new QLabel(NachtlagerDialog);
        labelRuhelevel->setObjectName("labelRuhelevel");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelRuhelevel);

        doubleSpinBoxRuhelevel = new QDoubleSpinBox(NachtlagerDialog);
        doubleSpinBoxRuhelevel->setObjectName("doubleSpinBoxRuhelevel");
        doubleSpinBoxRuhelevel->setDecimals(1);
        doubleSpinBoxRuhelevel->setMinimum(0.000000000000000);
        doubleSpinBoxRuhelevel->setMaximum(10.000000000000000);
        doubleSpinBoxRuhelevel->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, doubleSpinBoxRuhelevel);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(NachtlagerDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NachtlagerDialog);

        QMetaObject::connectSlotsByName(NachtlagerDialog);
    } // setupUi

    void retranslateUi(QDialog *NachtlagerDialog)
    {
        NachtlagerDialog->setWindowTitle(QCoreApplication::translate("NachtlagerDialog", "Nachtlager bearbeiten", nullptr));
        labelOrt->setText(QCoreApplication::translate("NachtlagerDialog", "Ort", nullptr));
        labelAbfahrt->setText(QCoreApplication::translate("NachtlagerDialog", "Abfahrt", nullptr));
        labelAnkunft->setText(QCoreApplication::translate("NachtlagerDialog", "Ankunft", nullptr));
        labelPreis->setText(QCoreApplication::translate("NachtlagerDialog", "Preis", nullptr));
        labelUnterkunft->setText(QCoreApplication::translate("NachtlagerDialog", "Unterkunfts-Typ", nullptr));
        comboBoxUnterkunft->setItemText(0, QCoreApplication::translate("NachtlagerDialog", "Bergplateau", nullptr));
        comboBoxUnterkunft->setItemText(1, QCoreApplication::translate("NachtlagerDialog", "H\303\266hle", nullptr));
        comboBoxUnterkunft->setItemText(2, QCoreApplication::translate("NachtlagerDialog", "Baumkrone", nullptr));

        labelRuhelevel->setText(QCoreApplication::translate("NachtlagerDialog", "Ruhelevel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NachtlagerDialog: public Ui_NachtlagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NACHTLAGERDIALOG_H
