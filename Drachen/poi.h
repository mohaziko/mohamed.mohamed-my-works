#ifndef POI_H
#define POI_H

#include "qcontainerfwd.h"
#include <string>
#include "json.hpp"

using json = nlohmann::json;
class POI
{
public:
    POI(const std::string& name, const std::string& typ, double latitude, double longitude);
    POI(const json& j);

    // Getter
    std::string getName() const;
    std::string getTyp() const;
    double getLatitude() const;
    double getLongitude() const;

    // JSON-Konvertierung
    json to_JSON() const;

    // Icon-Pfad für GUI
    QString getIconPfad() const;

private:
    std::string name;
    std::string typ;
    double latitude;
    double longitude;
};

#endif // POI_H
