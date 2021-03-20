#include <iostream>
#include <vector>
#include <chrono>
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

int main() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    data azi;
    azi.zi=now->tm_mday;
    azi.luna=now->tm_mon + 1;
    azi.an=now->tm_year + 1900;

    std::vector<Masina*> m;
//    m.push_back(new Standard(0,500000,2020,1,1));
//    m.push_back(new Camion(1,500000,2009,1,2));
//    m.push_back(new Autobuz(2,500000,2019,1,10));
//    std::cout<<m[0]->getAsigurare(1)<<" "<<m[1]->getAsigurare(1)<<" "<<m[2]->getAsigurare(1);

    std::vector<Angajat*> a;
    a.push_back(new Director("Lipianu","Ovidiu",azi,data{9,12,1990}));
    a.push_back(new Mecanic("Lipianu","Florin",azi,data{9,12,1990}));
    a.push_back(new Asistent("Stan","Florin",azi,data{9,12,1990}));

//    while (1){
//        std::string command;
//        std::cin>>command;
//
//        if(command=="exit")break;
//
//        if(command=="adauga"){
//            std::string nume,prenume;
//            data day,bday;
//
//            while(!(nume.size()>0&&nume.size()<30))
//            {std::cout<<"introduceti numele(maxim 30 de caractere):";
//                std::cin>>nume;}
//
//            while(!(prenume.size()>0&&prenume.size()<30))
//            {std::cout<<"introduceti prenumele(maxim 30 de caractere):";
//                std:: cin>>prenume;}
//
//            std::cout<<"introduceti data nasterii(zi luna an):\n";
//            std::cin>>bday.zi>>bday.luna>>bday.an;
//            while(age(azi,bday)<18)
//            {std::cout<<"Angajatul trebuie să aibă peste 18 ani\n";
//                std::cin>>bday.zi>>bday.luna>>bday.an;
//            }
//
//            std::cout<<"introduceti data angajarii(zi luna an):\n";
//            std::cin>>day.zi>>day.luna>>day.an;
//            while(age(azi,day)<0)
//            {std::cout<<"Data angajării nu poate fi o dată din viitor.\n";
//             std::cout<<"introduceti data angajarii(zi luna an):\n";
//                std::cin>>day.zi>>day.luna>>day.an;
//            }
//            std::string job;
//            std::cout<<"introduceti funtia(Director/Mecanic/Asistent):\n";
//            std::cin>>job;
//            if(job=="Director"){
//                a.push_back(new Director(nume,prenume,bday,day));
//            }
//            else if (job=="Mecanic"){a.push_back(new Mecanic(nume,prenume,bday,day));
//                }
//            else if(job=="Asistent"){a.push_back(new Asistent(nume,prenume,bday,day));
//                }
//            else {
//
//            }
//        }
//
//        if(command=="afiseaza"){
//            for(auto ang:a){
//                std::cout<<ang->getPrenume()<<" "<<ang->getNume()<<"\n";
//            }
//        }
//        if(command=="salariu"){
//            int id;
//            bool found=0;
//            while(!found) {
//                std::cout << "introducere id angajat:";
//                std::cin >> id;
//                for (auto ang:a) {
//                    if (ang->getID() == id) {
//                        found=1;
//                        std::cout << 1000.0 * age(azi, ang->getAngajare()) * ang->getCoeficient() << "\n";
//                    }
//                }
//                if(!found)std::cout<<"id invalid\n";
//            }
//        }
//        if (command=="sterge"){
//            int id;
//            bool found=0;
//            while(!found) {
//                std::cout << "introducere id angajat:";
//                std::cin >> id;
//                int i=0;
//                for (auto ang:a) {
//                    if (ang->getID() == id) {
//                        found=1;
//                        a.erase(a.begin()+i);
//                    }
//                    i++;
//                }
//                if(!found)std::cout<<"id invalid\n";
//            }
//        }
//        if(command=="edit"){
//            int id;
//            bool found=0;
//            while(!found) {
//                std::cout << "introducere id angajat:";
//                std::cin >> id;
//                for (auto ang:a) {
//                    if (ang->getID() == id) {
//                        found=1;
//                        std::string camp;
//                        std::cout<<"Introduce campul pe care doresti sa il modifici:\n";
//                        std::cin>>camp;
//                        if(camp=="nume"){
//                            std::string nume;
//                            std::cout<<"Nume nou:\n";
//                            std::cin>>nume;
//                            ang->setNume(nume);
//                        }else if(camp=="prenume"){
//                            std::string nume;
//                            std::cout<<"Prenume nou:\n";
//                            std::cin>>nume;
//                            ang->setPrenume(nume);
//                        }else {
//                            //de adaugat pentru data de nastere si data de angajare
//                        }
//                    }
//                }
//                if(!found)std::cout<<"id invalid\n";
//            }
//        }
//    }

    return 0;
}
