#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QStringList>
#include <QDateEdit>
#include <QDialogButtonBox>
#include "DragonPOILayer.h"
#include "dragonmap.h"
#include "filmstudio.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT
public:
    MainWindow(Filmstudio *f, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // ***** Slots für ListWidgets benötigt *****
    void on_drachenListWidget_itemClicked(QListWidgetItem* item);
    void on_reisePlanListWidget_itemClicked(QListWidgetItem *item); // ***** Neu!!! *****
    void on_reiseListWidget_itemClicked(QListWidgetItem *item);

    // ***** Slots für Buttons benötigt *****
    void on_addDracheButton_clicked();
    void on_addReiseplanButton_clicked();                           // ***** Neu!!! *****
    void on_addDrachenreiseButton_clicked();
    void on_addPassengerButton_clicked();
    void on_saveButton_clicked();


    void on_actionEinlesen_triggered();

    void on_actionBeenden_triggered();

    void on_actionSpeichern_triggered();



    void on_actionReiseplan_l_schen_triggered();




    void on_actionPassagier_l_schen_triggered();

    void on_actionDrache_l_schen_triggered();

    void on_actionDrachereise_l_schen_triggered();

    void on_actionPerson_suchen_triggered();

    void on_actionLandkarte_suchen_triggered();

    void on_horizontalSliderZoom_valueChanged(int value);

private:

    Ui::MainWindow* ui;
    Filmstudio* studio;

    DragonMap* mapHandler ;//für den Zugriff auf die Landkarte
    DragonPOILayer* poiLayer;
    //zur Begrenzung des Sliders
    int minZoom=100 ;
    int maxZoom=200;

    void fillDrachenListe();
    void showDrachenDetails(Drache* drache);
    void showReiseplaene(Drache* drache);                           // ***** Neu!!! *****
    void showDrachenreisen(Reiseplan* plan);                        // ***** Geändert!!! *****
    void showDrachenreiseDetails(Drachenreise* reise);
    QString frageDatum(const QString& titel, const QString& label, const QDate& defaultDate);
    void resetZoomSlider();
    void resizeEvent(QResizeEvent* event);
};

#endif // MAINWINDOW_H
