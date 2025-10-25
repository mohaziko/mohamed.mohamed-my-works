/********************************************************************************
** Form generated from reading UI file 'suchergebnisdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUCHERGEBNISDIALOG_H
#define UI_SUCHERGEBNISDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SuchergebnisDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditPassagierName;
    QPushButton *pushButtonSuche;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxPassagier;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidgetPassagier;
    QGroupBox *groupBoxPlayer;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidgetPlayer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *WidgetReiseabschnitte;

    void setupUi(QDialog *SuchergebnisDialog)
    {
        if (SuchergebnisDialog->objectName().isEmpty())
            SuchergebnisDialog->setObjectName("SuchergebnisDialog");
        SuchergebnisDialog->resize(649, 564);
        verticalLayout = new QVBoxLayout(SuchergebnisDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(SuchergebnisDialog);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lineEditPassagierName = new QLineEdit(SuchergebnisDialog);
        lineEditPassagierName->setObjectName("lineEditPassagierName");
        lineEditPassagierName->setReadOnly(false);

        horizontalLayout_2->addWidget(lineEditPassagierName);

        pushButtonSuche = new QPushButton(SuchergebnisDialog);
        pushButtonSuche->setObjectName("pushButtonSuche");
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/suchen.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSuche->setIcon(icon);

        horizontalLayout_2->addWidget(pushButtonSuche);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBoxPassagier = new QGroupBox(SuchergebnisDialog);
        groupBoxPassagier->setObjectName("groupBoxPassagier");
        verticalLayout_2 = new QVBoxLayout(groupBoxPassagier);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tableWidgetPassagier = new QTableWidget(groupBoxPassagier);
        if (tableWidgetPassagier->columnCount() < 5)
            tableWidgetPassagier->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPassagier->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPassagier->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPassagier->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPassagier->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPassagier->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetPassagier->setObjectName("tableWidgetPassagier");

        verticalLayout_2->addWidget(tableWidgetPassagier);


        verticalLayout_3->addWidget(groupBoxPassagier);

        groupBoxPlayer = new QGroupBox(SuchergebnisDialog);
        groupBoxPlayer->setObjectName("groupBoxPlayer");
        horizontalLayout = new QHBoxLayout(groupBoxPlayer);
        horizontalLayout->setObjectName("horizontalLayout");
        tableWidgetPlayer = new QTableWidget(groupBoxPlayer);
        if (tableWidgetPlayer->columnCount() < 5)
            tableWidgetPlayer->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPlayer->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPlayer->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetPlayer->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetPlayer->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetPlayer->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidgetPlayer->setObjectName("tableWidgetPlayer");

        horizontalLayout->addWidget(tableWidgetPlayer);


        verticalLayout_3->addWidget(groupBoxPlayer);

        groupBox = new QGroupBox(SuchergebnisDialog);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        WidgetReiseabschnitte = new QTableWidget(groupBox);
        if (WidgetReiseabschnitte->columnCount() < 5)
            WidgetReiseabschnitte->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        WidgetReiseabschnitte->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        WidgetReiseabschnitte->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        WidgetReiseabschnitte->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        WidgetReiseabschnitte->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        WidgetReiseabschnitte->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        WidgetReiseabschnitte->setObjectName("WidgetReiseabschnitte");

        gridLayout->addWidget(WidgetReiseabschnitte, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addLayout(verticalLayout_4);


        retranslateUi(SuchergebnisDialog);

        QMetaObject::connectSlotsByName(SuchergebnisDialog);
    } // setupUi

    void retranslateUi(QDialog *SuchergebnisDialog)
    {
        SuchergebnisDialog->setWindowTitle(QCoreApplication::translate("SuchergebnisDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SuchergebnisDialog", "Name des Passagiers:", nullptr));
        pushButtonSuche->setText(QString());
        groupBoxPassagier->setTitle(QCoreApplication::translate("SuchergebnisDialog", "Reisepl\303\244ne als Passagier", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPassagier->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SuchergebnisDialog", "PlanNr.", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPassagier->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SuchergebnisDialog", "PlanName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPassagier->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SuchergebnisDialog", "ReiseBeginn", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPassagier->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SuchergebnisDialog", "ReiseEnde", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPassagier->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SuchergebnisDialog", "Preis", nullptr));
        groupBoxPlayer->setTitle(QCoreApplication::translate("SuchergebnisDialog", "Reisepl\303\244ne als Player", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPlayer->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SuchergebnisDialog", "PlanNr.", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPlayer->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SuchergebnisDialog", "PlanName", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetPlayer->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SuchergebnisDialog", "ReiseBeginn", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetPlayer->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SuchergebnisDialog", "ReiseEnde", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetPlayer->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("SuchergebnisDialog", "Preis", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SuchergebnisDialog", "Reiseabschnitte", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = WidgetReiseabschnitte->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("SuchergebnisDialog", "Typ", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = WidgetReiseabschnitte->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("SuchergebnisDialog", "Ziel/Lagerort", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = WidgetReiseabschnitte->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("SuchergebnisDialog", "Abfahrt", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = WidgetReiseabschnitte->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("SuchergebnisDialog", "Ankunft", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = WidgetReiseabschnitte->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("SuchergebnisDialog", "Preis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SuchergebnisDialog: public Ui_SuchergebnisDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUCHERGEBNISDIALOG_H
