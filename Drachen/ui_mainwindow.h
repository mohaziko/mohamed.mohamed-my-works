/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEinlesen;
    QAction *actionSpeichern;
    QAction *actionBeenden;
    QAction *actionDrache_L_schen;
    QAction *actionReiseplan_L_schen;
    QAction *actionDrachereise_L_schen;
    QAction *actionPassagier_L_schen;
    QAction *actionDrache_l_schen;
    QAction *actionReiseplan_l_schen;
    QAction *actionDrachereise_l_schen;
    QAction *actionPassagier_l_schen;
    QAction *actionEinlesen_2;
    QAction *actionPerson_suchen;
    QAction *actionLandkarte_suchen;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QListWidget *drachenListWidget;
    QGraphicsView *graphicsViewMap;
    QSlider *horizontalSliderZoom;
    QVBoxLayout *verticalLayout;
    QLabel *label_drachenDetails;
    QPlainTextEdit *detailTextEdit;
    QLabel *label_Plaene;
    QListWidget *reisePlanListWidget;
    QLabel *label_reisen;
    QListWidget *reiseListWidget;
    QLabel *label_drachenflugDetails;
    QListWidget *reiseDetailsListWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *addDracheButton;
    QPushButton *addReiseplanButton;
    QPushButton *addDrachenreiseButton;
    QPushButton *addPassengerButton;
    QPushButton *saveButton;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuDrache_L_schen;
    QMenu *menusuchen;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1080, 639);
        actionEinlesen = new QAction(MainWindow);
        actionEinlesen->setObjectName("actionEinlesen");
        actionEinlesen->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/einlesen.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionEinlesen->setIcon(icon);
        actionSpeichern = new QAction(MainWindow);
        actionSpeichern->setObjectName("actionSpeichern");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/speichern.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSpeichern->setIcon(icon1);
        actionBeenden = new QAction(MainWindow);
        actionBeenden->setObjectName("actionBeenden");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/beenden.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionBeenden->setIcon(icon2);
        actionDrache_L_schen = new QAction(MainWindow);
        actionDrache_L_schen->setObjectName("actionDrache_L_schen");
        actionReiseplan_L_schen = new QAction(MainWindow);
        actionReiseplan_L_schen->setObjectName("actionReiseplan_L_schen");
        actionDrachereise_L_schen = new QAction(MainWindow);
        actionDrachereise_L_schen->setObjectName("actionDrachereise_L_schen");
        actionPassagier_L_schen = new QAction(MainWindow);
        actionPassagier_L_schen->setObjectName("actionPassagier_L_schen");
        actionDrache_l_schen = new QAction(MainWindow);
        actionDrache_l_schen->setObjectName("actionDrache_l_schen");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/drache.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionDrache_l_schen->setIcon(icon3);
        actionReiseplan_l_schen = new QAction(MainWindow);
        actionReiseplan_l_schen->setObjectName("actionReiseplan_l_schen");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/reiseplan.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionReiseplan_l_schen->setIcon(icon4);
        actionDrachereise_l_schen = new QAction(MainWindow);
        actionDrachereise_l_schen->setObjectName("actionDrachereise_l_schen");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/drachenreise.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionDrachereise_l_schen->setIcon(icon5);
        actionPassagier_l_schen = new QAction(MainWindow);
        actionPassagier_l_schen->setObjectName("actionPassagier_l_schen");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/passagier.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionPassagier_l_schen->setIcon(icon6);
        actionEinlesen_2 = new QAction(MainWindow);
        actionEinlesen_2->setObjectName("actionEinlesen_2");
        actionEinlesen_2->setCheckable(false);
        actionEinlesen_2->setIcon(icon);
        actionPerson_suchen = new QAction(MainWindow);
        actionPerson_suchen->setObjectName("actionPerson_suchen");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../Users/moham/Downloads/icons/suchen.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionPerson_suchen->setIcon(icon7);
        actionLandkarte_suchen = new QAction(MainWindow);
        actionLandkarte_suchen->setObjectName("actionLandkarte_suchen");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("icons/landkarte.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionLandkarte_suchen->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        drachenListWidget = new QListWidget(centralwidget);
        drachenListWidget->setObjectName("drachenListWidget");

        verticalLayout_2->addWidget(drachenListWidget);

        graphicsViewMap = new QGraphicsView(centralwidget);
        graphicsViewMap->setObjectName("graphicsViewMap");

        verticalLayout_2->addWidget(graphicsViewMap);

        horizontalSliderZoom = new QSlider(centralwidget);
        horizontalSliderZoom->setObjectName("horizontalSliderZoom");
        horizontalSliderZoom->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(horizontalSliderZoom);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_drachenDetails = new QLabel(centralwidget);
        label_drachenDetails->setObjectName("label_drachenDetails");

        verticalLayout->addWidget(label_drachenDetails);

        detailTextEdit = new QPlainTextEdit(centralwidget);
        detailTextEdit->setObjectName("detailTextEdit");
        detailTextEdit->setReadOnly(true);

        verticalLayout->addWidget(detailTextEdit);

        label_Plaene = new QLabel(centralwidget);
        label_Plaene->setObjectName("label_Plaene");

        verticalLayout->addWidget(label_Plaene);

        reisePlanListWidget = new QListWidget(centralwidget);
        reisePlanListWidget->setObjectName("reisePlanListWidget");

        verticalLayout->addWidget(reisePlanListWidget);

        label_reisen = new QLabel(centralwidget);
        label_reisen->setObjectName("label_reisen");

        verticalLayout->addWidget(label_reisen);

        reiseListWidget = new QListWidget(centralwidget);
        reiseListWidget->setObjectName("reiseListWidget");

        verticalLayout->addWidget(reiseListWidget);

        label_drachenflugDetails = new QLabel(centralwidget);
        label_drachenflugDetails->setObjectName("label_drachenflugDetails");

        verticalLayout->addWidget(label_drachenflugDetails);

        reiseDetailsListWidget = new QListWidget(centralwidget);
        reiseDetailsListWidget->setObjectName("reiseDetailsListWidget");

        verticalLayout->addWidget(reiseDetailsListWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addDracheButton = new QPushButton(centralwidget);
        addDracheButton->setObjectName("addDracheButton");

        buttonLayout->addWidget(addDracheButton);

        addReiseplanButton = new QPushButton(centralwidget);
        addReiseplanButton->setObjectName("addReiseplanButton");

        buttonLayout->addWidget(addReiseplanButton);

        addDrachenreiseButton = new QPushButton(centralwidget);
        addDrachenreiseButton->setObjectName("addDrachenreiseButton");

        buttonLayout->addWidget(addDrachenreiseButton);

        addPassengerButton = new QPushButton(centralwidget);
        addPassengerButton->setObjectName("addPassengerButton");

        buttonLayout->addWidget(addPassengerButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        buttonLayout->addWidget(saveButton);


        verticalLayout->addLayout(buttonLayout);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 25));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName("menuDatei");
        menuDrache_L_schen = new QMenu(menubar);
        menuDrache_L_schen->setObjectName("menuDrache_L_schen");
        menusuchen = new QMenu(menubar);
        menusuchen->setObjectName("menusuchen");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuDrache_L_schen->menuAction());
        menubar->addAction(menusuchen->menuAction());
        menuDatei->addAction(actionEinlesen);
        menuDatei->addAction(actionSpeichern);
        menuDatei->addAction(actionBeenden);
        menuDrache_L_schen->addAction(actionDrache_l_schen);
        menuDrache_L_schen->addAction(actionReiseplan_l_schen);
        menuDrache_L_schen->addAction(actionDrachereise_l_schen);
        menuDrache_L_schen->addAction(actionPassagier_l_schen);
        menusuchen->addAction(actionPerson_suchen);
        menusuchen->addAction(actionLandkarte_suchen);
        toolBar->addAction(actionEinlesen);
        toolBar->addAction(actionPerson_suchen);
        toolBar->addAction(actionLandkarte_suchen);
        toolBar->addAction(actionSpeichern);
        toolBar->addAction(actionBeenden);
        toolBar->addAction(actionDrache_l_schen);
        toolBar->addAction(actionReiseplan_l_schen);
        toolBar->addAction(actionDrachereise_l_schen);
        toolBar->addAction(actionPassagier_l_schen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Drachenflug-Manager", nullptr));
        actionEinlesen->setText(QCoreApplication::translate("MainWindow", "Einlesen", nullptr));
        actionSpeichern->setText(QCoreApplication::translate("MainWindow", "Speichern", nullptr));
        actionBeenden->setText(QCoreApplication::translate("MainWindow", "Beenden", nullptr));
        actionDrache_L_schen->setText(QCoreApplication::translate("MainWindow", "Drache L\303\266schen", nullptr));
        actionReiseplan_L_schen->setText(QCoreApplication::translate("MainWindow", "Reiseplan L\303\266schen", nullptr));
        actionDrachereise_L_schen->setText(QCoreApplication::translate("MainWindow", "Drachereise L\303\266schen", nullptr));
        actionPassagier_L_schen->setText(QCoreApplication::translate("MainWindow", "Passagier L\303\266schen", nullptr));
        actionDrache_l_schen->setText(QCoreApplication::translate("MainWindow", "Drache l\303\266schen", nullptr));
        actionReiseplan_l_schen->setText(QCoreApplication::translate("MainWindow", "Reiseplan l\303\266schen", nullptr));
        actionDrachereise_l_schen->setText(QCoreApplication::translate("MainWindow", "Drachereise l\303\266schen", nullptr));
        actionPassagier_l_schen->setText(QCoreApplication::translate("MainWindow", "Passagier l\303\266schen", nullptr));
        actionEinlesen_2->setText(QCoreApplication::translate("MainWindow", "Einlesen", nullptr));
        actionPerson_suchen->setText(QCoreApplication::translate("MainWindow", "Person suchen", nullptr));
        actionLandkarte_suchen->setText(QCoreApplication::translate("MainWindow", "Landkarte\n"
"suchen", nullptr));
        label_drachenDetails->setText(QCoreApplication::translate("MainWindow", "Details zum Drachen:", nullptr));
        label_Plaene->setText(QCoreApplication::translate("MainWindow", "Reisepl\303\244ne", nullptr));
        label_reisen->setText(QCoreApplication::translate("MainWindow", "Drachenreisen:", nullptr));
        label_drachenflugDetails->setText(QCoreApplication::translate("MainWindow", "Details zur Drachenreise:", nullptr));
        addDracheButton->setText(QCoreApplication::translate("MainWindow", "Drache hinzuf\303\274gen", nullptr));
        addReiseplanButton->setText(QCoreApplication::translate("MainWindow", "Reiseplan hinzuf\303\274gen", nullptr));
        addDrachenreiseButton->setText(QCoreApplication::translate("MainWindow", "Reise hinzuf\303\274gen", nullptr));
        addPassengerButton->setText(QCoreApplication::translate("MainWindow", "Passagier buchen", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Speichern", nullptr));
        menuDatei->setTitle(QCoreApplication::translate("MainWindow", "Datei", nullptr));
        menuDrache_L_schen->setTitle(QCoreApplication::translate("MainWindow", "l\303\266schen", nullptr));
        menusuchen->setTitle(QCoreApplication::translate("MainWindow", "suchen", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
