#include "Race.h"
#include <stdio.h>
#include <iostream>
#include "Utilizer.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Race::Race(std::string name) :average_laptime(Utilizer::generateAverageLaptime())
{
    race_name=name;
    head=NULL;
}

Race::Race(const Race& rhs) :average_laptime(rhs.average_laptime)
{
    race_name=rhs.race_name;
    if(rhs.head==NULL){
        head=NULL;
    }
    else{
        Car *current=this->head;
        Car *current_rhs=rhs.head;
        head=new Car(*rhs.head);
        while(current_rhs->getNext()!=NULL){
            Car *tmp=new Car(*current_rhs->getNext());
            tmp->nalliyan(); // PROBLEM OLA BILER!!!
            current->addCar(tmp);

            current=current->getNext();
            current_rhs=current_rhs->getNext();
        }
        
    }
}

Race::~Race(){
   Car *current=this->head;
   if(current==NULL){
       return;
   } 
   else{
       while(current->getNext()!=NULL){
           Car *tmp=current;
           current=current->getNext();
           delete tmp;
           
       }
       delete current;
   }
}

std::string Race::getRaceName() const{
 return this->race_name;
}

string randomString()
{
	string s = "tepesii";
  
	s[0] = rand() % 26 + 65;
	s[1] = rand() % 26 + 65;
	s[2] = rand() % 26 + 65;
	s[3] = rand() % 26 + 65;
	s[4] = rand() % 26 + 65;
	s[5] = rand() % 26 + 65;
    s[6] = rand() % 26 + 65; 

	return s;
}



void Race::addCartoRace(){
    string s1=randomString();
    string s2=randomString();
    string s3=" ";
    string fullname=s1+s3;
    fullname=fullname+s2;

    Car *randcar=new Car(fullname);
    Car *current= this->head;
    if(head==NULL){
        this->head=randcar;
    }
    else {
        while(current->getNext()!=NULL){
            current=current->getNext();
        }
        current->addCar(randcar);
    }
    
}

void Race::addCartoRace(Car& car){
    Car *newcar = new Car(car);
    Car *current= this->head;

    if(head==NULL){
        this->head=newcar;
    }
    else {
        while(current->getNext()!=NULL){
            current=current->getNext();
        }
        current->addCar(newcar);
    }
    
}


int Race::getNumberOfCarsinRace(){
    int num=0;
    if(this->head==NULL){
        return 0;
    }
    else{
        
        Car *current=this->head;
        while(current!=NULL){
            num++;
            current=current->getNext();
        }
    }
    return num;
}

void Race::goBacktoLap(int lap){
    Car *current=this->head;
    while(current!=NULL){

        Laptime *lap_cur=current->getHead();
        Laptime *tmp=NULL;

        int lapsize=lap_cur->getlapsize();
        int pos=lapsize-lap;

        if (lap>lapsize){
            ;
        }
        else {
            for(int i=0;i<=pos;i++){
                lap_cur=lap_cur->getnext();
            }
            tmp=lap_cur;
            if(tmp->getnext()==NULL){
                ;
            }
            else {
                tmp=tmp->getnext();
                Laptime *nxt=NULL;
                while(tmp!=NULL){
                    nxt=tmp;
                    tmp=tmp->getnext();
                    delete nxt;
                }
                
            }
                // delete tmp;
        }

        current=current->getNext();
    }
    this->sorting();
}


void Race::operator++(){
    if(head==NULL){
        return;
    }
    else {
        Car *current=this->head;
        while(current!=NULL){
            
            current->Lap(average_laptime);
            current=current->getNext();
        }
    }
    this->sorting();
}


void Race::operator--(){
    if(head==NULL){
        return;
    }
    else{
        Car *current=this->head;
        while(current!=NULL){
            if(current==NULL){
                return;
            }
            else {
                Laptime *lap_cur=current->getHead();
                Laptime *tmp;
                while(lap_cur!=NULL){
                    tmp=lap_cur;
                    lap_cur=lap_cur->getnext();
                }
                tmp->delLast();

                
            }
            current=current->getNext();
        }
        
    }
    this->sorting();
}


Car Race::operator[](const int car_in_position){
    int size=(this->head)->getcarsize();
    
    Car *current=this->head;
    Car *tmp=NULL;
    if (car_in_position>size){
        Car zerocar=Car("DOES NOT EXISTS");
        return zerocar;
    }
    else {
        for (int i=0;i<=car_in_position ;i++){
            tmp=current;
            current=current->getNext();
        }
        return *tmp;
    }
}


Car Race::operator[](std::string driver_name){
    
    Car *current=this->head;

    while(current!=NULL){
        if(current->getDriverName()==driver_name){
            return *current;
        }
        current=current->getNext();
    }
    
    
}


Race& Race::operator=(const Race& rhs){
    //this->race_name=rhs.race_name;
    //this->average_laptime=rhs.average_laptime;

}

void Race::sorting(){
    int carsize=this->getNumberOfCarsinRace();
    int t;
    int arr_total[carsize];
    Car *arr_car[carsize];
    Car *tmp=NULL;

    Car *current=this->head;
   for(int i=0;i<carsize && current!=NULL ;i++)
   {
       int tot=(current->getTotalLap()).getlaptime();
       arr_total[i]=tot;
       arr_car[i]=current;
       current=current->getNext();
   }

     
    for (int k=0;k<carsize; ++k) 
    {
        for (int j= k+1; j<carsize; ++j)
        {
            if (arr_total[k] > arr_total[j]) 
                {
                    t = arr_total[k];
                    arr_total[k] = arr_total[j];
                    arr_total[j] = t;

                    tmp=arr_car[k];
                    arr_car[k]=arr_car[j];
                    arr_car[j]=tmp;


                }
            }
    }

this->head=arr_car[0];
arr_car[carsize-1]->addCar(NULL); // PROBLEM OLA BILER
for(int l=0; l<carsize-1; ++l){
    arr_car[l]->addCar(arr_car[l+1]);
    }
    
    
}


std::ostream& operator<<(std::ostream& os, const Race& race){
  
  Car *current=race.head;
  int carsize=race.head->getcarsize();
  int points [10]={25,18,15,12,10,8,6,4,2,1};
  int i=0;
  int pos=1;
  while(current!=NULL){
      if (carsize<10)
      {
          os<<pos;
      }
      else if(carsize<100 && carsize>=10 && pos>=10){
          os<<pos;
      }
      else if(carsize<100 && pos<10){
          os<<"0"<<pos;
      }
      else if(carsize<1000 && carsize>100 && pos<10 ){
          os<<"00"<<pos;
      }
      else if(carsize<1000 && carsize>100 && pos>=10 && pos<100){
          os<<"0"<<pos;
      }
      else if(carsize<1000 && carsize>=100 && pos>=100 && pos<1000){
          os<<pos;
      }
      pos++;
      os<<"--"<< *current;
      if(i<10){
         os<<"--"<<points[i];
         i++;
      }
      else{
          os<<"--"<<"0";
          i++;
      }
    


    if (pos<=10 && current->getDriverName()==race.getfastestcar().getDriverName()){
        os<<"--"<<"1";
    }
    os<<"\n";
    current=current->getNext();
  }
  return os;

}