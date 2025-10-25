#include "kartenszene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <cmath>

KartenSzene::KartenSzene(QObject* parent)
    : QGraphicsScene(parent), centerX(0), centerY(0), offset(0), zoom(0), scaleFactor(1.0), tileSize(256), pixmapItem(nullptr)
{
}

void KartenSzene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!pixmapItem)
        return;  // Wenn keine Karte vorhanden ist, abbrechen

    // Umrechnung der Klickposition in Kartentile (X/Y in Kacheln)
    QPointF relativePos = pixmapItem->mapFromScene(event->scenePos());
    double xTile = relativePos.x() / tileSize + (centerX - offset);
    double yTile = relativePos.y() / tileSize + (centerY - offset);

    // Umrechnung der Kachelposition in GPS-Koordinaten
    double n = std::pow(2.0, zoom);
    double lon = xTile / n * 360.0 - 180.0;
    double latRad = std::atan(std::sinh(M_PI * (1 - 2 * yTile / n)));
    double lat = qRadiansToDegrees(latRad);

    // ************ POI-Erstellung ab hier ************
    QDialog dialog;
    dialog.setWindowTitle("Neuen POI hinzufügen");

    QFormLayout* form = new QFormLayout(&dialog);

    // Eingabefelder
    QLineEdit* nameEdit = new QLineEdit();
    QComboBox* typCombo = new QComboBox();
    typCombo->addItems({"Draggonport", "Höhle", "Baumkrone", "Bergplateau"});

    // Felder zum Formular hinzufügen
    form->addRow("Name:", nameEdit);
    form->addRow("Typ:", typCombo);

    // OK/Abbrechen-Buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addWidget(buttonBox);

    // Verknüpfung: Wenn OK oder Cancel gedrückt wird
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString name = nameEdit->text().trimmed();
        QString typ = typCombo->currentText();

        if (!name.isEmpty()) {
            json j;
            j["name"] = name.toStdString();
            j["typ"] = typ.toStdString();
            j["latitude"] = lat;
            j["longitude"] = lon;

            POI* neuerPoi = new POI(j);  // JSON → POI
            emit poiHinzugefuegt(neuerPoi);  // Signal senden

            // Roter Punkt + Name in Szene
            QPointF scenePos = event->scenePos();
            addEllipse(scenePos.x() - 5, scenePos.y() - 5, 10, 10, QPen(Qt::red), QBrush(Qt::red));

            QGraphicsTextItem* label = addText(name);
            label->setPos(scenePos.x() + 6, scenePos.y() - 10);
        } else {
            QMessageBox::warning(nullptr, "Ungültiger Name", "Bitte gib einen Namen für den POI ein.");
        }
    }



    // HIER IM PRAKTIKUM 5 ERGÄNZEN

    // ************ Ende POI-Erstellung ************

    // Weitergabe an Basis-Klassen-Handler
    QGraphicsScene::mousePressEvent(event);
}

void KartenSzene::setUmrechnungsParameter(int centerX, int centerY, int offset, int zoom, qreal scaleFactor)
{
    // Parameter zum Umrechnen zwischen GPS und Szene-Koordinaten setzen
    this->centerX = centerX;
    this->centerY = centerY;
    this->offset = offset;
    this->zoom = zoom;
    this->scaleFactor = scaleFactor;
}


void KartenSzene::setPixmapItem(QGraphicsPixmapItem *newPixmapItem)
{
    // Referenz auf das Kartenbild setzen
    pixmapItem = newPixmapItem;  // wird im Praktikum 5 gesetzt
}
