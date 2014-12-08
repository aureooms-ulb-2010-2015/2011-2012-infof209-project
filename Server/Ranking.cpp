#include "Ranking.hpp"
#include "./../Init/Init.hpp"


// class Ranking

Ranking::Ranking(string directoryPath)
{
	filePath = directoryPath + "Global_point.txt";
	fileTemp = directoryPath + "TemporaryFile.txt";
	createFile();
}

Ranking::Ranking(const char * dir)
{   
    string directoryPath = dir;
	filePath = directoryPath + "Global_point.txt";
	fileTemp = directoryPath + "TemporaryFile.txt";
	createFile();
}

string Ranking::getPlayerRanking(string nickname)
{
	vector<pair<string , int> > ranking = RankingSort();
	size_t i;
	for (i=0 ; i < ranking.size() && nickname.compare(ranking[i].first)!=0; i++ )
		;
	
	stringstream out;
	out << i+1;
	string s = out.str();
	
	return s;
}

int Ranking::getPlayerPoints(string nickname)
{
	FILE * pFile;
   char str [50];
   bool res = false;
	int point = 0;

   pFile = fopen (filePath.c_str(), "r");
   if (pFile == NULL) 
		perror ("Error opening file");
   else 
   {
       while(fscanf (pFile, "%s", str)!= EOF && res==false)
       {
			if (nickname.compare(str)== 0)
				res = true;
	   }
		fclose (pFile);
	}
	if(res == true){
	   	point = atoi(str);
    }
    else{
        this->addPlayer(nickname);
        point = POINT_INIT;
    }
	return point;
}

void Ranking::addPlayer(string nickname)
{

	if(researchNickname(nickname)== false)
	{
		string linePlayer;
		stringstream out;
		out << POINT_INIT;
		string s = out.str();
		linePlayer = nickname + " " + s; 
		FILE* file = fopen(filePath.c_str(), "a+");
		fprintf(file, "%s\n", linePlayer.c_str());
		fclose(file);
	}
	
}


void Ranking::setPlayerPoints(string nickname , int oldpoint, int newpoint)
{
	char line_file[1000];
	string space = " ";
	
	stringstream out1, out2;
	out1 << oldpoint;
	out2 << newpoint;
	string s1 = out1.str();
	string s2 = out2.str();
	
	string newline = nickname + space + s2; // the line of the player to edit in the file.
	string oldline = nickname + space + s1; //the line to replace in the file
	// we create the temporary file
	
	FILE* filepoint = fopen(filePath.c_str(), "r");
	if (filepoint == NULL)
		perror ("Error opening file");
	else 
	{
		FILE* fileTmp = fopen(fileTemp.c_str(), "w");
		while(fgets(line_file, 999 ,filepoint)!= NULL)
		{
			int ln = strlen(line_file);
			line_file[ln-1]='\0';
			if(oldline.compare(line_file)== 0)
			{
				fprintf(fileTmp, "%s\n", newline.c_str());
			}
			else 
				fprintf(fileTmp, "%s\n", line_file);
		}
		fclose(filepoint);
		fclose(fileTmp);
	
		rename( fileTemp.c_str() , filePath.c_str());
	}
}

void Ranking::addPointsToPlayer(string nickname , int point)
{
	
	
	int pt = getPlayerPoints(nickname);//we recovered the old score.
	int newpoint = pt + point; //score is added to the point obtained.
	setPlayerPoints(nickname , pt, newpoint);

}

void Ranking::subtractPointsToPlayer(string nickname , int point)
{
	
	
	int pt = getPlayerPoints(nickname);//we recovered the old score.
	if ( pt > point)
	{
		int newpoint = pt - point; //score is added to the point obtained.
		setPlayerPoints(nickname , pt, newpoint);
	}
	else{
	    setPlayerPoints(nickname,pt,0);
	}

}

string Ranking::getRankingList()
{
		vector<pair<string , int> > ranking = RankingSort();
		string rank;
		string separateur =";" ;
		
		for ( size_t i=0 ; i < ranking.size(); i++ )
		{
			stringstream out;
			out << ranking[i].second;
			string j = out.str();
			rank+= ranking[i].first + " " + j + separateur;
			
		}
		
	return rank;
	
}

void Ranking::createFile()
{
	//we check if the file already exists
	FILE* fileCreate;
	
	fileCreate = fopen(filePath.c_str(), "r");
	if( fileCreate == NULL ) //the file doesn't exist
	{
		fileCreate = fopen (filePath.c_str(), "w" );
		fclose(fileCreate);
	}
	else
	{
		fclose(fileCreate);
	}
	
}

vector<pair<string , int> > Ranking::RankingSort()
{
	vector<pair<string , int> > ranking;
	pair <string , int> p;
	string rank;
	char line[100] ;
	char word[50];
	int point;
	FILE* filepoint = fopen(filePath.c_str(), "r");
	if (filepoint == NULL)
		perror ("Error opening file");
	else 
	{
		while(fgets(line, 999 ,filepoint)!= NULL)
		{
			sscanf (line,"%s %d",word,&point);
			string nickname(word);
			p = make_pair (nickname,point);
			ranking.push_back(p);
			
		}
		
		sort (ranking.begin(), ranking.end(), comparePoints);
		reverse(ranking.begin(), ranking.end());
		
	}
	return ranking;
}


bool Ranking::researchNickname(string nickname)
{
	FILE * pFile;
   char mt [50];
   bool res = false;

   pFile = fopen (filePath.c_str() , "r");
   if (pFile == NULL) 
		perror ("Error opening file");
   else 
   {
       while(fscanf (pFile, "%s", mt)!= EOF && res==false)
       {
			if (nickname.compare(mt)== 0)
			{
				res = true;
			}	
	   }
		fclose (pFile);
   }
	return res;
}


bool comparePoints (pair<string , int> i , pair<string , int> j)
{
	return (i.second < j.second);
}



