#include"Board.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Board::Board(uint _size, std::vector<Player*>* _players, Coordinate chest) : chest(chest.x,chest.y) {
    size=_size;
    players=_players;
}

Board::~Board(){

}

bool Board::isCoordinateInBoard(const Coordinate& c){
    int s=this->size;
    if(c.x<s && c.x>=0 && c.y<s && c.y>=0){
        return true;
    }
    else {
        return false;
    }
        
}

bool Board::isPlayerOnCoordinate(const Coordinate& c){
    int s=(*players).size();
    
    for(int i=0;i<s;i++){
       if((*players)[i]->getCoord().x==c.x && (*players)[i]->getCoord().y==c.y){
           return true;
        }
        
    }
    return false;
}

Player * Board::operator [](const Coordinate& c){
    int s=(*players).size();
    if(isPlayerOnCoordinate(c)==false){
        return NULL;
    }
    else{
        for(int i=0;i<s;i++){
            if((*players)[i]->getCoord().x==c.x && (*players)[i]->getCoord().y==c.y){
                return (*players)[i];
            }
        
        }
    }
}

Coordinate Board::getChestCoordinates(){
    return chest;
}


void Board::printBoardwithID(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            Coordinate c(j,i);
            if(c==this->getChestCoordinates()){
                std::cout<<"Ch";
            }
            else if(c==this->getChestCoordinates() && isPlayerOnCoordinate(c)){
                std::cout<<(this->operator[](c)->getBoardID());
            }
            else if(isPlayerOnCoordinate(c)){
                std::cout<<(this->operator[](c)->getBoardID());
            }
            else{
                std::cout<<"__";
            }
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }

}

void Board::printBoardwithClass(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            Coordinate c(j,i);
            if(c==this->getChestCoordinates()){
                std::cout<<"Ch";
            }
            else if(c==this->getChestCoordinates() && isPlayerOnCoordinate(c)){
                std::cout<<(this->operator[](c)->getClassAbbreviation());
            }
            else if(isPlayerOnCoordinate(c)){
                std::cout<<(this->operator[](c)->getClassAbbreviation());
            }
            else{
                std::cout<<"__";
            }
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }
}