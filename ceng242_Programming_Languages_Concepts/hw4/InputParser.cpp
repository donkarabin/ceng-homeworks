#include"InputParser.h"
#include <string>
//#include"Constants.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Game* InputParser::parseGame(){
    uint size;
    int chx,chy,px,py;
    uint maxturn;
    int num_p;
    int p_id;
    Team team;
    std::string cls;
    std::string tim;


    std::cin >> size;
    std::cin >>chx>>chy;
    std::cin >> maxturn;
    std::cin >> num_p;
    Coordinate chest(chx,chy);
    Game* g= new Game(maxturn,size,chest);
    for(int i=0; i<num_p; i++){
        std::cin >> p_id>> cls>> tim>>px>>py;
        //std::istream& operator>> (std::istream& in, Team team); 
        if(tim=="BARBARIANS"){
            team=BARBARIANS;
        }
        else if(tim=="KNIGHTS"){
            team=KNIGHTS;
        }
        
        g->addPlayer(p_id,px,py,team,cls);
    }


    return g;

}