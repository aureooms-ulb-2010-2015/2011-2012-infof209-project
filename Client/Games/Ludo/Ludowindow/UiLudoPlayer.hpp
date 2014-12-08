#ifndef UILUDOPLAYER_HPP
#define UILUDOPLAYER_HPP


#include "UiLudoPiece.hpp"
#include "UiOwnedCell.hpp"
#include "../LudoClass/LudoPlayer.hpp"

#include <QString>

class UiLudoPlayer : public LudoPlayer
{
public:
    UiLudoPlayer(QString,int);
};

#endif // UILUDOPLAYER_HPP
