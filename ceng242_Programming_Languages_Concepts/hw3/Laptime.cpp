#include "Laptime.h"
#include <stdio.h>
#include <iostream>

using namespace std;
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
//Laptime::Laptime(int ltime);

Laptime::Laptime(int ltime){
    laptime=ltime;
    next=NULL;
    chainsize=0;

}

Laptime::Laptime(const Laptime& rhs){
    laptime=rhs.laptime;
    chainsize=rhs.chainsize;
    next=rhs.next;
}

Laptime::~Laptime(){
  
 
    // Laptime *current=this->next;
    // Laptime *nxt=NULL;

    //     while(current!=NULL){
    //         nxt=current->getnext();
    //         delete (current);
    //         current=nxt;
    //     }
    // next=NULL;
    // current=NULL;

    
}

void Laptime::addLaptime(Laptime *next){
    this->next=next;
    chainsize+=1;

}

bool Laptime::operator<(const Laptime& rhs) const{
    if ((this->laptime)<rhs.laptime){
        return true;
    }
    else 
        return false;
}

bool Laptime::operator>(const Laptime& rhs) const{
    if ((this->laptime)>rhs.laptime){
        return true;
    }
    else 
        return false;    
}


Laptime& Laptime::operator+(const Laptime& rhs){
    laptime+=rhs.laptime;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Laptime& laptime){
  int total=laptime.laptime;
  int minutes = (total/60000);
  total=total-(minutes*60000);
  int seconds= (total/1000);
  total=total-(seconds*1000);
  int milliseconds= total;

  os<<minutes<<":";
  if(seconds<10 && seconds>=0){
      os<<"0"<<seconds<<".";
  }

  else {
    os<<seconds<<".";
  }

  if (milliseconds<=100 && milliseconds>10){
      os<<"0"<<milliseconds;
  }
  else if(milliseconds<10 && milliseconds>=0){
      os<<"00"<<milliseconds;
  }
  else {
      os<<milliseconds;
  }
  return os;
}


int Laptime::getchainsize(){
    return chainsize;
}

int Laptime::getlaptime() const{
    return laptime;
}

Laptime* Laptime::getnext(){
    return next;
}

int Laptime::getlapsize(){
    int size=0;
    Laptime *current=this;

    while(current!=NULL){
        size++;
        current=current->getnext();
    }
    return size;
}