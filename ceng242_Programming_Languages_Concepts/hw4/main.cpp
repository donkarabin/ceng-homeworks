#include"Player.h"
#include"Archer.h"
#include"Tank.h"
#include"Priest.h"
#include"Fighter.h"
#include"Scout.h"
#include"Board.h"
#include"Game.h"


int main(){

   /* Player *archer = new Archer(0, 1, 2, BARBARIANS);
	Player *fighter = new Fighter(1, 2, 2, BARBARIANS);
	Player *scout = new Scout(2, 3, 2, BARBARIANS);
	Player *priest = new Priest(3, 4, 1, KNIGHTS);
	Player *tank = new Tank(4, 6, 3, KNIGHTS);

	// Shared methods
	std::cout << "Archer ID: " << archer->getID() << std::endl;
	std::cout << "Tank Board ID: " << tank->getBoardID() << std::endl;
	std::cout << "Scout position: " << scout->getCoord() << std::endl;
	std::cout << "Priest team: " << (priest->getTeam() == BARBARIANS ? "BARBARIANS" : "KNIGHTS") << std::endl;
	std::cout << "Fighter HP: " << fighter->getHP() << std::endl;
	std::cout << "Archer Dead? " << (archer->isDead() ? "YES" : "NO") << std::endl;

	// Virtual methods
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
	delete tank;*/





	std::vector<Player*> players;
	Board board(6, &players, Coordinate(5, 0));
	std::cout << "Coordinate " << Coordinate(6, 2) << "in board? " << board.isCoordinateInBoard(Coordinate(6, 2)) << std::endl;
	std::cout << "Coordinate " << Coordinate(-2, 1) << "in board? " << board.isCoordinateInBoard(Coordinate(-2, 1)) << std::endl;
	std::cout << "Coordinate " << Coordinate(6, -2) << "in board? " << board.isCoordinateInBoard(Coordinate(6, -2)) << std::endl;
	std::cout << "Coordinate " << Coordinate(2, 3) << "in board? " << board.isCoordinateInBoard(Coordinate(2, 3)) << std::endl;

	Archer* archer = new Archer(0, 1, 4, BARBARIANS);
	Fighter* fighter = new Fighter(1, 1, 5, BARBARIANS);
	Scout* scout = new Scout(2, 2, 4, BARBARIANS);
	Priest *priest = new Priest(3, 4, 4, KNIGHTS);
	Tank *tank = new Tank(4, 5, 3, KNIGHTS);

	players.push_back(archer);
	players.push_back(fighter);
	players.push_back(scout);
	players.push_back(priest);
	players.push_back(tank);

	std::cout << "Player on coordinate " << Coordinate(5, 3) << "? " << board.isPlayerOnCoordinate(Coordinate(5, 3)) << std::endl;
	std::cout << "Player on coordinate " << Coordinate(3, 3) << "? " << board.isPlayerOnCoordinate(Coordinate(3, 3)) << std::endl;

	std::cout << "ID of player on coordinate " << Coordinate(4, 4) << " " << board[Coordinate(4, 4)]->getID() << std::endl;
	std::cout << "Printing with ID" << std::endl << std::endl;
	board.printBoardwithID();

	std::cout << "Printing with class" << std::endl << std::endl;
	board.printBoardwithClass();



return 0;
}
