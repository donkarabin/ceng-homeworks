#include <stdio.h>
#include <iostream>
#include "Car.h"
#include "Utilizer.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Car::Car(std::string name){
    driver_name=name;
    performance=Utilizer::generatePerformance();
    head=NULL;
    next=NULL;
}

Car::Car(const Car& rhs){
    driver_name=rhs.driver_name;
    performance=rhs.performance;
    next=rhs.next;

    if (rhs.head==NULL) {
         head = NULL;
     }

    else {
        head = new Laptime (*rhs.head); //BURDA PROBLEM OLA BILER!!!
        Laptime *current=head;
        Laptime *rhs_current=rhs.head;
        while(rhs_current->getnext()!=NULL){
            Laptime *t = new Laptime(*rhs_current->getnext());
            current->addLaptime (t);

            current = current->getnext ();
            rhs_current = rhs_current->getnext ();
        }
    }
    
}

Car::~Car(){
   Laptime *current=this->head;
   if(current==NULL){
       return;
   } 
   else{
       while(current!=NULL){
           Laptime *tmp=current;
           current=current->getnext();
           delete tmp;
           
       }
   delete current;
   }

}

std::string Car::getDriverName() const{
    return this->driver_name;
}

double Car::getPerformance() const{
    return this->performance;
}

void Car::addCar(Car *next){
    this->next=next;
}

bool Car::operator<(const Car& rhs) const{
    int total_this, total_rhs;
    Laptime *current=this->head;
    Laptime *rhs_current=rhs.head;
    while(current!=NULL){
        total_this+=(current->getlaptime());
        current=current->getnext();
    }

    while(rhs_current!=NULL){
        total_rhs+=(rhs_current->getlaptime());
        rhs_current=rhs_current->getnext();
    }

    if(total_this<total_rhs)
        return true;
    else 
        return false;
}


bool Car::operator>(const Car& rhs) const{
        int total_this, total_rhs;
    Laptime *current=this->head;
    Laptime *rhs_current=rhs.head;
    while(current!=NULL){
        total_this+=(current->getlaptime());
        current=current->getnext();
    }

    while(rhs_current!=NULL){
        total_rhs+=(rhs_current->getlaptime());
        rhs_current=rhs_current->getnext();
    }

    if(total_this>total_rhs)
        return true;
    else 
        return false;
}

Laptime Car::operator[](const int lap) const{
    int size=(this->head)->getlapsize();
    
    Laptime *current=this->head;
    Laptime *tmp=NULL;
    if (lap>size){
        Laptime zerolap=Laptime(0);
        return zerolap;
    }
    else {
        for (int i=0;i<=lap ;i++){
            tmp=current;
            current=current->getnext();
        }
        return *tmp;
    }
}

void Car::Lap(const Laptime& average_laptime){
    int variance=Utilizer::generateLaptimeVariance(this->getPerformance());
    int average;
    average=average_laptime.getlaptime();
    average+=variance;
    Laptime *newlap= new Laptime(average);
    if(this->head==NULL){
        this->head=newlap;
    }
    else{
        Laptime *current=this->head;
        while (current->getnext()!=NULL){
            current=current->getnext();
        }
        current->addLaptime(newlap);

    }
}

std::ostream& operator<<(std::ostream& os, const Car& car){
    string name=car.getDriverName();
    int pos= name.find(' ');
    pos++;
    
    for(int i=0;i<3;i++){
        char a=toupper(name[pos+i]);
        os<<a;
    }
    
    os<<"--";
    if(car.head==NULL){
        Laptime zerolap(0);
        os<<zerolap;
    }
    else{
        os<<car.getLatestLap()<<"--";
        os<<car.getFastestLap()<<"--";
        os<<car.getTotalLap();


    }
    return os;
   // os<<car.getLatestLap();
}


    Laptime Car::getLatestLap() const{
        Laptime *current=this->head;
        while(current->getnext()!=NULL){
            current=current->getnext();
        }

        return *current;
    }

    Laptime Car::getTotalLap() const{
        int total=0;
        Laptime *current=this->head;
        while(current->getnext()!=NULL){
            total+=current->getlaptime();
            current=current->getnext();
        }
        total+=current->getlaptime();
        Laptime tot(total);
        return tot;
    }

    Laptime Car::getFastestLap() const{
        //int maxint=2000000000;
        int val=head->getlaptime();
        int cur_time;
        Laptime *current = this->head;
        while(current!=NULL){
            cur_time = current->getlaptime();
            //cout << "sikdirdimehebbet" << endl;
            if(cur_time <= val){
                val=cur_time;
                //cout<<"siaut"<<endl;
            }
            else if(cur_time>val){
                //cout<<"get qaqa"<<endl;
                ;
            }
            //cout<<"burdadi"<<endl;
            current=current->getnext();
        }
        Laptime fas(val);
        return fas;
    }