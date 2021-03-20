//
// Created by Admin on 20-Mar-21.
//

#ifndef ATELIERAUTO_MASINA_H
#define ATELIERAUTO_MASINA_H

#include <ctime>
#include "Angajat.h"

class Masina {
private:
    int ID;
    int km;
    int an_fabricatie;
    bool diesel;
public:
    Masina(int id, int km, int anFabricatie, bool diesel);

    virtual ~Masina();

public:

    int vechime(int an_fabricatie){
        std::time_t t = std::time(0);   // get time now
        std::tm* now = std::localtime(&t);
        data azi;
        azi.an=now->tm_year + 1900;
        return azi.an-an_fabricatie+1;
    }
    int getId() const;

    void setId(int id);

    int getKm() const;

    void setKm(int km);

    int getAnFabricatie() const;

    void setAnFabricatie(int anFabricatie);

    bool isDiesel() const;

    void setDiesel(bool diesel);

public:
    virtual float getAsigurare(bool discount=0){return 0;}

};

class Standard: public Masina{
private:
    bool transmisie;
public:
    bool isTransmisie() const {
        return transmisie;
    }

    void setTransmisie(bool transmisie) {
        Standard::transmisie = transmisie;
    }

public:
    float getAsigurare(bool discount=0) override{
    float polita= vechime(this->getAnFabricatie())*100;
    if (this->isDiesel())polita+=500;
    if (this->getKm()>200000)polita+=500;
    if(discount)return 0.95*polita;
    return polita;
    }

    Standard(int id, int km, int anFabricatie, bool diesel, bool transmisie) : Masina(id, km, anFabricatie, diesel),
                                                                               transmisie(transmisie) {}
};

class Autobuz: public Masina{
private:
    int locuri;
public:
    int getLocuri() const {
        return locuri;
    }

    void setLocuri(int locuri) {
        Autobuz::locuri = locuri;
    }

public:
    float getAsigurare(bool discount=0) override{
        float polita= vechime(this->getAnFabricatie())*200;
        if (this->isDiesel())polita+=1000;
        if (this->getKm()>200000)polita+=1000;
        else if (this->getKm()>100000)polita+=500;
        if(discount)return 0.9*polita;
        return polita;
    }

    Autobuz(int id, int km, int anFabricatie, bool diesel, int locuri) : Masina(id, km, anFabricatie, diesel),
                                                                         locuri(locuri) {}
};

class Camion: public Masina{
private:
    int tonaj;
public:
    int getTonaj() const {
        return tonaj;
    }

    void setTonaj(int tonaj) {
        Camion::tonaj = tonaj;
    }

public:
    float getAsigurare(bool discount=0) override{
        float polita= vechime(this->getAnFabricatie())*300;
        if (this->getKm()>800000)polita+=700;
        if(discount)return 0.85*polita;
        return polita;
    }

    Camion(int id, int km, int anFabricatie, bool diesel, int tonaj) : Masina(id, km, anFabricatie, diesel),
                                                                       tonaj(tonaj) {}
};


#endif //ATELIERAUTO_MASINA_H
