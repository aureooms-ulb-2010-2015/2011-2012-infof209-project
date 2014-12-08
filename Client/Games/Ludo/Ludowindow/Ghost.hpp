#ifndef GHOST_HPP
#define GHOST_HPP
#include <QLabel>
#include <QMovie>

class Ghost : public QLabel
{
    private:
        QString _path;
        int _gridi;
        int _gridj;

        QMovie *_ghostMovie;
    public:
        Ghost(int,int);
        int getGridI();
        int getGridJ();
};

#endif // GHOST_HPP
