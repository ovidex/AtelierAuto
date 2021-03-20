//
// Created by Admin on 20-Mar-21.
//

#ifndef ATELIERAUTO_ANGAJAT_H
#define ATELIERAUTO_ANGAJAT_H


#include <string>
struct data{
    int zi,luna,an;
};

class Angajat {
protected:
    int ID;
    std::string Nume;
    std::string Prenume;
    float coeficient;
    data nastere;
    data angajare;
public:
    static int next_id;

    Angajat(std::string Nume,std::string Prenume,data nastere,data angajare) {
        this->setId(next_id);
        next_id++;
        this->setNume(Nume);
        this->setPrenume(Prenume);
        this->setNastere(nastere);
        this->setAngajare(angajare);
    }

    Angajat(){

    }

    virtual ~Angajat() {

    }

    int getID(){
        return this->ID;
    }
    std::string getNume(){
        return this->Nume;
    }
    std::string getPrenume(){
        return this->Prenume;
    }

    int getId() const {
        return ID;
    }

    void setId(int id) {
        ID = id;
    }

    void setNume(const std::string &nume) {
        Nume = nume;
    }

    void setPrenume(const std::string &prenume) {
        Prenume = prenume;
    }

    virtual float getCoeficient() const {
        return coeficient;
    }
    const data &getNastere() const {
        return nastere;
    }

    void setNastere(const data &nastere) {
        this->nastere.an=nastere.an;
        this->nastere.luna=nastere.luna;
        this->nastere.zi=nastere.zi;
    }

    const data &getAngajare() const {
        return angajare;
    }

    void setAngajare(const data &angajare) {
        this->angajare.an=angajare.an;
        this->angajare.luna=angajare.luna;
        this->angajare.zi=angajare.zi;
    }

};

class Director: public Angajat{
    float coeficient=2;
public:

    float getCoeficient() const override {
        return this->coeficient;
    }

    Director(const std::string &nume, const std::string &prenume, const data &nastere, const data &angajare) : Angajat(
            nume, prenume, nastere, angajare) {}

};
class Mecanic: public Angajat{
    const float coeficient=1.5;
public:

    float getCoeficient() const override {
        return this->coeficient;
    }
    Mecanic(const std::string &nume, const std::string &prenume, const data &nastere, const data &angajare) : Angajat(
            nume, prenume, nastere, angajare) {}
};
class Asistent: public Angajat{
    const float coeficient=1;
public:

    float getCoeficient() const override {
        return this->coeficient;
    }
    Asistent(const std::string &nume, const std::string &prenume, const data &nastere, const data &angajare) : Angajat(
            nume, prenume, nastere, angajare) {}
};


#endif //ATELIERAUTO_ANGAJAT_H
