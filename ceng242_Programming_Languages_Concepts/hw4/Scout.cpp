#include"Scout.h"
using namespace std;
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Scout::Scout(uint id,int x,int y, Team team) : Player(id,x,y,team){
   this->HP=125;
}

int Scout::getAttackDamage() const{
    return 25;
}

int Scout::getHealPower() const{
    return 0;
}

int Scout::getMaxHP() const{
    return this->HP;
}

std::vector<Goal> Scout::getGoalPriorityList(){
   std::vector <Goal> list;
   list.push_back(CHEST);
   list.push_back(TO_ALLY);
   list.push_back(ATTACK);
   return list;
   
}

const std::string Scout::getClassAbbreviation() const{
   if(team==BARBARIANS){
      return "SC";
   }

   else{
      return "sc";
   
   }
}

std::vector<Coordinate> Scout::getAttackableCoordinates(){
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

std::vector<Coordinate> Scout::getMoveableCoordinates(){
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

std::vector<Coordinate> Scout::getHealableCoordinates(){
    std::vector<Coordinate> vec;
    return vec; 
}