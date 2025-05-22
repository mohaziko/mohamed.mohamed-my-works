#ifndef KUNDE_H
#define KUNDE_H


#include <string>
class Kunde
{
public:
    Kunde(const std::string& nachname);
    int getId() const;
    std::string getNachname() const;
private:
    int id;
    std::string nachname;
    static int nextID;
};

#endif // KUNDE_H
