#include "poi.h"
#include <QString>
POI::POI(const std::string& name, const std::string& typ, double latitude, double longitude)
    : name(name), typ(typ), latitude(latitude), longitude(longitude) {}

POI::POI(const json& j)
    : name(j.at("name").get<std::string>()),
    typ(j.at("typ").get<std::string>()),
    latitude(j.at("latitude").get<double>()),
    longitude(j.at("longitude").get<double>()) {}

std::string POI::getName() const {
    return name;
}

std::string POI::getTyp() const {
    return typ;
}

double POI::getLatitude() const {
    return latitude;
}

double POI::getLongitude() const {
    return longitude;
}

json POI::to_JSON() const {
    return json{
        {"name", name},
        {"typ", typ},
        {"latitude", latitude},
        {"longitude", longitude}
    };
}

QString POI::getIconPfad() const {
    QString typQt = QString::fromStdString(typ).toLower();

    if (typQt == "höhle")
        return ":/icons/hoehle.svg";
    else if (typQt == "baumkrone")
        return ":/icons/baumkrone.svg";
    else if (typQt == "bergplateau")
        return ":/icons/bergplateau.svg";
    else if (typQt == "draggonport")
        return ":/icons/draggonport.svg";
    else
        return ":/icons/poi.svg";  // Fallback
}
