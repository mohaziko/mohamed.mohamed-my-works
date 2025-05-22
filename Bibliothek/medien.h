#ifndef MEDIEN_H
#define MEDIEN_H

#include <string>
#include <iostream>

class Medien {
protected:
    int id;
    std::string autor;
    std::string titel;
    bool ausgeliehen;
    int kundenId;
    static int nextID;
public:
    Medien(const std::string& autor, const std::string& titel);
    virtual ~Medien() = default;
    int getID() const;
    std::string getAutor() const;
    std::string getTitel() const;
    bool istAusgeliehen() const;
    void ausleihen(int kundenId);
    void zurueckgeben();
    virtual void print() const = 0;
    virtual std::string typ() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Medien& medium);
    operator std::string() const;
    int getKundenId() const;

};

#endif
