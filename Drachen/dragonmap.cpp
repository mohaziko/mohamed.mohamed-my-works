#include "DragonMap.h"
#include "kartenszene.h"
#include "POI.h"
#include "drachenflug.h"
#include "nachtlager.h"
#include "reiseplan.h"
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkDiskCache>
#include <QSlider>
#include <QEventLoop>
#include <QGraphicsView>
#include <QtMath>

DragonMap::DragonMap(QGraphicsView* view, QSlider* zoomSlider, QObject* parent)
    : QObject(parent), view(view), zoomSlider(zoomSlider), scaleFactor(1.0)
{
    view->setRenderHint(QPainter::Antialiasing); // Schöneres Zeichnen der Karte
    connect(zoomSlider, &QSlider::valueChanged, this, &DragonMap::aktualisiereZoom); // Zoomänderung verbinden
}

void DragonMap::latLonToTile(double lat, double lon, int zoom, int &tileX, int &tileY) {
    double latRad = qDegreesToRadians(lat); // Umrechnung in Bogenmaß
    int n = 1 << zoom; // Anzahl der Kacheln in jeder Richtung
    tileX = static_cast<int>(n * ((lon + 180.0) / 360.0)); // Längengrad zu Tile-X
    tileY = static_cast<int>(n * (1.0 - log(tan(latRad) + 1.0 / cos(latRad)) / M_PI) / 2.0); // Breitengrad zu Tile-Y
}

std::pair<double, double> DragonMap::berechneKartenzentrum(const std::map<std::string, POI*>& pois, double fallbackLat, double fallbackLon) {
    if (pois.empty()) return {fallbackLat, fallbackLon}; // Fallback-Zentrum
    // Min/Max-Berechnung über alle POIs
    double minLat = 90.0, maxLat = -90.0, minLon = 180.0, maxLon = -180.0;
    for (const auto& [_, poi] : pois) {
        double lat = poi->getLatitude();
        double lon = poi->getLongitude();
        minLat = std::min(minLat, lat);
        maxLat = std::max(maxLat, lat);
        minLon = std::min(minLon, lon);
        maxLon = std::max(maxLon, lon);
    }
    return { (minLat + maxLat) / 2.0, (minLon + maxLon) / 2.0 }; // Mittelpunkt zurückgeben
}

void DragonMap::landKarteAnzeigen(double lat, double lon, int zoom, int tileCount,
                                  const std::map<std::string, POI*>& pois,
                                  Reiseplan* plan,
                                  std::function<void(POI*)> poiCallback)
{
    // Übergabewerte in Member speichern ---
    this->tileCount = tileCount;
    this->tileSize = 256; // ist zwar konstant, aber zur Sicherheit setzen
    this->zoom = zoom;
    this->GPSX = lat;
    this->GPSY = lon;
    this->poiCallback = poiCallback;

    const int offset = tileCount / 2;
    int centerX, centerY;
    latLonToTile(lat, lon, zoom, centerX, centerY); // Zentrum berechnen

    if (!manager)
        manager = new QNetworkAccessManager(this); // Netzwerkmanager initialisieren

    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this); // Caching für Tiles
    diskCache->setCacheDirectory("tileCacheNZ");
    diskCache->setMaximumCacheSize(100 * 1024 * 1024); // 100 MB
    manager->setCache(diskCache);

    QPixmap mapPixmap(tileSize * tileCount, tileSize * tileCount); // Leeres Bild für die Karte
    QPainter painter(&mapPixmap); // Zum Zeichnen auf das Bild

    QEventLoop loop;
    int totalTiles = tileCount * tileCount;
    int loadedTiles = 0;

    // Alle Kacheln laden
    for (int dx = -offset; dx <= offset; ++dx) {
        for (int dy = -offset; dy <= offset; ++dy) {
            int tileX = centerX + dx;
            int tileY = centerY + dy;

            QString url = QString("https://tile.opentopomap.org/%1/%2/%3.png")
                              .arg(zoom).arg(tileX).arg(tileY); // Tile-URL
            QNetworkRequest request((QUrl(url)));
            QNetworkReply* reply = manager->get(request);

            connect(reply, &QNetworkReply::finished, this, [=, &loadedTiles, &loop, &painter]() mutable {
                QPixmap tile;
                tile.loadFromData(reply->readAll()); // Tile aus Antwort laden
                reply->deleteLater();

                int px = (dx + offset) * tileSize;
                int py = (dy + offset) * tileSize;

                if (!tile.isNull()) {
                    painter.drawPixmap(px, py, tile); // Zeichnen, wenn geladen
                } else {
                    painter.fillRect(px, py, tileSize, tileSize, Qt::lightGray); // Fehler: graue Fläche
                }

                if (++loadedTiles == totalTiles) loop.quit(); // Warten bis alle Tiles fertig
            });
        }
    }

    loop.exec(); // Blockiert bis alle Tiles da sind
    painter.end();

    originalMapPixmap = mapPixmap; // Zwischenspeichern für späteren Zoom
    scaleFactor = zoomSlider ? zoomSlider->value() / 100.0 : 1.0;

    if (!scene) {
        scene = new KartenSzene(view); // Neue Szene, wenn noch keine existiert
        view->setScene(scene);
        QObject::connect(scene, &KartenSzene::poiHinzugefuegt, scene, [poiCallback](POI* poi){
            if (poiCallback) poiCallback(poi); // Callback bei neuen POIs
        });
    } else {
        scene->clear(); // Vorhandene Szene leeren
        pixmapItem = nullptr;
    }

    if (!pixmapItem) {
        pixmapItem = scene->addPixmap(originalMapPixmap); // Karte anzeigen
    } else {
        pixmapItem->setPixmap(originalMapPixmap);
    }

    pixmapItem->setPos(0, 0);
    scene->setSceneRect(pixmapItem->boundingRect());
    pixmapItem->setScale(1.0);

    view->resetTransform();
    view->scale(scaleFactor, scaleFactor);
    view->centerOn(pixmapItem);

    scene->setPixmapItem(pixmapItem);
    scene->setUmrechnungsParameter(centerX, centerY, offset, zoom, scaleFactor);

    zeichnePOIs(scene, pois, centerX, centerY, tileSize, offset, zoom, scaleFactor);
    if (plan)
        zeichneFlugVerbindungen(scene, plan, pois, centerX, centerY, tileSize, offset, zoom, scaleFactor);

    view->resetTransform();
    view->scale(scaleFactor, scaleFactor);
    view->centerOn(pixmapItem);
    scene->setUmrechnungsParameter(centerX, centerY, offset, zoom, scaleFactor);
}


QPointF DragonMap::gpsZuSzenePosition(double lat, double lon, int tileSize, int centerX, int centerY, int offset, int zoom, qreal scaleFactor)
{
    // Berechne die Gesamtanzahl der Tiles auf der Weltkarte bei diesem Zoom-Level
    double n = std::pow(2.0, zoom);

    // Längengrad (lon) in Tile-X umrechnen (Web-Mercator)
    double x = (lon + 180.0) / 360.0 * n;

    // Breitengrad (lat) in Tile-Y umrechnen, inklusive Mercator-Projektion
    double latRad = qDegreesToRadians(lat); // Umrechnung in Bogenmaß
    double y = (1.0 - std::log(std::tan(latRad) + 1.0 / std::cos(latRad)) / M_PI) / 2.0 * n;

    // Berechne Pixel-Position relativ zur sichtbaren Kartensektion (zentriert um centerX/centerY)
    double xPix = (x - (centerX - offset)) * tileSize;
    double yPix = (y - (centerY - offset)) * tileSize;

    // Rückgabe als Punkt im Szenenkoordinatensystem
    return QPointF(xPix, yPix);
}

QGraphicsView *DragonMap::getView() const
{
    return view;
}



void DragonMap::zeichnePOIs(QGraphicsScene* scene, const std::map<std::string, POI*>& pois,
                            int centerX, int centerY, int tileSize, int offset, int zoom, qreal scaleFactor)
{
    for (const auto& [key, poi] : pois)
    {
        double lat = poi->getLatitude();
        double lon = poi->getLongitude();

        // zentrale Umrechnung der GPS-Koordinaten in Szenenposition
        QPointF poiPos = gpsZuSzenePosition(lat, lon, tileSize, centerX, centerY, offset, zoom, scaleFactor);

        // Icon-Pfad abhängig vom POI-Typ über POI-Methode bestimmen
        QString iconPath = poi->getIconPfad();

        // Icon vorbereiten (Größe hängt vom Zoom ab)
        QPixmap icon(iconPath);
        int baseSize = 35;
        int iconSize = baseSize * std::pow(scaleFactor, 0.5);  // Anpassung an Zoomfaktor
        QPixmap scaledIcon = icon.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Icon als Bild-Item in Szene einfügen
        QGraphicsPixmapItem* iconItem = new QGraphicsPixmapItem(scaledIcon);
        iconItem->setPos(poiPos + QPointF(-iconSize / 2, -iconSize / 2));  // zentrieren
        iconItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);      // Icon bleibt gleich groß beim Zoom
        scene->addItem(iconItem);

        // Textlabel mit POI-Namen hinzufügen
        QGraphicsTextItem* label = new QGraphicsTextItem(QString::fromStdString(poi->getName()));
        label->setDefaultTextColor(Qt::black);
        QFont font("Arial", 14 * std::pow(scaleFactor, 0.5));
        label->setFont(font);

        // Text etwas unterhalb des Icons platzieren
        qreal offsetX = -10 / std::sqrt(scaleFactor) * 0.2;
        qreal offsetY =  10 / std::sqrt(scaleFactor) * 0.2;
        label->setPos(poiPos + QPointF(offsetX, offsetY));
        label->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        scene->addItem(label);
    }
}


void DragonMap::zeichneFlugVerbindungen(QGraphicsScene* scene, Reiseplan* plan,
                                        const std::map<std::string, POI*>& pois,
                                        int centerX, int centerY, int tileSize, int offset, int zoom, qreal scaleFactor)
{
    QPointF lastPos;
    bool letzteVerbindungWarFlug = false;  // ***** merkt, ob vorher ein Flug war *****

    for (auto* abschnitt : plan->getReiseabschnitte()) {
        std::string ziel;

        // Zielname aus dem Abschnitt extrahieren (und cast speichern)
        auto* flug = dynamic_cast<Drachenflug*>(abschnitt);
        auto* lager = dynamic_cast<Nachtlager*>(abschnitt);

        // Zielname aus dem Abschnitt extrahieren
        if (flug) {
            ziel = flug->getZiel();
        } else if (lager) {
            ziel = lager->getLagerOrt();
        } else {
            continue;  // unbekannter Reisetyp
        }

        auto it = pois.find(ziel);
        if (it == pois.end()) {
            qWarning() << "Ziel nicht gefunden im POI-Set:" << QString::fromStdString(ziel);
            continue;
        }

        POI* poi = it->second;
        double lat = poi->getLatitude();
        double lon = poi->getLongitude();

        // zentrale Umrechnung
        QPointF poiPos = gpsZuSzenePosition(lat, lon, tileSize, centerX, centerY, offset, zoom, scaleFactor);


        // nur Linie zum letzten Punkt bei Flugverbindungen zeichnen
        if (flug!=nullptr) {
            QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(lastPos, poiPos));
            QPen pen(Qt::red, 4);
            line->setPen(pen);
            scene->addItem(line);
        }
        else {
            // ***** Ausgabe bei Verbindungsunterbrechung *****
            if (letzteVerbindungWarFlug) {

                // ***** Nur beim ersten Abbruch warnen *****
                qDebug() << "Achtung: Reiseverbindung unterbrochen nach"
                         << QString::fromStdString(ziel);
            }
            letzteVerbindungWarFlug = true;   // Flag setzen
        }
        lastPos = poiPos;  // Verbindung fortsetzen
    }
}


void DragonMap::aktualisiereZoom()
{
    if (!view || !view->scene())
        return;

    // Transformierung zurücksetzen und neuen Zoom anwenden
    view->resetTransform();
    view->scale(scaleFactor, scaleFactor);  // scaleFactor wird vorher gesetzt!

    // Ansicht zentrieren
    QRectF sceneRect(0, 0, tileCount * tileSize, tileCount * tileSize);
    view->scene()->setSceneRect(sceneRect);
    //view->centerOn(sceneRect.center());

    emit zoomUpdated(static_cast<int>(scaleFactor * 100));
}


int DragonMap::berechneMinZoom() const {
    if (!view || !scene)
        return 100;  // Fallback

    QSizeF viewSize = view->viewport()->size();
    QRectF sceneRect = scene->sceneRect();

    if (sceneRect.width() <= 0 || sceneRect.height() <= 0)
        return 100;  // Fallback

    // Zoomfaktor berechnen: Verhältnis View zu Scene
    qreal faktorX = viewSize.width() / sceneRect.width();
    qreal faktorY = viewSize.height() / sceneRect.height();
    qreal minFaktor = std::min(faktorX, faktorY);

    // Umwandeln in Prozentwert für den Slider (z. B. 0.7 → 70)
    return static_cast<int>(std::round(minFaktor * 100));
}


// ----- getter -----
int DragonMap::getTileCount() const { return tileCount; }
int DragonMap::getZoom() const { return zoom; }
double DragonMap::getGPSY() const { return GPSY; }
double DragonMap::getGPSX() const { return GPSX; }
qreal DragonMap::getScaleFactor() const { return scaleFactor; }

// ----- setter -----
void DragonMap::setTileCount(int newTileCount) { tileCount = newTileCount; }
void DragonMap::setZoom(int newZoom) { zoom = newZoom; }
void DragonMap::setGPSY(double newGPSY) { GPSY = newGPSY; }
void DragonMap::setGPSX(double newGPSX) { GPSX = newGPSX; }
void DragonMap::setScaleFactor(qreal newScaleFactor) { scaleFactor = newScaleFactor; }
