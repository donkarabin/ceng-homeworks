#include"Archer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/


Archer::Archer(uint id,int x,int y, Team team) : Player(id,x,y,team){
   this->HP=200;
}

int Archer::getAttackDamage() const{
    return 50;
}

int Archer::getHealPower() const{
    return 0;
}

int Archer::getMaxHP() const{
    return this->HP;
}

std::vector<Goal> Archer::getGoalPriorityList(){
   std::vector <Goal> list;
   list.push_back(ATTACK);
   return list;
   
}

const std::string Archer::getClassAbbreviation() const{
   if(team==BARBARIANS){
      return "AR";
   }

   else{
      return "ar";
   
   }
}

std::vector<Coordinate> Archer::getAttackableCoordinates(){
   std::vector<Coordinate> vec;
   int x=coordinate.x;
   int y=coordinate.y;
   Coordinate pos(x,y-1);  //up
   vec.push_back(pos);  
   pos.y=y-2;
   vec.push_back(pos);

   pos.y=y+1;              //down
   vec.push_back(pos);
   pos.y=y+2;
   vec.push_back(pos);

   pos.x=x-1;              //left
   pos.y=y;
   vec.push_back(pos);
   pos.x=x-2;
   vec.push_back(pos);

   pos.x=x+1;              //right
   pos.y=y;
   vec.push_back(pos);
   pos.x=x+2;
   vec.push_back(pos);

   return vec;

}

std::vector<Coordinate> Archer::getMoveableCoordinates(){
   std::vector<Coordinate> vec;
   
   return vec;
}
std::vector<Coordinate> Archer::getHealableCoordinates(){
   std::vector<Coordinate> vec;
   
   return vec;
}

