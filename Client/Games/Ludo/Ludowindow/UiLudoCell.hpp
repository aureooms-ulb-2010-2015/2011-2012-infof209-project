
#ifndef MYLABEL_H
#define MYLABEL_H


#include <QMovie>
#include "UiLudoPiece.hpp"
#include "UiCell.hpp"
#include "InformationDesk.hpp"

class UiLudoCell : public UiCell
{

   Q_OBJECT
   private:

        InformationDesk* _informationDesk;
        int _caseNumber;
        UiLudoPiece * _horse;


    public:
        UiLudoCell();
        int getCaseNumber();
        void setCaseNumber(int);
        void setHorse(UiLudoPiece* horse);
        UiLudoPiece* getHorse();
        bool findMyColor(int,int,int);//le booléen servira a dire si la case est un bridge ou pas


};

#endif // MYLABEL_H
