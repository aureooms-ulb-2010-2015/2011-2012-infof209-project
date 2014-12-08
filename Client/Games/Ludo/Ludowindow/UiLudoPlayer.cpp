#include "UiLudoPlayer.hpp"
#include <sstream>


UiLudoPlayer::UiLudoPlayer(QString color, int id ) : LudoPlayer(color.toStdString())
{
    
    int intcolor;
    for(int i = 0; i<4; ++i){
             UiLudoPiece* newPiece= new UiLudoPiece(color,-1,i);
            this->_hisPieces->push_back(newPiece);
    }
    setIDPlayer(id);
    istringstream temp(color.toStdString());
    temp>>intcolor;
    this->setplayerColor(intcolor);

}
