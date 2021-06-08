#include"Game.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Game::Game(uint maxTurnNumber, uint boardSize, Coordinate chest) : board(boardSize,&players,chest){
    turnNumber=1;
    this->maxTurnNumber=maxTurnNumber;

}

Game::~Game(){
    int s=players.size();
    for(int i=0;i<s;i++){
        delete players[i];
    }
}

void Game::addPlayer(int id, int x, int y, Team team, std::string cls){
    if(cls=="ARCHER"){
        Player* a=new Archer(id,x,y,team);
        players.push_back(a);
    }
    else if(cls=="FIGHTER"){
        Player* f=new Fighter(id,x,y,team);
        players.push_back(f);
    }
    else if(cls=="PRIEST"){
        Player* p=new Priest(id,x,y,team);
        players.push_back(p);
    }
    else if(cls=="SCOUT"){
        Player* s=new Scout(id,x,y,team);
        players.push_back(s);
    }
    else{
        Player* t=new Tank(id,x,y,team);
        players.push_back(t);
    }
}

bool Game::isGameEnded(){
    int s=this->getBoard()->getboardsize();
    int vs=players.size();
    int bs=0,ks=0,chestflag=0;
    Coordinate c=this->getBoard()->getChestCoordinates();


    for(int i=0;i<vs;i++){
        if((players[i]->getTeam())==BARBARIANS){
            bs++;
        }
        else if((players[i]->getTeam())==KNIGHTS){
            ks++;
        }
    }


    


    for(int i=0;i<vs;i++){
        if((players[i]->getTeam())==BARBARIANS && players[i]->getCoord().x==c.x && players[i]->getCoord().y==c.y){
            chestflag=222;
        }
    }


    if(bs==0){           //if all barbarians die
        std::cout<<"Game ended at turn "<<turnNumber<<". All barbarians dead. Knight victory."<<std::endl;
    }

    else if(ks==0){   //if all knights died
        std::cout<<"Game ended at turn "<<turnNumber<<". All knights dead. Barbarian victory."<<std::endl;

    }
    else if(turnNumber==maxTurnNumber){ //knights victory by maxturn
        std::cout<<"Game ended at turn "<<turnNumber<<". Maximum turn number reached. Knight victory."<<std::endl;

    }
    else if(chestflag==222){  //barbarians reached the chest
        std::cout<<"Game ended at turn "<<turnNumber<<". Chest captured. Barbarian victory."<<std::endl;

    }

}


void Game::playTurn(){
    this->sorting();
    int s=players.size();
    std::cout<<"Turn "<<turnNumber<<" has started."<<std::endl;
    for(int i=0;i<s;i++){
        playTurnForPlayer(players[i]);
    }
    turnNumber++;
}

Goal Game::playTurnForPlayer(Player* player){
    int vs=this->players.size();
    int a;
    int ps=player->getGoalPriorityList().size();
    std::vector<Goal> plist=player->getGoalPriorityList();
    std::cout<<"asgdiahsasdas"<<std::endl;
    Team pteam=player->getTeam();

    if(player->isDead()){
        std::cout<<"Player "<<player->getBoardID()<<" died."<<std::endl;

        for(int i=0 ; i<vs ; i++){
            if(players[i] == player){
                delete players[i];
                a=i;
            }
        }
        players.erase(players.begin()+a);
    }
    else{
        for(int i=0; i<ps; i++){

            if(plist[i]==ATTACK){

                std::vector<Coordinate> atcor=player->getAttackableCoordinates();
                std::vector<Player*> attackables;

                for(int j=0; j<atcor.size(); i++){
                    if(this->getBoard()->isPlayerOnCoordinate(atcor[i])){
                        if(pteam==BARBARIANS && (this->getBoard()->operator[](atcor[i]))->getTeam()==KNIGHTS ){
                            attackables.push_back(this->getBoard()->operator[](atcor[i]));
                        }
                        else if(pteam==KNIGHTS && (this->getBoard()->operator[](atcor[i]))->getTeam()==BARBARIANS ){
                            attackables.push_back(this->getBoard()->operator[](atcor[i]));
                        }
                    }
                }
                if(attackables.size()!=0){
                    sortids(attackables);
                    player->attack(attackables[0]);
                    return ATTACK;
                }
            }

            else if(plist[i]==CHEST){
                std::vector<Coordinate> movcor=player->getMoveableCoordinates();
                int ms=movcor.size();
                int manabs=(player->getCoord()) - (this->getBoard()->getChestCoordinates());
                std::vector<Coordinate> carr;
                std::vector<int> mar;
                
                
                int mcorabs;
                for(int i=0; i<ms; i++){
                    if(!(this->getBoard()->isPlayerOnCoordinate(movcor[i]))){
                        mcorabs=movcor[i] - (this->getBoard()->getChestCoordinates());
                        mar.push_back(mcorabs);
                        carr.push_back(movcor[i]);
                    }
                }
                int scarr=carr.size();
                Coordinate *c;
                int tmp;
                if(scarr!=0){
                    tmp=mar[0];
                    for(int i=0; i<scarr; i++){
                        if(tmp>mar[i]){
                            tmp=mar[i];
                            *c=carr[i];
                        }
                    }
                }

                if(tmp<manabs){
                    player->movePlayerToCoordinate(*c);
                    return CHEST;

                }
            
            
            }

            else if(plist[i]==TO_ENEMY){
                Coordinate *c;

                if(player->getTeam()==BARBARIANS){

                    std::vector<Player*> enem;
                    std::vector<int> distances;
                    int mdis;
                    Player* p1=NULL;
                    Player* p2=NULL;
                    Player* closest=NULL;


                    for(int i=0; i<vs; i++){

                        if(players[i]->getTeam()==KNIGHTS){

                            *c=players[i]->getCoord();
                            enem.push_back(players[i]);
                            mdis=*c-player->getCoord();
                            distances.push_back(mdis);
                            
                        }
                    }

                    int s1=distances.size();
                    int tmp=20000000;
                    int t2;
                    for(int i=0; i<s1; i++){
                        if(tmp>distances[i]){
                            tmp=distances[i];
                            p1=enem[i];
                        }
                        else if(tmp==distances[i]){
                            p2=enem[i];
                            t2=tmp;
                        }
                    }
                    if(p2 && t2==tmp){
                        if(p1->getID()<p2->getID()){
                            closest=p1;
                        }
                        else
                        {
                            closest=p2;
                        }
                        
                    }
                    else if(t2!=tmp || p2==NULL){
                        closest=p1;
                    }

                    std::vector<Coordinate> movcor=player->getMoveableCoordinates();
                    int ms=movcor.size();
                    
                    std::vector<Coordinate> carr;
                    std::vector<int> mar;
                    int mcorabs;
                    for(int i=0; i<ms; i++){
                        if(!(this->getBoard()->isPlayerOnCoordinate(movcor[i]))){
                            mcorabs=movcor[i] - (closest->getCoord());
                            mar.push_back(mcorabs);
                            carr.push_back(movcor[i]);
                        }
                    }

                    int scarr=carr.size();
                    Coordinate *c2;
                    int tmp2;
                    if(scarr!=0){
                        tmp2=mar[0];
                        for(int i=0; i<scarr; i++){
                            if(tmp2>mar[i]){
                                tmp2=mar[i];
                                *c2=carr[i];
                            }
                        }
                    player->movePlayerToCoordinate(*c2);
                    return TO_ENEMY;
                    }
                }


                else if(player->getTeam()==KNIGHTS){

                    std::vector<Player*> enem;
                    std::vector<int> distances;
                    int mdis;
                    Player* p1=NULL;
                    Player* p2=NULL;
                    Player* closest=NULL;


                    for(int i=0; i<vs; i++){

                        if(players[i]->getTeam()==BARBARIANS){

                            *c=players[i]->getCoord();
                            enem.push_back(players[i]);
                            mdis=*c-player->getCoord();
                            distances.push_back(mdis);
                            
                        }
                    }

                    int s1=distances.size();
                    int tmp=20000000;
                    int t2;
                    for(int i=0; i<s1; i++){
                        if(tmp>distances[i]){
                            tmp=distances[i];
                            p1=enem[i];
                        }
                        else if(tmp==distances[i]){
                            p2=enem[i];
                            t2=tmp;
                        }
                    }
                    if(p2 && t2==tmp){
                        if(p1->getID()<p2->getID()){
                            closest=p1;
                        }
                        else
                        {
                            closest=p2;
                        }
                        
                    }
                    else if(t2!=tmp || p2==NULL){
                        closest=p1;
                    }

                    std::vector<Coordinate> movcor=player->getMoveableCoordinates();
                    int ms=movcor.size();
                    
                    std::vector<Coordinate> carr;
                    std::vector<int> mar;
                    int mcorabs;
                    for(int i=0; i<ms; i++){
                        if(!(this->getBoard()->isPlayerOnCoordinate(movcor[i]))){
                            mcorabs=movcor[i] - (closest->getCoord());
                            mar.push_back(mcorabs);
                            carr.push_back(movcor[i]);
                        }
                    }

                    int scarr=carr.size();
                    Coordinate *c2;
                    int tmp2;
                    if(scarr!=0){
                        tmp2=mar[0];
                        for(int i=0; i<scarr; i++){
                            if(tmp2>mar[i]){
                                tmp2=mar[i];
                                *c2=carr[i];
                            }
                        }
                    player->movePlayerToCoordinate(*c2);
                    return TO_ENEMY;
                    }
                }
            }



            else if(plist[i]==TO_ALLY){
                Coordinate *c;
                if(player->getTeam()==BARBARIANS){
                    std::vector<Player*> ally;
                    std::vector<int> distances;
                    int mdis;
                    Player* p1=NULL;
                    Player* p2=NULL;
                    Player* closest=NULL;


                    for(int i=0; i<vs; i++){

                        if(players[i]->getTeam()==BARBARIANS && players[i]!=player){

                            *c=players[i]->getCoord();
                            ally.push_back(players[i]);
                            mdis=*c-player->getCoord();
                            distances.push_back(mdis);
                            
                        }
                    }

                    int s1=distances.size();
                    int tmp=20000000;
                    int t2;
                    for(int i=0; i<s1; i++){
                        if(tmp>distances[i]){
                            tmp=distances[i];
                            p1=ally[i];
                        }
                        else if(tmp==distances[i]){
                            p2=ally[i];
                            t2=tmp;
                        }
                    }
                    if(p2 && t2==tmp){
                        if(p1->getID()<p2->getID()){
                            closest=p1;
                        }
                        else
                        {
                            closest=p2;
                        }
                        
                    }
                    else if(t2!=tmp || p2==NULL){
                        closest=p1;
                    }

                    std::vector<Coordinate> movcor=player->getMoveableCoordinates();
                    int ms=movcor.size();
                    
                    std::vector<Coordinate> carr;
                    std::vector<int> mar;
                    int mcorabs;
                    for(int i=0; i<ms; i++){
                        if(!(this->getBoard()->isPlayerOnCoordinate(movcor[i]))){
                            mcorabs=movcor[i] - (closest->getCoord());
                            mar.push_back(mcorabs);
                            carr.push_back(movcor[i]);
                        }
                    }

                    int scarr=carr.size();
                    Coordinate *c2;
                    int tmp2;
                    if(scarr!=0){
                        tmp2=mar[0];
                        for(int i=0; i<scarr; i++){
                            if(tmp2>mar[i]){
                                tmp2=mar[i];
                                *c2=carr[i];
                            }
                        }
                    player->movePlayerToCoordinate(*c2);
                    return TO_ALLY;
                    }
                }

                else if(player->getTeam()==KNIGHTS){
                    std::vector<Player*> ally;
                    std::vector<int> distances;
                    int mdis;
                    Player* p1=NULL;
                    Player* p2=NULL;
                    Player* closest=NULL;


                    for(int i=0; i<vs; i++){

                        if(players[i]->getTeam()==KNIGHTS && players[i]!=player){

                            *c=players[i]->getCoord();
                            ally.push_back(players[i]);
                            mdis=*c-player->getCoord();
                            distances.push_back(mdis);
                            
                        }
                    }

                    int s1=distances.size();
                    int tmp=20000000;
                    int t2;
                    for(int i=0; i<s1; i++){
                        if(tmp>distances[i]){
                            tmp=distances[i];
                            p1=ally[i];
                        }
                        else if(tmp==distances[i]){
                            p2=ally[i];
                            t2=tmp;
                        }
                    }
                    if(p2 && t2==tmp){
                        if(p1->getID()<p2->getID()){
                            closest=p1;
                        }
                        else
                        {
                            closest=p2;
                        }
                        
                    }
                    else if(t2!=tmp || p2==NULL){
                        closest=p1;
                    }

                    std::vector<Coordinate> movcor=player->getMoveableCoordinates();
                    int ms=movcor.size();
                    
                    std::vector<Coordinate> carr;
                    std::vector<int> mar;
                    int mcorabs;
                    for(int i=0; i<ms; i++){
                        if(!(this->getBoard()->isPlayerOnCoordinate(movcor[i]))){
                            mcorabs=movcor[i] - (closest->getCoord());
                            mar.push_back(mcorabs);
                            carr.push_back(movcor[i]);
                        }
                    }

                    int scarr=carr.size();
                    Coordinate *c2;
                    int tmp2;
                    if(scarr!=0){
                        tmp2=mar[0];
                        for(int i=0; i<scarr; i++){
                            if(tmp2>mar[i]){
                                tmp2=mar[i];
                                *c2=carr[i];
                            }
                        }
                    player->movePlayerToCoordinate(*c2);
                    return TO_ALLY;
                    }
                }
            }

            else if(plist[i]==HEAL){
                std::vector<Coordinate> range=player->getHealableCoordinates();
                int sr=range.size();
                Team tim=player->getTeam();
                for(int i=0; i<sr; i++){
                    if(this->getBoard()->isPlayerOnCoordinate(range[i]) && (this->getBoard()->operator[](range[i])->getTeam())==tim){
                        player->heal(this->getBoard()->operator[](range[i]));
                    }
                }
                return HEAL;
            }

        }




    }

    //std::cout<<"ASDASDASDASD"<<std::endl;

    return NO_GOAL;
}



void Game::sorting(){
    int vs=this->players.size();
    int t;
    int a[vs];
    Player* p[vs];
    Player* tmp=NULL;

   for(int i=0;i<vs;i++)
   {
       int aid=players[i]->getID();
       a[i]=aid;
       p[i]=players[i];
   }

     
    for (int k=0;k<vs; ++k) 
    {
        for (int j= k+1; j<vs; ++j)
        {
            if (a[k] > a[j]) 
                {
                    t = a[k];
                    a[k] = a[j];
                    a[j] = t;

                    tmp=p[k];
                    p[k]=p[j];
                    p[j]=tmp;


                }
            }
    }

players.clear();

for(int l=0; l<vs; ++l){
    players.push_back(p[l]);
    }
    
    
}


void Game::sortids(std::vector<Player*> vec){
    int vs=vec.size();
    int t;
    int a[vs];
    Player* p[vs];
    Player* tmp=NULL;

   for(int i=0;i<vs;i++)
   {
       int aid=vec[i]->getID();
       a[i]=aid;
       p[i]=vec[i];
   }

     
    for (int k=0;k<vs; ++k) 
    {
        for (int j= k+1; j<vs; ++j)
        {
            if (a[k] > a[j]) 
                {
                    t = a[k];
                    a[k] = a[j];
                    a[j] = t;

                    tmp=p[k];
                    p[k]=p[j];
                    p[j]=tmp;


                }
            }
    }

vec.clear();

for(int l=0; l<vs; ++l){
    vec.push_back(p[l]);
    }

}