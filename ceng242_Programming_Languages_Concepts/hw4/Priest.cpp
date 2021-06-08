#include"Priest.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Priest::Priest(uint id,int x,int y, Team team) : Player(id,x,y,team){
   this->HP=150;
}

int Priest::getAttackDamage() const{
    return 0;
}

int Priest::getHealPower() const{
    return 50;
}

int Priest::getMaxHP() const{
    return this->HP;
}

std::vector<Goal> Priest::getGoalPriorityList(){
   std::vector <Goal> list;
   list.push_back(HEAL);
   list.push_back(TO_ALLY);
   list.push_back(CHEST);
   return list;
   
}

const std::string Priest::getClassAbbreviation() const{
   if(team==BARBARIANS){
      return "PR";
   }

   else{
      return "pr";
   
   }
}

std::vector<Coordinate> Priest::getAttackableCoordinates(){
    std::vector<Coordinate> vec;
    return vec;
}

std::vector<Coordinate> Priest::getMoveableCoordinates(){
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

   pos.x=x-1;              //upleft
   pos.y=y-1;
   vec.push_back(pos);

   pos.x=x+1;              //upright
   pos.y=y-1;
   vec.push_back(pos);

   pos.x=x-1;              //downleft
   pos.y=y+1;
   vec.push_back(pos);

   pos.x=x+1;              //downright
   pos.y=y+1;
   vec.push_back(pos); 
   
   pos.x=x;                //up
   pos.y=y-1;
   vec.push_back(pos);

   pos.y=y+1;              //down
   vec.push_back(pos);






   return vec;
}
std::vector<Coordinate> Priest::getHealableCoordinates(){
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

   pos.x=x-1;              //upleft
   pos.y=y-1;
   vec.push_back(pos);

   pos.x=x+1;              //upright
   pos.y=y-1;
   vec.push_back(pos);

   pos.x=x-1;              //downleft
   pos.y=y+1;
   vec.push_back(pos);

   pos.x=x+1;              //downright
   pos.y=y+1;
   vec.push_back(pos); 
   
   pos.x=x;                //up
   pos.y=y-1;
   vec.push_back(pos);

   pos.y=y+1;              //down
   vec.push_back(pos);
   
   return vec;
}