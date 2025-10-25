#include "suchergebnisdialog.h"
#include "drachenflug.h"
#include "drachenflugdialog.h"
#include "nachtlager.h"
#include "nachtlagerdialog.h"
#include "ui_suchergebnisdialog.h"

#include<QMessageBox>

SuchergebnisDialog::SuchergebnisDialog(Filmstudio *s, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SuchergebnisDialog),studio(s)
{
    ui->setupUi(this);

    // Tabellen initialisieren
    QStringList headerPlayer = {"PlanNr.", "PlanName", "ReiseBeginn", "ReiseEnde"};
    QStringList headerPassagier = {"PlanNr.", "PlanName", "ReiseBeginn", "ReiseEnde"};
    QStringList headerReiseabschnitte ={"Typ", "Ziel/Lagerort", "Abfahrt", "Ankunft", "Preis"};

    // Setzt die Anzahl der Spalten beider Tabellen (Player & Passagier) auf 5
    ui->tableWidgetPlayer->setColumnCount(5);
    ui->tableWidgetPassagier->setColumnCount(5);
    ui->WidgetReiseabschnitte->setColumnCount(5);

    // Setzt die Breiten der einzelnen Spalten
    ui->tableWidgetPlayer->setColumnWidth(0, 50);   // Spalte "PlanNr."
    ui->tableWidgetPlayer->setColumnWidth(1, 150);  // Spalte "PlanName"
    ui->tableWidgetPlayer->setColumnWidth(2, 120);  // Spalte "Beginn"
    ui->tableWidgetPlayer->setColumnWidth(3, 120);  // Spalte "Ende"
    ui->tableWidgetPlayer->setColumnWidth(4, 80);  // Spalte "preis"

    ui->tableWidgetPassagier->setColumnWidth(0, 50);   // Spalte "PlanNr."
    ui->tableWidgetPassagier->setColumnWidth(1, 150);  // Spalte "PlanName"
    ui->tableWidgetPassagier->setColumnWidth(2, 120);  // Spalte "Beginn"
    ui->tableWidgetPassagier->setColumnWidth(3, 120);  // Spalte "Ende"
    ui->tableWidgetPassagier->setColumnWidth(4, 80);  // Spalte "preis"

    ui->WidgetReiseabschnitte->setColumnWidth(0, 100);  // Typ
    ui->WidgetReiseabschnitte->setColumnWidth(1, 150);  // Ziel/Lagerort
    ui->WidgetReiseabschnitte->setColumnWidth(2, 120);  // Abfahrt
    ui->WidgetReiseabschnitte->setColumnWidth(3, 120);  // Ankunft
    ui->WidgetReiseabschnitte->setColumnWidth(4, 80);   // Preis

    this->setMinimumWidth(565);  // Minimalbreite festlegen
    this->setMaximumWidth(565);  // Minimalbreite festlegen

    // Setzt die Beschriftungen der Spaltenköpfe (z.B. PlanNr., Name, Beginn, Ende)
    ui->tableWidgetPlayer->setHorizontalHeaderLabels(headerPlayer);
    ui->tableWidgetPassagier->setHorizontalHeaderLabels(headerPassagier);
    ui->WidgetReiseabschnitte->setHorizontalHeaderLabels(headerReiseabschnitte);

    // Sorgt dafür, dass die letzte Spalte automatisch den verbleibenden Platz nutzt
    ui->tableWidgetPlayer->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetPassagier->horizontalHeader()->setStretchLastSection(true);
    ui->WidgetReiseabschnitte->horizontalHeader()->setStretchLastSection(true);


    // Verhindert, dass Zellen direkt bearbeitet werden können (rein zur Anzeige)
    ui->tableWidgetPlayer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetPassagier->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->WidgetReiseabschnitte->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Macht die Auswahl zeilenweise – beim Klicken wird die ganze Zeile markiert
    ui->tableWidgetPlayer->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetPassagier->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->WidgetReiseabschnitte->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Erlaubt nur eine einzige Auswahl gleichzeitig – keine Mehrfachauswahl
    ui->tableWidgetPlayer->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetPassagier->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->WidgetReiseabschnitte->setSelectionMode(QAbstractItemView::SingleSelection);

    // Blendet die linke vertikale Kopfspalte (Zeilennummerierung) aus
    ui->tableWidgetPlayer->verticalHeader()->setVisible(false);
    ui->tableWidgetPassagier->verticalHeader()->setVisible(false);
    ui->WidgetReiseabschnitte->verticalHeader()->setVisible(false);

    // setzt lineEdit als nicht editierbar
    ui->lineEditPassagierName->setReadOnly(true);

    // Hintergrundfarbe der Headerzeile ändern
    QHeaderView* headerTablePlayer = ui->tableWidgetPlayer->horizontalHeader();
    headerTablePlayer->setStyleSheet("QHeaderView::section { background-color: lightblue; color: black; }");

    QHeaderView* headerTablePassagier = ui->tableWidgetPassagier->horizontalHeader();
    headerTablePassagier->setStyleSheet("QHeaderView::section { background-color: rgb(200, 245, 220); color: black; }");

    QHeaderView* header  = ui->WidgetReiseabschnitte->horizontalHeader();
    header ->setStyleSheet("QHeaderView::section { background-color: rgb(200, 245, 220); color: black; }");


}

SuchergebnisDialog::~SuchergebnisDialog()
{
    delete ui;
}

void SuchergebnisDialog::addPlayerEntry(int nummer, const QString &name, const QString &beginn, const QString &ende,double  preis)
{


    int row = ui->tableWidgetPlayer->rowCount();
    ui->tableWidgetPlayer->insertRow(row);
    ui->tableWidgetPlayer->setItem(row, 0, new QTableWidgetItem(QString::number(nummer)));
    ui->tableWidgetPlayer->setItem(row, 1, new QTableWidgetItem(name));
    ui->tableWidgetPlayer->setItem(row, 2, new QTableWidgetItem(beginn));
    ui->tableWidgetPlayer->setItem(row, 3, new QTableWidgetItem(ende));
    ui->tableWidgetPlayer->setItem(row, 4, new QTableWidgetItem(QString::number(preis,'f',2)));

}

void SuchergebnisDialog::addPassagierEntry(int nummer, const QString &name, const QString &beginn, const QString &ende,double  preis)
{
    int row = ui->tableWidgetPassagier->rowCount();
    ui->tableWidgetPassagier->insertRow(row);
    ui->tableWidgetPassagier->setItem(row, 0, new QTableWidgetItem(QString::number(nummer)));
    ui->tableWidgetPassagier->setItem(row, 1, new QTableWidgetItem(name));
    ui->tableWidgetPassagier->setItem(row, 2, new QTableWidgetItem(beginn));
    ui->tableWidgetPassagier->setItem(row, 3, new QTableWidgetItem(ende));
    ui->tableWidgetPassagier->setItem(row, 4, new QTableWidgetItem(QString::number(preis,'f',2)));

}

void SuchergebnisDialog::setPassagierName(const QString &name)
{
     ui->lineEditPassagierName->setText(name);
}

void SuchergebnisDialog::starteSuche(const QString &name)
{
    ui->lineEditPassagierName->setReadOnly(false);
    ui->lineEditPassagierName->setText(name);
    ui->tableWidgetPlayer->setRowCount(0);      // vorhandene Zeilen löschen
    ui->tableWidgetPassagier->setRowCount(0);   // vorhandene Zeilen löschen

    std::string nameStd = name.toStdString();

    std::vector<ReiseInfo*> alsPlayer = studio->findeReiseplaeneAlsPlayer(nameStd);
    std::vector<ReiseInfo*> alsPassagier = studio->findeReiseplaeneAlsPassagier(nameStd);

    for (ReiseInfo* info : alsPlayer) {
        addPlayerEntry(info->nummer,
                       QString::fromStdString(info->name),
                       QString::fromStdString(info->beginn),
                       QString::fromStdString(info->ende),
                       info->preis);


        delete info;
    }

    for (ReiseInfo* info : alsPassagier) {
        addPassagierEntry(info->nummer,
                          QString::fromStdString(info->name),
                          QString::fromStdString(info->beginn),
                          QString::fromStdString(info->ende),
                          info->preis);
        delete info;
    }

}

void SuchergebnisDialog::zeigeReiseabschnitte(int planN)
{
    ui->WidgetReiseabschnitte->setRowCount(0); // Leeren

    aktuellerPlan  = studio->findeReiseplan(planN);
    if (!aktuellerPlan ) return;

    const auto& abschnitte = aktuellerPlan ->getReiseabschnitte();
    for (Drachenreise* r : abschnitte) {
        int row = ui->WidgetReiseabschnitte->rowCount();
        ui->WidgetReiseabschnitte->insertRow(row);


        // Spalte 0: Icon basierend auf dem tatsächlichen Typ
        QTableWidgetItem* iconItem = new QTableWidgetItem();
        if (auto* flug = dynamic_cast<Drachenflug*>(r)) {
            iconItem->setIcon(QIcon(":/icons/drachenflug.svg")); // z.B. Symbol für Drachenflug
            ui->WidgetReiseabschnitte->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(flug->getZiel())));
        }
        else if (auto* lager = dynamic_cast<Nachtlager*>(r)) {
            iconItem->setIcon(QIcon(":/icons/nachtlager.svg")); // z.B. Symbol für Nachtlager
            ui->WidgetReiseabschnitte->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(lager->getLagerOrt())));
        } else {
            if (!flug && !lager) continue;
        }

        ui->WidgetReiseabschnitte->setItem(row, 0, iconItem);

       // ui->WidgetReiseabschnitte->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(r->getTyp())));

        // Ziel/Lagerort je nach Typ unterschiedlich
        ui->WidgetReiseabschnitte->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(r->getAbfahrt())));
        ui->WidgetReiseabschnitte->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(r->getAnkunft())));
        ui->WidgetReiseabschnitte->setItem(row, 4, new QTableWidgetItem(QString::number(r->getPreis(), 'f', 2)));
    //     QString ziel = (r->getTyp() == "nachtlager")
    //                        ? QString::fromStdString(static_cast<Nachtlager*>(r)->getLagerOrt())
    //                        : QString::fromStdString(static_cast<Drachenflug*>(r)->getZiel());

    //     ui->WidgetReiseabschnitte->setItem(row, 1, new QTableWidgetItem(ziel));
    //     ui->WidgetReiseabschnitte->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(r->getAbfahrt())));
    //     ui->WidgetReiseabschnitte->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(r->getAnkunft())));
    //     ui->WidgetReiseabschnitte->setItem(row, 4, new QTableWidgetItem(QString::number(r->getPreis(), 'f', 2)));
    // }
    }
}

void SuchergebnisDialog::on_pushButtonSuche_clicked()
{
    QString name = ui->lineEditPassagierName->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warnung", "Bitte geben Sie einen Namen ein.");
        return;
    }

    starteSuche(name);


}


void SuchergebnisDialog::on_WidgetReiseabschnitte_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    if (!aktuellerPlan || row < 0 || row >= aktuellerPlan->getReiseabschnitte().size())
        return;

    Drachenreise* reise = aktuellerPlan->getReiseabschnitte().at(row);

    if (reise->getTyp() == "nachtlager") {
        Nachtlager* nachtlager = dynamic_cast<Nachtlager*>(reise);
        if (nachtlager) {
            NachtlagerDialog dlg(nachtlager, this);
            if (dlg.exec() == QDialog::Accepted) {
                aktuellerPlan->sortiereReisen();
                QMessageBox::information(this, "Geändert", "Nachtlager wurde aktualisiert.");
                zeigeReiseabschnitte(aktuellerPlan->getReiseplanNummer());
            }
        }
    } else if (reise->getTyp() == "drachenflug") {
        Drachenflug* flug = dynamic_cast<Drachenflug*>(reise);
        if (flug) {
            DrachenflugDialog dlg(flug, this);
            if (dlg.exec() == QDialog::Accepted) {
                aktuellerPlan->sortiereReisen();
                QMessageBox::information(this, "Geändert", "Drachenflug wurde aktualisiert.");
                zeigeReiseabschnitte(aktuellerPlan->getReiseplanNummer());
            }
        }
    }
}


void SuchergebnisDialog::on_tableWidgetPlayer_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem* planItem = ui->tableWidgetPlayer->item(row, 0); // Annahme: Spalte 0 enthält planNr
    if (!planItem) return;

    int planNr = planItem->text().toInt();
    zeigeReiseabschnitte(planNr);
}


void SuchergebnisDialog::on_tableWidgetPassagier_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem* planItem = ui->tableWidgetPassagier->item(row, 0);
    if (!planItem) return;

    int planNr = planItem->text().toInt();
    zeigeReiseabschnitte(planNr);
}

