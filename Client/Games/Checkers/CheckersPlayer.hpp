#ifndef CHECKERSPLAYER_HPP_INCLUDED
#define CHECKERSPLAYER_HPP_INCLUDED

#include "../GamePlayer.hpp"
#include <string>

using namespace std;

class CheckersPlayer: public GamePlayer
{
  private:
    string _colour;
    bool _isMyTurn;
  public:
    CheckersPlayer(string colour);
    ~CheckersPlayer();

    string getColour();
    bool isMyTurn();
    void switchTurn();
};




#endif // CHECKERSPLAYER_HPP_INCLUDED
