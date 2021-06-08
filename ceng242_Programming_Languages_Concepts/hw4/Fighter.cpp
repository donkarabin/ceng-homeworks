#include"Fighter.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Fighter::Fighter(uint id,int x,int y, Team team) : Player(id,x,y,team){
   this->HP=400;
}

int Fighter::getAttackDamage() const{
    return 100;
}

int Fighter::getHealPower() const{
    return 0;
}

int Fighter::getMaxHP() const{
    return this->HP;
}

std::vector<Goal> Fighter::getGoalPriorityList(){
   std::vector <Goal> list;
   list.push_back(ATTACK);
   list.push_back(TO_ENEMY);
   list.push_back(CHEST);
   return list;
   
}

const std::string Fighter::getClassAbbreviation() const{
   if(team==BARBARIANS){
      return "FI";
   }

   else{
      return "fi";
   
   }
}

std::vector<Coordinate> Fighter::getAttackableCoordinates(){
   std::vector<Coordinate> vec;
   int x=coordinate.x;
   int y=coordinate.y;
   Coordinate pos(x,y); 

   pos.x=x-1;              //left
   pos.y=y;
   vec.push_back(pos);
   
   pos.x=x+1;              //right
   pos.y=y;
   vec.push_back(pos);
   
   pos.x=x;
   pos.y=y-1;              //up
   vec.push_back(pos);

   pos.y=y+1;              //down
   vec.push_back(pos);
   return vec;
}

std::vector<Coordinate> Fighter::getMoveableCoordinates(){
   std::vector<Coordinate> vec;
   int x=coordinate.x;
   int y=coordinate.y;
   Coordinate pos(x,y); 

   pos.x=x-1;              //left
   pos.y=y;
   vec.push_back(pos);
   
   pos.x=x+1;              //right
   pos.y=y;
   vec.push_back(pos);
   
   pos.x=x;
   pos.y=y-1;              //up
   vec.push_back(pos);

   pos.y=y+1;              //down
   vec.push_back(pos);
   return vec;
}
std::vector<Coordinate> Fighter::getHealableCoordinates(){
   std::vector<Coordinate> vec;
   
   return vec;
}