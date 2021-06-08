#include <stdio.h>
#include <iostream>
#include "Laptime.h"
#include "Car.h"
#include "Race.h"

using namespace std;

int main(){
    //  Laptime lap1=Laptime(70000);

     Laptime lap3=Laptime(55000);
     Laptime lap4=Laptime(85550);
     Laptime lap5=Laptime(99500);
     Laptime lap6=Laptime(122500);


    Car car1=Car("Lewis Hamilton");
    Car car2=Car("Fernando Alonso");
    car1.Lap(lap6);
    Car *pt=&car2;
    //cout<<car2.getDriverName()<<endl;
    // cout<<"Performance:"<<car2.getPerformance()<<endl;
    car2.Lap(lap3);
    car2.Lap(lap4);
    car2.Lap(lap5);

    //cout<<"Lapsize"<<car2.getHead()->getlapsize()<<endl;
    //cout<<"LAP5:"<<lap5<<endl;
    Car car3= Car(car2);
    //cout<<"COPY CAR"<<*car3<<endl;
    //delete car3;
    
    //car2.Lap(lap3);
    //cout<<"LAP3:"<<lap3<<endl;
    //car2.Lap(lap4);
    //cout<<"LAP4:"<<lap4<<endl;
    //cout<<car2<<endl;

    Race race1=Race("Monaco");
    Race race2=Race("Bahrain");
    race1.addCartoRace(car2);
    race1.addCartoRace(car1);
    race1.operator--();
    cout<<race1<<endl;
    //race1.addCartoRace(car2);
    // race1.goBacktoLap(2);

    //cout<<"BLYAT:"<<(car2.getHead())->getlapsize()<<endl;

    //cout<<lap2.getlaptime()<<" 1ci"<<endl;
    //cout<<lap2.getlap2()<<" 2ci"<<endl;
    // cout<<"LAPTIME: "<<lap6<<endl;

    //lap4.operator[](2);
}