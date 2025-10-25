/********************************************************************************
** Form generated from reading UI file 'drachenflugdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRACHENFLUGDIALOG_H
#define UI_DRACHENFLUGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrachenflugDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_ziel;
    QLabel *label_Abf;
    QLabel *label_Ank;
    QLabel *label_Preis;
    QLabel *label_ent;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QDateEdit *dateEdit;
    QDateEdit *dateEdit_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;

    void setupUi(QDialog *DrachenflugDialog)
    {
        if (DrachenflugDialog->objectName().isEmpty())
            DrachenflugDialog->setObjectName("DrachenflugDialog");
        DrachenflugDialog->resize(537, 528);
        buttonBox = new QDialogButtonBox(DrachenflugDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(124, 270, 171, 29));
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        widget = new QWidget(DrachenflugDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(11, 11, 217, 212));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_ziel = new QLabel(widget);
        label_ziel->setObjectName("label_ziel");

        verticalLayout->addWidget(label_ziel);

        label_Abf = new QLabel(widget);
        label_Abf->setObjectName("label_Abf");

        verticalLayout->addWidget(label_Abf);

        label_Ank = new QLabel(widget);
        label_Ank->setObjectName("label_Ank");

        verticalLayout->addWidget(label_Ank);

        label_Preis = new QLabel(widget);
        label_Preis->setObjectName("label_Preis");

        verticalLayout->addWidget(label_Preis);

        label_ent = new QLabel(widget);
        label_ent->setObjectName("label_ent");

        verticalLayout->addWidget(label_ent);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName("dateEdit");

        verticalLayout_2->addWidget(dateEdit);

        dateEdit_2 = new QDateEdit(widget);
        dateEdit_2->setObjectName("dateEdit_2");

        verticalLayout_2->addWidget(dateEdit_2);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName("spinBox");

        verticalLayout_2->addWidget(spinBox);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName("spinBox_2");

        verticalLayout_2->addWidget(spinBox_2);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_2);


        retranslateUi(DrachenflugDialog);

        QMetaObject::connectSlotsByName(DrachenflugDialog);
    } // setupUi

    void retranslateUi(QDialog *DrachenflugDialog)
    {
        DrachenflugDialog->setWindowTitle(QCoreApplication::translate("DrachenflugDialog", "Dialog", nullptr));
        label_ziel->setText(QCoreApplication::translate("DrachenflugDialog", "Ziel :", nullptr));
        label_Abf->setText(QCoreApplication::translate("DrachenflugDialog", "Abfahrt :", nullptr));
        label_Ank->setText(QCoreApplication::translate("DrachenflugDialog", "Ankunft :", nullptr));
        label_Preis->setText(QCoreApplication::translate("DrachenflugDialog", "Preis :", nullptr));
        label_ent->setText(QCoreApplication::translate("DrachenflugDialog", "Entfernung :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrachenflugDialog: public Ui_DrachenflugDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRACHENFLUGDIALOG_H
