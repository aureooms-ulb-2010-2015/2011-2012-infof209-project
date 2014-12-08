#if !defined(_COMMUNICATION_LIBRARY)
#define _COMMUNICATION_LIBRARY
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
using namespace std;

bool Escaped(string content, unsigned int index);
vector<string> Split_get(string start,string token);


string Escape_get(string start);
string Unescape_get(string start);


string Replace(string start,const char* token,const char* replacement);

string valid_filename(string filename);

string Serialize(map<string,string> content);
map<string,string> Deserialize(string encoded);

#endif
