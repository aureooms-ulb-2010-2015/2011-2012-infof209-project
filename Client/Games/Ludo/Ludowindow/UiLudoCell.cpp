#include "UiLudoCell.hpp"
#include "Const.hpp"
#include <QDebug>

UiLudoCell::UiLudoCell(){

    _informationDesk = new InformationDesk;
}


int UiLudoCell::getCaseNumber(){return _caseNumber;}
void UiLudoCell::setCaseNumber(int caseNumber){_caseNumber=caseNumber;}

void UiLudoCell::setHorse(UiLudoPiece* horse){_horse = horse;}
UiLudoPiece* UiLudoCell::getHorse(){return _horse;}

bool UiLudoCell::findMyColor(int i,int j,int k){
    bool res=false;

    if (_informationDesk->northSide(i,j)){


        if (i==0){
            if(j==6){ this->setCaseNumber(49);}
            else if(j==7){ this->setCaseNumber(50);}
            else if(j==8){ this->setCaseNumber(51);}
            this->setMycolorPath(_informationDesk->getGreyPath());



        }

        else if (i==1){
            if(j==6){
                this->setCaseNumber(48);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }
            else if(j==7){
                this->setCaseNumber(100);
                this->setMycolorPath(_informationDesk->getRedPath());




            }
            else if(j==8){
                this->setCaseNumber(0);
                this->setMycolorPath(_informationDesk->getRedPath());

            }

        }

        else if (i==2){
            if(j==6){
                this->setCaseNumber(47);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }
            else if(j==7){
                this->setCaseNumber(101);
                this->setMycolorPath(_informationDesk->getRedPath());

            }
            else if(j==8){
                this->setCaseNumber(1);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }

        }

        else if (i==3){
            if(j==6){
                this->setCaseNumber(46);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }
            else if(j==7){
                this->setCaseNumber(102);
                this->setMycolorPath(_informationDesk->getRedPath());

            }
            else if(j==8){
                this->setCaseNumber(2);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }

        }

        else if (i==4){
            if(j==6){
                this->setCaseNumber(45);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }
            else if(j==7){
                this->setCaseNumber(103);
                this->setMycolorPath(_informationDesk->getRedPath());

            }
            else if(j==8){
                this->setCaseNumber(3);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }

        }
        else if (i==5){
            if(j==6){
                this->setCaseNumber(44);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }
            else if(j==7){
                this->setCaseNumber(104);
                this->setMycolorPath(_informationDesk->getRedPath());

            }
            else if(j==8){
                this->setCaseNumber(4);
                this->setMycolorPath(_informationDesk->getGreyPath());

            }

        }
    }
    else if (_informationDesk->westSide(i,j)){


            if(i==6){
                if (j==0){
                    this->setCaseNumber(38);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==1){
                    this->setCaseNumber(39);
                    this->setMycolorPath(_informationDesk->getGreenPath());

                }
                else if (j==2){
                    this->setCaseNumber(40);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==3){
                    this->setCaseNumber(41);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==4){
                    this->setCaseNumber(42);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==5){
                    this->setCaseNumber(43);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }

            }
            else if(i==7){
                if (j==0){
                    this->setCaseNumber(37);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==1){
                    this->setCaseNumber(100);
                    this->setMycolorPath(_informationDesk->getGreenPath());

                }
                else if (j==2){
                    this->setCaseNumber(101);
                    this->setMycolorPath(_informationDesk->getGreenPath());

                }
                else if (j==3){
                    this->setCaseNumber(102);
                    this->setMycolorPath(_informationDesk->getGreenPath());

                }
                else if (j==4){
                    this->setCaseNumber(103);
                    this->setMycolorPath(_informationDesk->getGreenPath());

                }
                else if (j==5){
                    this->setCaseNumber(104);
                    this->setMycolorPath(_informationDesk->getGreenPath());

                }

            }

            else if(i==8){
                if (j==0){
                    this->setCaseNumber(36);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==1){
                    this->setCaseNumber(35);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==2){
                    this->setCaseNumber(34);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==3){
                    this->setCaseNumber(33);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==4){
                    this->setCaseNumber(32);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if (j==5){
                    this->setCaseNumber(31);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }

            }


        }

    else if (_informationDesk->southSide(i,j)){


            if (i==9){
                if(j==6){
                    this->setCaseNumber(30);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if(j==7){
                    this->setCaseNumber(104);
                    this->setMycolorPath(_informationDesk->getYellowPath());

                }
                else if(j==8){
                    this->setCaseNumber(18);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
            }

            else if (i==10){
                if(j==6){
                    this->setCaseNumber(29);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if(j==7){
                    this->setCaseNumber(103);
                    this->setMycolorPath(_informationDesk->getYellowPath());

                }
                else if(j==8){
                    this->setCaseNumber(19);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }

            }

            else if (i==11){
                if(j==6){
                    this->setCaseNumber(28);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if(j==7){
                    this->setCaseNumber(102);
                    this->setMycolorPath(_informationDesk->getYellowPath());

                }
                else if(j==8){
                    this->setCaseNumber(20);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }

            }

            else if (i==12){
                if(j==6){
                    this->setCaseNumber(27);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }
                else if(j==7){
                    this->setCaseNumber(101);
                    this->setMycolorPath(_informationDesk->getYellowPath());

                }
                else if(j==8){
                    this->setCaseNumber(21);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }

            }

            else if (i==13){
                if(j==6){
                    this->setCaseNumber(26);
                    this->setMycolorPath(_informationDesk->getYellowPath());

                }
                else if(j==7){
                    this->setCaseNumber(100);
                    this->setMycolorPath(_informationDesk->getYellowPath());

                }
                else if(j==8){
                    this->setCaseNumber(22);
                    this->setMycolorPath(_informationDesk->getGreyPath());

                }

            }
            else if (i==14){
                if(j==6){this->setCaseNumber(25);}
                else if(j==7){ this->setCaseNumber(24);}
                else if(j==8){this->setCaseNumber(23);}
                this->setMycolorPath(_informationDesk->getGreyPath());


            }

        }

    else if (_informationDesk->eastSide(i,j)){

             if(i==6){

                 if (j==9){ this->setCaseNumber(5);}
                 else if (j==10){ this->setCaseNumber(6);}
                 else if (j==11){ this->setCaseNumber(7);}
                 else if (j==12){this->setCaseNumber(8);}
                 else if (j==13){this->setCaseNumber(9);}
                 else if (j==14){ this->setCaseNumber(10);}
                 this->setMycolorPath(_informationDesk->getGreyPath());


             }
             else if(i==7){
                 if ((j>=9) && (j<=13)){
                     if (j==9){this->setCaseNumber(104);}
                     else if (j==10){this->setCaseNumber(103);}
                     else if (j==11){this->setCaseNumber(102);}
                     else if (j==12){this->setCaseNumber(101);}
                     else if (j==13){this->setCaseNumber(100);}
                     this->setMycolorPath(_informationDesk->getBluePath());

                 }
                 else{
                     this->setCaseNumber(11);
                     this->setMycolorPath(_informationDesk->getGreyPath());

                 }

             }

             else if(i==8){
                 if (j==9){
                     this->setCaseNumber(17);
                     this->setMycolorPath(_informationDesk->getGreyPath());

                 }
                 else if (j==10){
                     this->setCaseNumber(16);
                     this->setMycolorPath(_informationDesk->getGreyPath());

                 }
                 else if (j==11){
                     this->setCaseNumber(15);
                     this->setMycolorPath(_informationDesk->getGreyPath());

                 }
                 else if (j==12){
                     this->setCaseNumber(14);
                     this->setMycolorPath(_informationDesk->getGreyPath());

                 }
                 else if (j==13){
                     this->setCaseNumber(13);
                     this->setMycolorPath(_informationDesk->getBluePath());

                 }
                 else if (j==14){
                     this->setCaseNumber(12);
                     this->setMycolorPath(_informationDesk->getGreyPath());

                 }

             }


         }

    if (this->getCaseNumber()>=100){

        res=true;
    }
    return res;

}



