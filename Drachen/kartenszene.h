#ifndef KARTENSZENE_H
#define KARTENSZENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPointF>
#include <QMap>
#include "POI.h"
//#include "DragonPOILayer.h"

class KartenSzene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit KartenSzene(QObject* parent = nullptr);
    void setUmrechnungsParameter(int centerX, int centerY, int offset, int zoom, qreal scaleFactor);
    void setPixmapItem(QGraphicsPixmapItem* newPixmapItem);

signals:
    void poiHinzugefuegt(POI* neuerPoi);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int centerX;
    int centerY;
    int offset;
    int zoom;
    qreal scaleFactor;
    int tileSize;

    QGraphicsPixmapItem* pixmapItem;
    //    DragonPOILayer* dragonLayer; // Zeigt auf den POI-Layer, der für POI-Erstellung zuständig ist
};

#endif // KARTENSZENE_H
