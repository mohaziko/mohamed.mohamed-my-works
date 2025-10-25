#ifndef DRAGONMAP_H
#define DRAGONMAP_H

#include <QObject>
#include <QGraphicsView>
#include <QSlider>
#include <map>
#include <QNetworkAccessManager>
#include <functional>
#include "kartenszene.h"
#include "POI.h"
#include "reiseplan.h"

class DragonMap : public QObject
{
    Q_OBJECT
public:
    explicit DragonMap(QGraphicsView* view, QSlider* zoomSlider, QObject* parent = nullptr);

    // Karten-Methoden
    void landKarteAnzeigen(double lat, double lon, int zoom, int tileCount,
                           const std::map<std::string, POI*>& pois, Reiseplan* plan,
                           std::function<void(POI*)> poiCallback);

    static void latLonToTile(double lat, double lon, int zoom, int &tileX, int &tileY);
    std::pair<double, double> berechneKartenzentrum(const std::map<std::string, POI*>& pois, double fallbackLat, double fallbackLon);

    void zeichneFlugVerbindungen(QGraphicsScene* scene, Reiseplan* plan,
                                 const std::map<std::string, POI*>& pois,
                                 int centerX, int centerY, int tileSize, int offset, int zoom, qreal scaleFactor);

    void aktualisiereZoom();
    int berechneMinZoom() const;

    int getTileCount() const;
    int getZoom() const;
    double getGPSX() const;
    double getGPSY() const;
    qreal getScaleFactor() const;

    // Setter
    void setTileCount(int newTileCount);
    void setZoom(int newZoom);
    void setGPSX(double newGPSX);
    void setGPSY(double newGPSY);
    void setScaleFactor(qreal newScaleFactor);

    QGraphicsView *getView() const;

signals:
    void zoomUpdated(int zoomPercentage);  // Signal für GUI-Aktualisierung

private:
    void zeichnePOIs(QGraphicsScene* scene, const std::map<std::string, POI*>& pois,
                     int centerX, int centerY, int tileSize, int offset, int zoom, qreal scaleFactor);

    QPointF gpsZuSzenePosition(double lat, double lon, int tileSize, int centerX, int centerY,
                               int offset, int zoom, qreal scaleFactor);

    QGraphicsView* view;
    QSlider* zoomSlider;
    int tileCount = 9;
    int tileSize = 256;
    int zoom = 12;
    double GPSX = -45.493545;  // Latitude
    double GPSY = 167.6570732;  // Longitude
    qreal scaleFactor = 1.0;

    QPointF lastPos;
    QPixmap originalMapPixmap;  // das unskalierte Original
    QGraphicsPixmapItem* pixmapItem = nullptr;  // Zeiger auf aktuelles Kartenbild
    KartenSzene* scene = nullptr;    // Zeiger auf aktuelle Kartenbild

    std::map<std::string, POI*> letztePois;
    Reiseplan* letzterPlan = nullptr;
    std::function<void(POI*)> letzterPoiCallback = nullptr;

    QNetworkAccessManager* manager = nullptr;
    std::function<void(POI*)> poiCallback; // <== Callback speichern
};

#endif // DRAGONMAP_H
