#include "Ranking_test.hpp"

Test::Test()
{
	name = new string("julien");
	point = new int (0);
	rank = new Ranking("");
}

Test::~Test()
{
	delete name; delete point, delete rank; 
}

void Test::test_addPlayer()
{
	rank->addPlayer(name[0]);
	assert(rank->reserchNickname(name[0])==true);
}


void Test::test_addPointToPlayer()
{
	point[0] = rank->getPlayerPoint(name[0]);
	int p = 500;
	rank->addPointToPlayer(name[0], p);
	assert(rank->getPlayerPoint(name[0]) == point[0] + p);
}

void Test::test_subtractPointToPlayer()
{
	point[0] = rank->getPlayerPoint(name[0]);
	int p = 500;
	rank->subtractPointToPlayer(name[0], p);
	if (point[0] > p)
		assert(rank->getPlayerPoint(name[0]) == point[0] - p);
	else
		assert(rank->getPlayerPoint(name[0]) == point[0]);
}






