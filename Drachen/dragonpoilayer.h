#ifndef DRAGONPOILAYER_H
#define DRAGONPOILAYER_H

#include <QString>
#include <QInputDialog>
#include <map>
#include "reiseplan.h"
#include "poi.h"
#include "filmstudio.h"

class DragonPOILayer {
public:
    DragonPOILayer(Filmstudio* studio);

    std::map<std::string, POI*> getPOIsFuerReiseplan(Reiseplan* plan);
    POI* findePOIByName(const std::string& name); // ohne pois-Parameter

    QString wähleZielPoi(QWidget* parent = nullptr);
    std::pair<QString, QString> wähleNachtlagerOrtUndTyp(QWidget* parent = nullptr);
    void neuenPoiEintragen(POI* neuerPoi);

    QString zeigePoiAuswahlDialog(QWidget* parent, const QString& titel, const QString& labelText,
                                  const QStringList& optionen, bool allowCustom = false);
    POI* findePOIAusReiseabschnitt(Drachenreise* abschnitt);

private:
    Filmstudio* studio;
};

#endif // DRAGONPOILAYER_H

