#ifndef UILUDOBRIDGE_HPP
#define UILUDOBRIDGE_HPP

#include <QString>
#include "UiLudoCell.hpp"

class UiOwnedCell : public UiLudoCell
{
    private:
        int _ownerId;
    public:
        UiOwnedCell();
        UiOwnedCell(QString,int);
        int getOwnerId();
        void setOwnerId(int);

};

#endif // UILUDOBRIDGE_HPP
