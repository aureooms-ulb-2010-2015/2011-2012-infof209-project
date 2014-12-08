#ifndef CLIENT_PLAYER
#define CLIENT_PLAYER

#include <string>

using namespace std;

class Player{
    private:
        string _name;
        int _id;
        int _points;
    public:
        Player(){}
        Player(string n){_name = n;}
        Player(int id, string name, int p){ _name = name;_id = id;_points = p;}
        
        virtual string getName(){return _name;}
        virtual int getId(){return _id;}
        virtual int getPoints(){return _points;}
        
        virtual void setName(string n){_name = n;}
        virtual void setId(int id){_id = id;}
        virtual void setPoints(int i){_points = i;}
        
};

#endif
