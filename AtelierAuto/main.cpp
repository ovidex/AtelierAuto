#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <ctime>
#include "Angajat.h"
#include "Masina.h"
int Angajat::next_id=0;


int age(data today,data birth)
{
    int pd,pm,py,bd,bm,by;
    pd=today.zi;
    pm=today.luna;
    py=today.an;
    bd=birth.zi;
    bm=birth.luna;
    by=birth.an;
    int d, m, y;
    int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    y = py - by;
    if (pm < bm)
    {
        y--;
        m = 12 - (bm - pm);
    }
    else
    {m = pm - bm;}
    if (pd < bd)
    {
        m--;
        d = md[pm - 1] - (bd - pd);
    }
    else
    {d = pd - bd;}
    return y;
}
bool isFull(std::vector<Angajat*> angajati,std::string type){
    bool flag=1;
    for(auto ang:angajati){
        if(!ang->isBusy(type))flag=0;
    }
    return flag;
}
int main() {

    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    data azi;
    azi.zi=now->tm_mday;
    azi.luna=now->tm_mon + 1;
    azi.an=now->tm_year + 1900;
//    std::vector<Masina*> extra_list;
    extra  extra_list_global;

    std::vector<Masina*> m;
//    m.push_back(new Standard(0,500000,2020,1,1));
//    m.push_back(new Camion(1,500000,2009,1,2));
//    m.push_back(new Autobuz(2,500000,2019,1,10));
//    std::cout<<m[0]->getAsigurare(1)<<" "<<m[1]->getAsigurare(1)<<" "<<m[2]->getAsigurare(1);
    std::vector<Angajat*> a;

    a.push_back(new Director("Lipianu","Ovidiu",azi,data{9,12,1990}));
    a.push_back(new Mecanic("Lipianu","Florin",azi,data{9,12,1990}));

    while (1){
//        std::cout<<isFull(a,"standard")<<"\n";
        for(auto ang:a){
            ang->pass_time();
            for(auto ex:extra_list_global.autobuz){
                if(ang->check_available(ex.type)){extra_list_global.autobuz.erase(extra_list_global.autobuz.begin());};
            }
            for(auto ex:extra_list_global.standard){
                if(ang->check_available(ex.type)){extra_list_global.standard.erase(extra_list_global.standard.begin());};
            }
            for(auto ex:extra_list_global.camion){
                if(ang->check_available(ex.type)){extra_list_global.camion.erase(extra_list_global.camion.begin());};
            }
            std::cout<<"waiting time for "<<ang->getPrenume()<<" "<<ang->waiting_time()<<" queue: ";
            ang->afisare_coada();
            std::cout<<"\n";
        }

        std::string command;
        std::cin>>command;

        if(command=="exit")break;
        if(command=="wait")continue;
        if(command=="adauga"){
            std::string nume,prenume;
            data day,bday;

            while(!(nume.size()>0&&nume.size()<30))
            {std::cout<<"introduceti numele(maxim 30 de caractere):";
                std::cin>>nume;}

            while(!(prenume.size()>0&&prenume.size()<30))
            {std::cout<<"introduceti prenumele(maxim 30 de caractere):";
                std:: cin>>prenume;}

            std::cout<<"introduceti data nasterii(zi luna an):\n";
            std::cin>>bday.zi>>bday.luna>>bday.an;
            while(age(azi,bday)<18)
            {std::cout<<"Angajatul trebuie să aibă peste 18 ani\n";
                std::cin>>bday.zi>>bday.luna>>bday.an;
            }

            std::cout<<"introduceti data angajarii(zi luna an):\n";
            std::cin>>day.zi>>day.luna>>day.an;
            while(age(azi,day)<0)
            {std::cout<<"Data angajării nu poate fi o dată din viitor.\n";
             std::cout<<"introduceti data angajarii(zi luna an):\n";
                std::cin>>day.zi>>day.luna>>day.an;
            }
            std::string job;
            std::cout<<"introduceti funtia(Director/Mecanic/Asistent):\n";
            std::cin>>job;
            int flag=1;
            while(flag) {
                if (job == "Director") {
                    flag=0;
                    a.push_back(new Director(nume, prenume, bday, day));
                } else if (job == "Mecanic") {
                    flag=0;
                    a.push_back(new Mecanic(nume, prenume, bday, day));
                } else if (job == "Asistent") {
                    a.push_back(new Asistent(nume, prenume, bday, day));
                    flag=0;
                }
            }
        }

        if(command=="afiseaza"){
            for(auto ang:a){
                std::cout<<ang->getPrenume()<<" "<<ang->getNume()<<"\n";
            }
        }
        if(command=="salariu"){
            int id;
            bool found=0;
            while(!found) {
                std::cout << "introducere id angajat:";
                std::cin >> id;
                for (auto ang:a) {
                    if (ang->getID() == id) {
                        found=1;
                        std::cout << 1000.0 * age(azi, ang->getAngajare()) * ang->getCoeficient() << "\n";
                    }
                }
                if(!found)std::cout<<"id invalid\n";
            }
        }
        if (command=="sterge"){
            int id;
            bool found=0;
            while(!found) {
                std::cout << "introducere id angajat:";
                std::cin >> id;
                int i=0;
                for (auto ang:a) {
                    if (ang->getID() == id) {
                        found=1;
                        a.erase(a.begin()+i);
                    }
                    i++;
                }
                if(!found)std::cout<<"id invalid\n";
            }
        }
        if(command=="edit"){
            int id;
            bool found=0;
            while(!found) {
                std::cout << "introducere id angajat:";
                std::cin >> id;
                for (auto ang:a) {
                    if (ang->getID() == id) {
                        found=1;
                        std::string camp;
                        std::cout<<"Introduce campul pe care doresti sa il modifici:\n";
                        std::cin>>camp;
                        if(camp=="nume"){
                            std::string nume;
                            std::cout<<"Nume nou:\n";
                            std::cin>>nume;
                            ang->setNume(nume);
                        }else if(camp=="prenume"){
                            std::string nume;
                            std::cout<<"Prenume nou:\n";
                            std::cin>>nume;
                            ang->setPrenume(nume);
                        }else {
                            //de adaugat pentru data de nastere si data de angajare si alte campuri extra
                        }
                    }
                }
                if(!found)std::cout<<"id invalid\n";
            }
        }
        if(command=="atelier"){
            if(a.size()>0) {
                int id_Car, km_Car, an_Car;
                bool diesel_Car;
                std::cout << "introduceti datele masinii:\n";
                std::cout << "introduceti id:\n";
                std::cin >> id_Car;
                std::cout << "introduceti kilometraj:\n";
                std::cin >> km_Car;
                std::cout << "introduceti anul de fabricatie:\n";
                std::cin >> an_Car;
                std::cout << "este diesel?(da/nu):\n";
                std::string msg;

                int flag=1;
                while (flag)
                {std::cin >> msg;
                    if (msg == "da"){
                        diesel_Car = true;
                        flag=0;}
                else if (msg == "nu"){
                         diesel_Car = false;
                         flag=0;}
                }
                std::cout << "Care este tipul masinii?(standard/autobuz/camion):\n";
                flag=1;
                while (flag) {
                    std::cin >> msg;
                    if (msg == "standard") {
                        flag=0;
                        bool transmisie;
                        std::cout << "Care este tipul de transmisie?(1 pentru manual/0 pentru automat):\n";
                        std::cin >> transmisie;
                        m.push_back(new Standard(id_Car, km_Car, an_Car, diesel_Car, transmisie));
                    } else if (msg == "autobuz") {
                        flag=0;
                        int locuri;
                        std::cout << "Care este numarul de locuri?:\n";
                        std::cin >> locuri;
                        m.push_back(new Autobuz(id_Car, km_Car, an_Car, diesel_Car, locuri));
                    } else if (msg == "camion") {
                        flag=0;
                        int tonaj;
                        std::cout << "Care este tonajul?:\n";
                        std::cin >> tonaj;
                        m.push_back(new Camion(id_Car, km_Car, an_Car, diesel_Car, tonaj));
                    }
                }
                std::cout<<"Polita dvs. de asigurare:"<<m[0]->getAsigurare()<<"\n";

                std::cout<<"Pentru a continua (solicita):";
                std::string message;
                do{
                std::cin>>message;}
                while (message!="solicita");

                if(message == "solicita") {
                    if(isFull(a,msg)){
                        std::string da_nu;
                        std::cout<<"Toti angajatii sunt ocupati. Doresti sa astepti?(da/nu)\n";
                        do{
                        std::cin>>da_nu;}
                        while (da_nu!="da"&&da_nu!="nu");
                        if(da_nu=="da"){
                            if(msg=="camion")extra_list_global.camion.push_back((car_time){rand()%10+1,msg});
                            else if(msg=="standard")extra_list_global.standard.push_back((car_time){rand()%10+1,msg});
                            else if(msg=="autobuz")extra_list_global.autobuz.push_back((car_time){rand()%10+1,msg});
                        }
                        else if(da_nu=="nu"){std::cout<<"La revedere!\n"; continue;}
                    }
                    else{
                        std::string mesaj;

                        do{std::cout<<"Doriti un angajat special/primul disponibil(special/primul):\n";
                        std::cin>>mesaj;}
                        while (mesaj!="primul"&&mesaj!="special");
                        if(mesaj=="primul"){
                            for(auto angj:a){
                                if(angj->check_available(msg)){
                                    break;}
                            }
                        }
                        else if(mesaj=="special"){
                            std::cout<<"Introduceti id angajat:";
                            int id_ang;
                            std::cin>>id_ang;
                            for(auto ang:a){
                                if(ang->getID()==id_ang){
                                    if(ang->isBusy(msg)){
                                        std::string msg_ang;

                                        do{std::cout<<"Angajatul este ocupat!\n"<<"(asteapta/pleaca/primul):\n";
                                        std::cin>>msg_ang;}
                                        while (msg_ang!="asteapta"&&msg_ang!="primul"&&msg_ang!="pleaca");
                                        if(msg_ang=="asteapta"){
                                            ang->wait_here(msg);
                                        }
                                        else if(msg_ang=="primul"){
                                                for(auto angj:a){
                                                    {if(angj->check_available(msg))
                                                        break;}
                                                }
                                        }
                                        else if(msg_ang=="pleaca"){std::cout<<"La revedere!\n"; continue;}

                                    }
                                    else{
                                        ang->check_available(msg);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else{
                std::cout<<"Atelierul este inchis!\n";
            }
        }
    }

    return 0;
}
