//
// Created by Admin on 20-Mar-21.
//

#include "Masina.h"

int Masina::getId() const {
    return ID;
}

void Masina::setId(int id) {
    ID = id;
}

int Masina::getKm() const {
    return km;
}

void Masina::setKm(int km) {
    Masina::km = km;
}

int Masina::getAnFabricatie() const {
    return an_fabricatie;
}

void Masina::setAnFabricatie(int anFabricatie) {
    an_fabricatie = anFabricatie;
}

bool Masina::isDiesel() const {
    return diesel;
}

void Masina::setDiesel(bool diesel) {
    Masina::diesel = diesel;
}

Masina::Masina(int id, int km, int anFabricatie, bool diesel) : ID(id), km(km), an_fabricatie(anFabricatie),
                                                                diesel(diesel) {}

Masina::~Masina() {

}
