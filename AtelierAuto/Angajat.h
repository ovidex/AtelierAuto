//
// Created by Admin on 20-Mar-21.
//

#ifndef ATELIERAUTO_ANGAJAT_H
#define ATELIERAUTO_ANGAJAT_H
#include <string>
#include <vector>
#include <iostream>


struct data{
    int zi,luna,an;
};
struct coada_angajat{
    int standard;
    int camion,autobuz;
};
struct car_time{
    int time;
    std::string type;
};
struct extra{
    std::vector<car_time> camion;
    std::vector<car_time> autobuz;
    std::vector<car_time> standard;
};
class Angajat {
protected:
    int ID;
    std::string Nume;
    std::string Prenume;
    float coeficient;
    data nastere;
    data angajare;
    coada_angajat working;
    std::vector<car_time>  waiting;
    extra  extra_waiting;
    static int timp_lucru_random()
    {int v=rand()%10+1;
        return v;
    }
public:
    static int next_id;
    Angajat(std::string Nume,std::string Prenume,data nastere,data angajare) {
        working.standard=0;
        working.camion=0;
        working.autobuz=0;
        this->setId(next_id);
        next_id++;
        this->setNume(Nume);
        this->setPrenume(Prenume);
        this->setNastere(nastere);
        this->setAngajare(angajare);
    }
    bool check_available(std::string car_type){
        if(car_type=="standard"&& this->working.standard<3){
            this->working.standard++;
            int t=timp_lucru_random();
            this->waiting.push_back((car_time){t,"standard"});
            return true;
        }
        else if(car_type=="autobuz"&& this->working.autobuz==0){
            this->working.autobuz++;
            int t=timp_lucru_random();

            this->waiting.push_back((car_time){t,"autobuz"});
            return true;
        }
        else if(car_type=="camion"&& this->working.camion==0){
            this->working.camion++;
            int t=timp_lucru_random();
            this->waiting.push_back((car_time){t,"camion"});
            return true;
        }
        this->wait_here(car_type);
        return false;
    }
    bool isBusy(std::string car_type){
        if(car_type=="standard"&& this->working.standard==3){
            return true;
        }
        else if(car_type=="autobuz"&& this->working.autobuz==1){
            return true;
        }
        else if(car_type=="camion"&& this->working.camion==1){
            return true;
        }
        return false;
    }
    void wait_here(std::string car_type){
        if(car_type=="standard"){
            extra_waiting.standard.push_back((car_time){timp_lucru_random(),car_type});
        }
        else if(car_type=="autobuz"){
            extra_waiting.autobuz.push_back((car_time){timp_lucru_random(),car_type});
        }
        else if(car_type=="camion"){
            extra_waiting.camion.push_back((car_time){timp_lucru_random(),car_type});
        }
    }
    void afisare_coada(){
        for(auto w:waiting)
        {std::cout<<w.type<<":"<<w.time<<" minutes- ";
        }
        for(auto w:extra_waiting.standard){
            std::cout<<w.time<<" ";
        }
        for(auto w:extra_waiting.autobuz){
            std::cout<<w.time<<" ";
        }
        for(auto w:extra_waiting.camion){
            std::cout<<w.time<<" ";
        }

    }
    void pass_time(){
        if(waiting.size()>0) {
            waiting[0].time--;
            if (waiting[0].time <= 0) {
                if(waiting[0].type=="standard"){
                    working.standard--;
                    if(extra_waiting.standard.size()>0){
                        waiting.push_back(extra_waiting.standard.front());
                        extra_waiting.standard.erase( extra_waiting.standard.begin());
                    }
                }
                else if(waiting[0].type=="autobuz"){
                    working.autobuz--;
                    if(extra_waiting.autobuz.size()>0){
                        waiting.push_back(extra_waiting.autobuz.front());
                        extra_waiting.autobuz.erase(extra_waiting.autobuz.begin());

                    }
                }
                else if(waiting[0].type=="camion"){
                    working.camion--;
                    if(extra_waiting.camion.size()>0){
                        waiting.push_back(extra_waiting.camion.front());
                        extra_waiting.camion.erase(extra_waiting.camion.begin());

                    }
                }
                waiting.erase(waiting.begin());
            }
        }
    }

    int waiting_time(){
        int t=0;
        for(auto car:waiting){
            t+=car.time;
        }
        return t;
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
