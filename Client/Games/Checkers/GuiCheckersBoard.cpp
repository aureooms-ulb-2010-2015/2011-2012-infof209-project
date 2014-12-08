#include "GuiCheckersBoard.hpp"


GuiCheckersBoard::GuiCheckersBoard():CheckersBoard(),QGridLayout()
{
    this->setSpacing(0);

}

GuiCheckersBoard::~GuiCheckersBoard()
{

}

void GuiCheckersBoard::addPiece(int row,int column, CheckersPiece* piece)
{
    this->_board[row][column] = piece;
    if (piece->getColour() == "White")
    {
        if (piece->isAKing())
            this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/WhiteKingPiece.png"));
        else
            this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/WhitePiece.png"));
    }

    else if (piece->getColour() == "Black")
    {
        if (piece->isAKing())
            this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/BlackKingPiece.png"));
        else
            this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/BlackPiece.png"));
    }
}

void GuiCheckersBoard::unselectPiece(int row,int column)
{
    if (not this->empty(row,column))
    {
        if (this->_board[row][column]->getColour() == "White")
        {
            if (((CheckersPiece*)this->_board[row][column])->isAKing())
                this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/WhiteKingPiece.png"));
            else
                this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/WhitePiece.png"));
        }

        else if (this->_board[row][column]->getColour() == "Black")
        {
            if (((CheckersPiece*)this->_board[row][column])->isAKing())
                this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/BlackKingPiece.png"));
            else
                this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/BlackPiece.png"));
        }

    }
}

void GuiCheckersBoard::selectPiece(int row,int column)
{
    if (not this->empty(row,column))
        this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/redCell.png"));
}

void GuiCheckersBoard::removePiece(int row,int column)
{
    this->_board[row][column] = NULL;
    this->labelGrid[row][column]->setPixmap(QPixmap("./Interface/Images/Checkers/BlackCell.png"));
}

void GuiCheckersBoard::initBoard()
{
    for (int i = 0;i<10;++i)
    {
        for(int j = 0;j<10;++j)
        {
            //Placement des pieces sur le plateau de jeu
            if(i<4 && i%2 != j%2)
            {
                _board[i][j] = new StandardCheckersPiece("Black");
                QLabel* aLabel = new QLabel();
                aLabel->setPixmap(QPixmap("./Interface/Images/Checkers/BlackPiece.png"));
                this->labelGrid[i][j] = aLabel;
                this->addWidget(labelGrid[i][j],i,j);
            }
            else if (i>5 && i%2 != j%2)
            {
                _board[i][j] = new StandardCheckersPiece("White");
                QLabel* aLabel = new QLabel();
                aLabel->setPixmap(QPixmap("./Interface/Images/Checkers/WhitePiece.png"));
                this->labelGrid[i][j] = aLabel;
                this->addWidget(labelGrid[i][j],i,j);
            }
            else if(i%2 != j%2)
            {
                _board[i][j] = NULL;
                QLabel* aLabel = new QLabel();
                aLabel->setPixmap(QPixmap("./Interface/Images/Checkers/BlackCell.png"));
                this->labelGrid[i][j] = aLabel;
                this->addWidget(labelGrid[i][j],i,j);
            }
            else
            {
                _board[i][j] = NULL;
                QLabel* aLabel = new QLabel();
                aLabel->setPixmap(QPixmap("./Interface/Images/Checkers/WhiteCell.png"));
                this->labelGrid[i][j] = aLabel;
                this->addWidget(labelGrid[i][j],i,j);

            }

            delete (_board[0][0]);
            _board[0][0] = NULL;
        }
    }
}

void GuiCheckersBoard::checkForKings()
{
    for(int i = 0; i < 10;++i)
    {
        if (this->_board[0][i] != NULL && this->_board[0][i]->getColour() == "White")
        {
            this->_board[0][i] = new KingCheckersPiece("White");
            this->labelGrid[0][i]->setPixmap(QPixmap("./Interface/Images/Checkers/WhiteKingPiece.png"));
        }
        else if (this->_board[9][i] != NULL && this->_board[9][i]->getColour() == "Black")
        {
            this->_board[9][i] = new KingCheckersPiece("Black");
            this->labelGrid[9][i]->setPixmap(QPixmap("./Interface/Images/Checkers/BlackKingPiece.png"));
        }
    }
}



