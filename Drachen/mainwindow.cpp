#include "mainwindow.h"
#include "drachenart.h"
#include "drachenflug.h"
#include "nachtlager.h"
#include "suchergebnisdialog.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include<QFormLayout>
#include<QDoubleSpinBox>


// Konstruktor
MainWindow::MainWindow(Filmstudio* f ,QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),studio(f)

{
    ui->setupUi(this);
poiLayer = new DragonPOILayer(studio);

    mapHandler=new DragonMap(ui->graphicsViewMap,ui->horizontalSliderZoom,this);
        fillDrachenListe();





}

// Destruktor
MainWindow::~MainWindow()
{
    delete ui;
    if (studio) delete studio;
    delete mapHandler;
    delete poiLayer;


}

void MainWindow::fillDrachenListe() {
    ui->drachenListWidget->clear();
    for (Drache* d : studio->getDrachenListe()) {
        ui->drachenListWidget->addItem(QString::fromStdString(d->getDrachenName()));
    }
}

void MainWindow::showDrachenDetails(Drache* drache) {
    std::stringstream ss;
    ss << "Name: " << drache->getDrachenName() << "\n"
       << "Player: " << drache->getMeinPlayer() << "\n"
       << "Art: " << drache->getDrachenArt() << "\n"
       << "Geschwindigkeit: " << drache->getGeschwindigkeit() << "\n"
       << "Ausdauer: " << drache->getAusdauer() << "\n"
       << "Erholung: " << drache->getErholung() << "\n"
       << "Preis: " << drache->getDrachenPreis();
    ui->detailTextEdit->setPlainText(QString::fromStdString(ss.str()));
}

void MainWindow::showReiseplaene(Drache* drache) {
    ui->reisePlanListWidget->clear();
    for (Reiseplan* plan : drache->getReiseplaene()) {
        ui->reisePlanListWidget->addItem(QString::fromStdString(plan->getName()));
    }
}

void MainWindow::showDrachenreisen(Reiseplan* plan) {
    ui->reiseListWidget->clear();
    for (Drachenreise* abschnitt : plan->getReiseabschnitte()) {
        ui->reiseListWidget->addItem(QString::number(abschnitt->getReiseNummer()));
    }
}


void MainWindow::showDrachenreiseDetails(Drachenreise* reise) {
    ui->reiseDetailsListWidget->clear();
    QStringList reiseDetails;

    reiseDetails << QString("Reisenummer: %1").arg(reise->getReiseNummer());
    reiseDetails << QString("Abfahrt: %1").arg(QString::fromStdString(reise->getAbfahrt()));
    reiseDetails << QString("Ankunft: %1").arg(QString::fromStdString(reise->getAnkunft()));

    // Spezifische Attribute je nach Typ
    if (Drachenflug* flug = dynamic_cast<Drachenflug*>(reise)) {
        reiseDetails << QString("Flugnummer: %1").arg(flug->getFlugNummer());
        reiseDetails << QString("Ziel: %1").arg(QString::fromStdString(flug->getZiel()));
        reiseDetails << QString("Entfernung: %1 km").arg(flug->getEntfernung());
    }
    else if (Nachtlager* lager = dynamic_cast<Nachtlager*>(reise)) {
        reiseDetails << QString("Lager-ID: %1").arg(lager->getLagerID());
        reiseDetails << QString("Ort: %1").arg(QString::fromStdString(lager->getLagerOrt()));
        reiseDetails << QString("Unterkunft: %1").arg(QString::fromStdString(lager->getUnterkunftsTyp()));
        reiseDetails << QString("Ruhelevel: %1").arg(lager->getRuheLevel());
        reiseDetails << QString("Preis: %1 €").arg(lager->getPreis());
    }

    reiseDetails << "Passagiere:";
    for (const QString& detail : reiseDetails) {
        ui->reiseDetailsListWidget->addItem(detail);
    }

    if (reise->getReiseplan()) {
        for (const std::string& name : reise->getReiseplan()->getPassagiere()) {
            ui->reiseDetailsListWidget->addItem(QString::fromStdString(name));
        }
    }
}

QString MainWindow::frageDatum(const QString &titel, const QString &label, const QDate &defaultDate)
{
    QDialog dialog(this);
    dialog.setWindowTitle(titel);

    QVBoxLayout layout(&dialog);

    QLabel info(label);
    layout.addWidget(&info);

    QDateEdit dateEdit;
    dateEdit.setCalendarPopup(true);
    dateEdit.setDate(defaultDate);
    layout.addWidget(&dateEdit);

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addWidget(&buttons);

    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        return dateEdit.date().toString("dd.MM.yyyy"); // Format anpassen
    }
    return ""; // oder QString(), wenn abgebrochen wurde
}

void MainWindow::resetZoomSlider()
{
    if (!mapHandler)
        return;

    minZoom = mapHandler->berechneMinZoom();   // dynamisch berechnen
    ui->horizontalSliderZoom->setMinimum(minZoom);
    ui->horizontalSliderZoom->setMaximum(maxZoom);

    ui->horizontalSliderZoom->setValue(minZoom);

    // Setzen in Map
    mapHandler->setScaleFactor(minZoom / 100.0);
    mapHandler->aktualisiereZoom();

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (mapHandler) {
        resetZoomSlider();  // Nur wenn AutoZoom noch aktiv
    }

}

void MainWindow::on_drachenListWidget_itemClicked(QListWidgetItem* item) {
    std::string name = item->text().toStdString();
    Drache* drache = studio->sucheDrache(name);
    if (drache) {
        showDrachenDetails(drache);
        showReiseplaene(drache);
        ui->reiseListWidget->clear();
        ui->reiseDetailsListWidget->clear();
    }
}

void MainWindow::on_reisePlanListWidget_itemClicked(QListWidgetItem* item) {
    if (!item || !ui->drachenListWidget->currentItem()) return;
    QListWidgetItem* dracheItem = ui->drachenListWidget->currentItem();
    if (!dracheItem || !item) return;

    Drache* drache = studio->sucheDrache(dracheItem->text().toStdString());
    if (!drache) return;

    Reiseplan* plan = drache->findeReiseplan(item->text().toStdString());
    if (!plan) return;

    showDrachenreisen(plan);
    ui->reiseDetailsListWidget->clear();

    std::map<std::string, POI*> poiSubset = poiLayer->getPOIsFuerReiseplan(plan);

    // Kartenzentrum berechnen (falls leer, verwende aktuelle GPS-Koordinaten)
    auto [lat, lon] = mapHandler->berechneKartenzentrum(
        poiSubset,
        mapHandler->getGPSX(),
        mapHandler->getGPSY()
        );

    // Karte anzeigen mit POI-Subset und aktivem Reiseplan
    mapHandler->landKarteAnzeigen(
        lat, lon,
        mapHandler->getZoom(),
        mapHandler->getTileCount(),
        poiSubset,
        plan,
        [this](POI* poi) { poiLayer->neuenPoiEintragen(poi); }
        );

    // Zoom zurücksetzen
    int minZoom = mapHandler->berechneMinZoom();

        ui->horizontalSliderZoom->setValue(minZoom);


}

void MainWindow::on_reiseListWidget_itemClicked(QListWidgetItem* item) {
    if (!item || !ui->drachenListWidget->currentItem() || !ui->reisePlanListWidget->currentItem()) {
        return; // Frühzeitiger Abbruch bei ungültigen Items
    }
    QListWidgetItem* dracheItem = ui->drachenListWidget->currentItem();
    QListWidgetItem* planItem = ui->reisePlanListWidget->currentItem();
    if (!dracheItem || !planItem || !item) return;

    Drache* drache = studio->sucheDrache(dracheItem->text().toStdString());
    Reiseplan* plan = drache->findeReiseplan(planItem->text().toStdString());
    if (!plan) return;

    int nummer = item->text().toInt();
    for (Drachenreise* r : plan->getReiseabschnitte()) {
        if (r->getReiseNummer() == nummer) {
            showDrachenreiseDetails(r);
            break;
        }
    }
}

void MainWindow::on_addDracheButton_clicked() {
    // 1. Name abfragen
    QString name = QInputDialog::getText(this, "Neuer Drache", "Name des Drachen:");
    if (name.isEmpty()) return;

    // 2. Player abfragen
    QString player = QInputDialog::getText(this, "Spielername", "Name des Spielers:");
    if (player.isEmpty()) return;

    // 3. Art auswählen
    QStringList arten = {"Nachtschatten", "Tagschatten", "ToedlicherNadder", "Skrill"};
    QString art = QInputDialog::getItem(this, "Art auswählen", "Drachenart:", arten, 0, false);

    // ***** 4. Drache erzeugen: Aufgabe 8: Konstruktor mit zwei Parametern anpassen *****
    Drache* neuerDrache = nullptr;
    if (art == "Nachtschatten"){

        neuerDrache = new Nachtschatten(name.toStdString(), player.toStdString());
    }
    else if (art == "Tagschatten"){

        neuerDrache = new Tagschatten(name.toStdString(), player.toStdString());
    }
    else if (art == "ToedlicherNadder"){

        neuerDrache = new ToedlicherNadder(name.toStdString(), player.toStdString());
    }
    else if (art == "Skrill"){

        neuerDrache = new Skrill(name.toStdString(), player.toStdString());
    }
    // 5. Aufgabe 8: diese setter-Aufrufe sollen hier ersetzt werden
   // neuerDrache->setDrachenName(name.toStdString());
// neuerDrache->setMeinPlayer(player.toStdString());

    // 6. Drache hinzufügen
    studio->addDrache(neuerDrache);
    fillDrachenListe();
}

void MainWindow::on_addReiseplanButton_clicked() {
    QListWidgetItem* selectedItem = ui->drachenListWidget->currentItem();
    if (!selectedItem) return;

    Drache* drache = studio->sucheDrache(selectedItem->text().toStdString());
    if (!drache) return;

    drache->addReiseplan(new Reiseplan());
    showReiseplaene(drache);
}

void MainWindow::on_addDrachenreiseButton_clicked() {

    // QListWidgetItem* dracheItem = ui->drachenListWidget->currentItem();
    // QListWidgetItem* planItem = ui->reisePlanListWidget->currentItem();

    // if (!dracheItem || !planItem) {
    //     QMessageBox::warning(this, "Keine Reiseplan ausgewählt",
    //                          "Bitte zuerst eine Reiseplan auswählen");
    //     return;
    // }

    // Drache* drache = studio->sucheDrache(dracheItem->text().toStdString());
    // Reiseplan* plan = drache->findeReiseplan(planItem->text().toStdString());
    // if (!plan) return;

    // QStringList arten = {"Drachenflug", "Nachtlager"};
    // QString art = QInputDialog::getItem(this, "Typ auswählen", "Reisetyp:", arten, 0, false);
    // if (art.isEmpty()) return;

    // //  Startdatum bestimmen: entweder Planende oder heute
    // QDate startDatum;
    // if (plan->getReiseabschnitte().empty()) {
    //     startDatum = QDate::currentDate();
    // } else {
    //     QDate planEnde = QDate::fromString(QString::fromStdString(plan->getPlanEnde()), "dd.MM.yyyy");
    //     startDatum = planEnde.isValid() ? planEnde : QDate::currentDate();
    // }

    // // Abfahrtsdatum erfragen (mit Startdatum vorbelegt)
    // QString abfahrtStr = frageDatum("Drachenreise", "Abfahrtsdatum auswählen", startDatum);
    // QDate abfahrtDate = QDate::fromString(abfahrtStr, "dd.MM.yyyy");
    // if (!abfahrtDate.isValid()) return;

    // // Ankunftsdatum Voreinstellung abhängig von art
    // QDate defaultAnkunftDate = (art == "Drachenflug") ? abfahrtDate : abfahrtDate.addDays(1);

    // // Ankunftsdatum erfragen (mit default vorbelegt)
    // QString ankunftStr = frageDatum("Drachenreise", "Ankunftsdatum auswählen", defaultAnkunftDate);
    // QDate ankunftDate = QDate::fromString(ankunftStr, "dd.MM.yyyy");
    // if (!ankunftDate.isValid()) return;

    // if (abfahrtDate > ankunftDate) {
    //     QMessageBox::warning(this, "Ungültige Datumsauswahl",
    //                          "Das Abfahrtsdatum darf nicht nach dem Ankunftsdatum liegen.");
    //     return;
    // }
    // // In Strings für Konstruktor wandeln
    // QString abfahrt = abfahrtDate.toString("dd.MM.yyyy");
    // QString ankunft = ankunftDate.toString("dd.MM.yyyy");

    // Drachenreise* reise = nullptr;

    // if (art == "Drachenflug") {
    //     QString ziel = QInputDialog::getText(this, "Flug", "Ziel:");
    //     if (ziel.isEmpty()) return;

    //     double entfernung = QInputDialog::getDouble(this, "Flug", "Entfernung (km):", 100.0, 0.0);
    //     reise = new Drachenflug(abfahrt.toStdString(), ankunft.toStdString(),
    //                             ziel.toStdString(), entfernung);
    // } else {
    //     QString ort = QInputDialog::getText(this, "Nachtlager", "Ort:");
    //     if (ort.isEmpty()) return;

    //     QStringList typen = {"Bergplateau", "Höhle", "Baumkrone"};
    //     QString typ = QInputDialog::getItem(this, "Typ", "Unterkunftstyp:", typen, 0, false);
    //     if (typ.isEmpty()) return;

    //     int ruhe = QInputDialog::getInt(this, "Nachtlager", "Ruhelevel:", 5, 1, 10);
    //     double preis = QInputDialog::getDouble(this, "Nachtlager", "Preis:", 100.0, 0.0);

    //     reise = new Nachtlager(abfahrt.toStdString(), ankunft.toStdString(), preis,
    //                            ort.toStdString(), typ.toStdString(), ruhe);
    // }

    // if (reise) {
    //     plan->addReise(std::unique_ptr<Drachenreise>(reise));
    //     showDrachenreisen(plan);
    // }
    QListWidgetItem* dracheItem = ui->drachenListWidget->currentItem();
    QListWidgetItem* planItem = ui->reisePlanListWidget->currentItem();
    if (!dracheItem || !planItem) {
        QMessageBox::warning(this, "Keine Drachen oder Reiseplan ausgewählt",
                             "Bitte zuerst Drachen und Reiseplan auswählen");
        return;
    }

    Drache* drache = studio->sucheDrache(dracheItem->text().toStdString());
    Reiseplan* plan = drache->findeReiseplan(planItem->text().toStdString());
    if (!plan) return;

    QString qDateStr = QString::fromStdString(plan->getPlanEnde());
    QDate date = QDate::fromString(qDateStr, "dd.MM.yyyy");
    if (!date.isValid())
        date = QDate::currentDate();

    QStringList arten = {"Drachenflug", "Nachtlager"};
    QString art = QInputDialog::getItem(this, "Typ auswählen", "Reisetyp:", arten, 0, false);

    Drachenreise* reise = nullptr;

    static QString letztesZiel;  // STEP 1: letztes Ziel merken für Vorauswahl im Nachtlager

    if (art == "Drachenflug") {
        QString abfahrt = frageDatum("von", "Bitte Datum von wählen:", date);
        QString ankunft = frageDatum("bis", "Bitte Datum bis wählen:", date);
        if (abfahrt.isEmpty() || ankunft.isEmpty()) return;


        QStringList alleZiele;  // STEP 2: Statt freier Texteingabe → Auswahl aller gültigen POIs
        for (const auto& [_, poi] : studio->getPoiMap()) {
            alleZiele << QString::fromStdString(poi->getName());
        }

        QString ziel = QInputDialog::getItem(this, "Flug", "Ziel auswählen:", alleZiele, 0, false);  // STEP 3: Dialog mit Auswahl
        if (ziel.isEmpty()) return;

        reise = new Drachenflug(abfahrt.toStdString(), ankunft.toStdString(), ziel.toStdString(), 0.0);

        letztesZiel = ziel;  // STEP 4: Ziel merken für spätere Vorauswahl
    }
    else {
        QString abfahrt = frageDatum("von", "Bitte Datum von wählen:", date);
        QString ankunft = frageDatum("bis", "Bitte Datum bis wählen:", date.addDays(1));
        if (abfahrt.isEmpty() || ankunft.isEmpty()) return;

        // STEP 5: Nur gültige Nachtlager-Orte (nach Typ)
        QStringList ortNamen;
        QMap<QString, QString> nameZuTyp;
        for (const auto& [_, poi] : studio->getPoiMap()) {
            std::string typ = poi->getTyp();
            if (typ == "Höhle" || typ == "Baumkrone" || typ == "Bergplateau") {
                QString name = QString::fromStdString(poi->getName());
                ortNamen << name;
                nameZuTyp[name] = QString::fromStdString(typ);
            }
        }

        int vorAuswahlIndex = ortNamen.indexOf(letztesZiel);
        if (vorAuswahlIndex < 0) vorAuswahlIndex = 0;

        QString ort = QInputDialog::getItem(this, "Nachtlager", "Ort auswählen:",
                                            ortNamen, vorAuswahlIndex, false);
        if (ort.isEmpty()) return;

        QString typ = nameZuTyp.value(ort);  // STEP 7: Typ wird automatisch aus Map gezogen

        int ruhe = QInputDialog::getInt(this, "Nachtlager", "Ruhelevel:", 5, 1, 10);
        double preis = QInputDialog::getDouble(this, "Nachtlager", "Preis:", 100.0, 0.0);

        reise = new Nachtlager(abfahrt.toStdString(), ankunft.toStdString(),
                               preis, ort.toStdString(), typ.toStdString(), ruhe);
    }

    if (reise) {
        plan->addReise(std::unique_ptr<Drachenreise>(reise));

        studio->aktualisiereEntfernungenInReiseplan(plan);  // STEP 8: Entfernungen aktualisieren lassen
        on_reisePlanListWidget_itemClicked(ui->reisePlanListWidget->currentItem()); // STEP 9: GUI sauber aktualisieren

        showDrachenreisen(plan);
    }
}


void MainWindow::on_addPassengerButton_clicked() {
    QListWidgetItem* flugItem = ui->reiseListWidget->currentItem();

    if (!flugItem) {
        QMessageBox::warning(this, "Keine Drachenreise ausgewählt",
                             "Bitte zuerst eine Drachenreise auswählen");
        return;
    }

    QString name = QInputDialog::getText(this, "Passagier hinzufügen", "Name des Passagiers:");
    if (name.isEmpty()) return;

    int reiseNummer = flugItem->text().toInt();
    Drachenreise* reise = studio->getDrachenreise(reiseNummer);
    if (!reise) return;

    // Zugriff auf Reiseplan:
    if (reise->getReiseplan()) {
        reise->getReiseplan()->addPassagier(name.toStdString());
        showDrachenreiseDetails(reise);
    }
}

void MainWindow::on_saveButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Daten speichern", "", "JSON Dateien (*.json)");
    if (!fileName.isEmpty()) {
        studio->speichernJSON(fileName.toStdString());
        QMessageBox::information(this, "Gespeichert", "Die Daten wurden erfolgreich gespeichert.");
    }
    else
        QMessageBox::warning(this, "Speichern abgebrochen", "Dateiname wurde nicht angegeben.");
}

void MainWindow::on_actionEinlesen_triggered()
{

    ui->drachenListWidget->clear();
    ui->detailTextEdit->clear();
    ui->reisePlanListWidget->clear();
    ui->reiseListWidget->clear();
    ui->reiseDetailsListWidget->clear();

    on_actionLandkarte_suchen_triggered();

    QString fileName = QFileDialog::getOpenFileName(this, "POI-Datei einlesen", "", "JSON Dateien (*.json)");
    if (fileName.isEmpty()) {
        return;
    }
    try {
        if (fileName.contains("poi", Qt::CaseInsensitive)) {
            // Wenn der Dateiname "poi" enthält → POI-Datei einlesen
            studio->einlesenPOIDatei(fileName.toStdString());

            QMessageBox::information(this, "POI-Daten eingelesen", "Die POI-Daten wurden erfolgreich eingelesen.");
        } else {
            // Sonst → normale JSON-Daten einlesen
            studio->einlesenJSON(fileName.toStdString());
            fillDrachenListe();
            QMessageBox::information(this, "Daten eingelesen", "Die Daten wurden erfolgreich eingelesen.");
        }
    }
        catch (const json::parse_error& e) {
            QMessageBox::critical(this, "JSON-Fehler", QString("Fehler beim Parsen:\n%1").arg(e.what()));
        }
        catch (const json::type_error& e) {
            QMessageBox::critical(this, "JSON-Typfehler", QString("Typfehler in den Daten:\n%1").arg(e.what()));
        }
        catch (const json::out_of_range& e) {
            QMessageBox::critical(this, "JSON-Strukturfehler", QString("Feld fehlt oder Indexfehler:\n%1").arg(e.what()));
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Allgemeiner Fehler", QString("Ein unbekannter Fehler ist aufgetreten:\n%1").arg(e.what()));
        }

        mapHandler->landKarteAnzeigen(
            mapHandler->getGPSX(),
            mapHandler->getGPSY(),
            mapHandler->getZoom(),
            mapHandler->getTileCount(),
            studio->getPoiMap(),
            nullptr,
            [this](POI* poi) { poiLayer->neuenPoiEintragen(poi); }
            );

}


void MainWindow::on_actionBeenden_triggered()
{

    close();
}


void MainWindow::on_actionSpeichern_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Daten speichern", "", "JSON Dateien (*.json)");
    if (fileName.isEmpty()) {
        return;
    }
    try {
        studio->speichernPOIDatei(fileName.toStdString());
        //studio->speichernJSON(fileName.toStdString());
        QMessageBox::information(this, "Gespeichert", "Die Daten wurden erfolgreich gespeichert.");
    } catch (const std::exception& e) {
         QMessageBox::critical(this, "Fehler beim Speichern", QString::fromStdString(e.what()));
    }


}









void MainWindow::on_actionPassagier_l_schen_triggered()
{
    QListWidgetItem* drachenItem = ui->drachenListWidget->currentItem();
    QListWidgetItem* planItem = ui->reisePlanListWidget->currentItem();
    QListWidgetItem* passagierItem = ui->reiseDetailsListWidget->currentItem();

    if (!drachenItem || !planItem || !passagierItem) {
        QMessageBox::warning(this, "Achtung", "Bitte Drachen, Reiseplan und Passagier auswählen.");
        return;
    }
    QString drachenName = drachenItem->text();
    QString planName = planItem->text();
    QString passagier = passagierItem->text();

    Drache* drache = studio->sucheDrache(drachenName.toStdString());
    if (!drache) {
        QMessageBox::critical(this, "Fehler", "Drache wurde im Filmstudio leider nicht gefunden.");
        return;
    }
    Reiseplan* plan = drache->findeReiseplan(planName.toStdString());
    if (!plan) {
        QMessageBox::critical(this, "Fehler", "Der ausgelegte Reiseplan wurde beim Drachen leider nicht gefunden.");
        return;
    }
    if (QMessageBox::question(this, "Passagier löschen",
                              QString("Passagier %1 wirklich aus dieser Reise streichen?").arg(passagier)) != QMessageBox::Yes) {
        return;
    }
    if (plan->loeschePassagier(passagier.toStdString())) {
        delete ui->reiseDetailsListWidget->takeItem(ui->reiseDetailsListWidget->currentRow());
    } else {
        QMessageBox::warning(this, "Achtung", "Passagier wurde im Plan leider nicht gefunden.");
    }
}


void MainWindow::on_actionReiseplan_l_schen_triggered()
{
    QListWidgetItem* drachenItem = ui->drachenListWidget->currentItem();
    QListWidgetItem* reiseplanItem = ui->reisePlanListWidget->currentItem();


    // 2. Prüfen ob etwas ausgewählt wurde
    if (!drachenItem || !reiseplanItem) {
        QMessageBox::warning(this, "Warnung", "Bitte sowohl einen Drachen als auch einen Reiseplan auswählen.");
        return;
    }
    // 3. Namen extrahieren
    QString drachenName = drachenItem->text();
    QString reiseplanName = reiseplanItem->text();

    // 4. Drachen über Filmstudio finden
    Drache* drache = studio->sucheDrache(drachenName.toStdString());
    if (!drache) {
        QMessageBox::critical(this, "Fehler", "Drache nicht gefunden.");
        return;
    }
    // 5. Sicherheitsabfrage ob wirklich gelöscht werden soll
    if (QMessageBox::question(this, "Reiseplan löschen",
                              QString("Reiseplan \"%1\" wirklich löschen?").arg(reiseplanName)) != QMessageBox::Yes) {
        return;
    }

    // 6. Löschen versuchen
    if (drache->loescheReiseplan(reiseplanName.toStdString())) {
        // 7. Listen aktualisieren
        fillDrachenListe();
        ui->reisePlanListWidget->clear();
        ui->reiseListWidget->clear();
        ui->reiseDetailsListWidget->clear();
        ui->detailTextEdit->clear();
    } else {
        QMessageBox::warning(this, "Warnung", "Reiseplan konnte nicht gelöscht werden.");
    }
}


void MainWindow::on_actionDrache_l_schen_triggered()
{
    // 1. Aktuell ausgewählten Drachen aus der Liste holen
        QListWidgetItem* drachenItem = ui->drachenListWidget->currentItem();

    // 2. Prüfen, ob etwas ausgewählt wurde
    if (!drachenItem) {
        QMessageBox::warning(this, "Warnung", "Bitte Drache auswählen");
        return;
    }

    // 3. Sicherheitsabfrage, ob der Drache wirklich gelöscht werden soll
    if (QMessageBox::question(this, "Drache löschen", "Drache wirklich löschen?") != QMessageBox::Yes) {
        return;
    }

    // 4. Drachenname extrahieren
    QString drachenName = drachenItem->text();

    // 5. Löschversuch im Filmstudio durchführen
    if (studio->loescheDrache(drachenName.toStdString())) {
        // 6. Liste neu füllen
        fillDrachenListe();

        // 7. Alle Detailfenster leeren
        ui->detailTextEdit->clear();
        ui->reisePlanListWidget->clear();
        ui->reiseListWidget->clear();
        ui->reiseDetailsListWidget->clear();
    }
}


void MainWindow::on_actionDrachereise_l_schen_triggered()
{
    QListWidgetItem* drachenItem = ui->drachenListWidget->currentItem();
    QListWidgetItem* reiseplanItem = ui->reisePlanListWidget->currentItem();
    QListWidgetItem* reisenItem = ui->reiseListWidget->currentItem();

    // 2. Prüfen ob etwas ausgewählt wurde
    if (!drachenItem || !reiseplanItem ||!reisenItem) {
        QMessageBox::warning(this, "Warnung", "Bitte sowohl einen Drachen als auch einen Reiseplan auswählen.");
        return;
    }


    // 3. Namen extrahieren
    QString drachenName = drachenItem->text();
    QString planName = reiseplanItem->text();
    QString reiseZiel = reisenItem->text();


    // 4. Drachen über Filmstudio finden
    Drache* drache = studio->sucheDrache(drachenName.toStdString());
    if (!drache) {
        QMessageBox::critical(this, "Fehler", "Drache nicht gefunden.");
        return;
    }
    // 5. Reiseplan suchen
    Reiseplan* plan = drache->findeReiseplan(planName.toStdString());
    if (!plan) {
        QMessageBox::critical(this, "Fehler", "Reiseplan nicht gefunden.");
        return;
    }
    // 6. Sicherheitsabfrage
    if (QMessageBox::question(this, "Drachenreise löschen",
                              QString("Drachenreise nach \"%1\" wirklich löschen?").arg(reiseZiel)) != QMessageBox::Yes) {
        return;
    }

    // 7. Versuchen zu löschen

    int reiseNummer = reiseZiel.toInt();


    if (plan->loescheDrachenreise(reiseNummer)) {
        showDrachenreisen(plan);
        ui->reiseDetailsListWidget->clear();

        on_reisePlanListWidget_itemClicked(ui->reisePlanListWidget->currentItem()); // Workaround

    } else {
        QMessageBox::warning(this, "Fehler", "Drachenreise konnte nicht gelöscht werden.");
    }


}




void MainWindow::on_actionPerson_suchen_triggered()
{
    bool ok;
    QString person = QInputDialog::getText(this, "Person suchen", "Name der Person :", QLineEdit::Normal, "", &ok);
    if(person.isEmpty()){
        return;
        }
    else if (ok && !person.isEmpty()) {
        std::string personStd = person.toStdString();

        std::vector<ReiseInfo*> alsPlayer = studio->findeReiseplaeneAlsPlayer(personStd);
        std::vector<ReiseInfo*> alsPassagier = studio->findeReiseplaeneAlsPassagier(personStd);

        SuchergebnisDialog dialog(studio,this);

        dialog.starteSuche(person);



        dialog.exec();
    }

}


void MainWindow::on_actionLandkarte_suchen_triggered()
{
    resetZoomSlider();   // Zoom-Slider zurücksetzen

    QDialog dialog(this);
    dialog.setWindowTitle("GPS Koordinaten und Optionen");
    QFormLayout form(&dialog);

    QDoubleSpinBox* latSpin = new QDoubleSpinBox(&dialog);
    latSpin->setRange(-90.0, 90.0);
    latSpin->setDecimals(6);
    latSpin->setValue(mapHandler->getGPSX());
    form.addRow("Latitude:", latSpin);

    QDoubleSpinBox* lonSpin = new QDoubleSpinBox(&dialog);
    lonSpin->setRange(-180.0, 180.0);
    lonSpin->setDecimals(6);
    lonSpin->setValue(mapHandler->getGPSY());
    form.addRow("Longitude:", lonSpin);

    QSpinBox* zoomSpin = new QSpinBox(&dialog);
    zoomSpin->setRange(8, 15);
    zoomSpin->setValue(mapHandler->getZoom());
    form.addRow("Zoom (8–15):", zoomSpin);

    QSpinBox* tileCountSpin = new QSpinBox(&dialog);
    tileCountSpin->setRange(3, 13);
    tileCountSpin->setSingleStep(2);
    tileCountSpin->setValue(mapHandler->getTileCount());
    form.addRow("Tile Count (3–13):", tileCountSpin);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
        return;

    // Werte übernehmen
    double lat = latSpin->value();
    double lon = lonSpin->value();
    int zoom = zoomSpin->value();
    int tileCount = tileCountSpin->value();

    mapHandler->setGPSX(lat);
    mapHandler->setGPSY(lon);
    mapHandler->setZoom(zoom);
    mapHandler->setTileCount(tileCount);

    // Karte anzeigen
    mapHandler->landKarteAnzeigen(
        lat, lon, zoom, tileCount,
        studio->getPoiMap(),
        nullptr,
        [this](POI* poi) { poiLayer->neuenPoiEintragen(poi); }
        );

    resetZoomSlider();               // Zoom-Slider zurücksetzen
    mapHandler->aktualisiereZoom();  // wichtig: wendet Zoom an

}


void MainWindow::on_horizontalSliderZoom_valueChanged(int value)
{
    double faktor = value / 100.0;  // Sliderwert (z.B. 150) → Faktor 1.5
    mapHandler->setScaleFactor(faktor);
    mapHandler->aktualisiereZoom();  // Zoom in der MapView anwenden
}

