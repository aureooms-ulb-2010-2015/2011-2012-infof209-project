#ifndef GAME_INFOS
#define GAME_INFOS

#include <string>

using namespace std;

class GameInfos{
    private :
        string _type;
        string _name;
        int _nPlayers;
        int _maxPlayers;
        int _id;
   public :
        GameInfos(string type, string name, int id, int nPlayers, int maxPlayers){
            setType(type);
            setName(name);
            setId(id);
            setNumberOfPlayers(nPlayers);
            setRequiredPlayers(maxPlayers);
        }
        string getType(){return _type;}
        string getName(){return _name;}
        int getNumberOfPlayers(){return _nPlayers;}
        int getRequiredPlayers(){return _maxPlayers;}
        int getId(){return _id;}
        
        void setType(string type){_type = type;}
        void setName(string name){_name = name;}
        void setNumberOfPlayers(int i){_nPlayers = i;}
        void setRequiredPlayers(int i){_maxPlayers = i;}
        void setId(int i){_id = i;}
};

#endif
