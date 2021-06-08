#include"Player.h"
/*#include"Archer.h"
#include"Tank.h"
#include"Priest.h"
#include"Fighter.h"
#include"Scout.h"
#include"Archer.cpp"
#include"Tank.cpp"
#include"Priest.cpp"
#include"Fighter.cpp"
#include"Scout.cpp"*/
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/


Player::Player(uint id,int x, int y, Team team) : coordinate(x,y), id(id) {
    this->team=team;
}

uint Player::getID() const{
    return id;
}


Team Player::getTeam() const{
    return team;
}

std::string Player::getBoardID(){
    string s;
    string z=to_string(getID());
    
    if(this->getID()<10){
        s="0"+z;
        return s;
    }
    else{
        return z;
    }


}

const Coordinate& Player::getCoord() const{
    return this->coordinate;
}

int Player::getHP() const{
    return HP;
}
bool Player::isDead() const{
    if (this->HP<=0){
        return true;
    }
    else
    {
        return false;
    }
    
}

bool Player::attack(Player *enemy){
    int at=this->getAttackDamage();
    
    enemy->HP=(enemy->HP)-at;
    std::cout<<"Player "<<this->getBoardID()<<" attacked Player "<<enemy->getBoardID()<<" ("<<at<<")"<<endl;

    return enemy->isDead();
}

void Player::heal(Player *ally){
    int he=this->getHealPower();
    
    ally->HP=(ally->HP)+he;
	if(ally->getHP() > ally->getMaxHP()){
		ally->HP=ally->getMaxHP();
	}
    std::cout<<"Player "<<this->getBoardID()<<" healed Player "<<ally->getBoardID()<<endl;
}

void Player::movePlayerToCoordinate(Coordinate c){
    int posx=coordinate.x;
    int posy=coordinate.y;

    int cx=c.x;
    int cy=c.y;

    coordinate.x=cx;
    coordinate.y=cy;

    cout<<"Player "<< this->getBoardID()<<" moved from ("<<posx<<"/"<<posy<<")"<<" to ("<<cx<<"/"<<cy<<")"<<endl;

}


/*int main()
{
    Player *archer = new Archer(0, 1, 2, BARBARIANS);
	Player *fighter = new Fighter(1, 2, 2, BARBARIANS);
	Player *scout = new Scout(2, 3, 2, BARBARIANS);
	Player *priest = new Priest(3, 4, 1, KNIGHTS);
	Player *tank = new Tank(4, 6, 3, KNIGHTS);

    std::cout << "Archer ID: " << archer->getID() << std::endl;
	std::cout << "Tank Board ID: " << tank->getBoardID() << std::endl;
	std::cout << "Scout position: " << scout->getCoord() << std::endl;
	std::cout << "Priest team: " << (priest->getTeam() == BARBARIANS ? "BARBARIANS" : "KNIGHTS") << std::endl;
	std::cout << "Fighter HP: " << fighter->getHP() << std::endl;
	std::cout << "Archer Dead? " << (archer->isDead() ? "YES" : "NO") << std::endl;

    std::cout << "Scout AD: " << scout->getAttackDamage() << std::endl;
	std::cout << "Archer AD: " << archer->getAttackDamage() << std::endl;
	std::cout << "Priest Heal: " << priest->getHealPower() << std::endl;
	std::cout << "Tank Max HP: " << tank->getMaxHP() << std::endl;
	std::cout << "Fighter Max HP: " << fighter->getMaxHP() << std::endl;

    	// Some interactions
	scout->attack(priest);
	priest->movePlayerToCoordinate(Coordinate(3, 4));
	archer->attack(scout);
	fighter->attack(tank);
	priest->heal(tank);
	archer->attack(priest);
	archer->attack(priest);
	tank->attack(fighter);
	scout->movePlayerToCoordinate(Coordinate(0, 0));

	std::vector<Coordinate> coor;
	coor = scout->getAttackableCoordinates();
	std::cout << "Scout attackable coordinates: {";
	for (auto& c : coor) {
		std::cout << c << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Archer Dead? " << (archer->isDead() ? "YES" : "NO") << std::endl;
	std::cout << "Priest HP: " << priest->getHP() << std::endl;
	archer->attack(priest);
	std::cout << "Priest Dead? " << (priest->isDead() ? "YES" : "NO") << std::endl;
	std::cout << "Priest Coordinate: " << priest->getCoord() << std::endl;

	delete archer;
	delete fighter;
	delete scout;
	delete priest;
	delete tank;

    return 0;
}*/