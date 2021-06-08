#include"Tank.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Tank::Tank(uint id,int x,int y, Team team) : Player(id,x,y,team){

}

int Tank::getAttackDamage() const{
    return 25;
}

int Tank::getHealPower() const{
    return 0;
}

int Tank::getMaxHP() const{
    return 1000;
}

std::vector<Goal> Tank::getGoalPriorityList(){
   std::vector <Goal> list;
   list.push_back(TO_ENEMY);
   list.push_back(ATTACK);
   list.push_back(CHEST);
   return list;
   
}

const std::string Tank::getClassAbbreviation() const{
   if(team==BARBARIANS){
      return "TA";
   }

   else{
      return "ta";
   
   }
}

std::vector<Coordinate> Tank::getAttackableCoordinates(){
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

std::vector<Coordinate> Tank::getMoveableCoordinates(){
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
std::vector<Coordinate> Tank::getHealableCoordinates(){

    std::vector<Coordinate> vec;
    return vec;

   
}

