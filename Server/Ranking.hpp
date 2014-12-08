#ifndef _Ranking_HPP
#define _Ranking_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
#include "../Init/Init.hpp"


using namespace std;

class Ranking
{
	
	public:
	
	Ranking(string directoryPath);
	Ranking(const char * directoryPath);
	~Ranking(){}
	string getPlayerRanking(string nickname);
	int getPlayerPoints(string nickname);
	void addPlayer(string nickname);
	void addPointsToPlayer(string nickname , int point);
	void subtractPointsToPlayer(string nickname , int point);
	string getRankingList();
	bool researchNickname( string nickname);
	
	private:

	string filePath;
	string fileTemp;	
	void createFile();
	vector<pair<string , int> > RankingSort();
	void setPlayerPoints(string nickname , int oldpoint, int newpoint);
	
};

bool comparePoints (pair<string , int> i , pair<string , int> j);

#endif /* _Ranking_HPP */













