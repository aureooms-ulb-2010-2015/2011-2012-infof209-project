#include "../h/communication_library.h"

bool Escaped(string content, unsigned int index){
	if((index == 0) || (content[index-1] != *"%")){
		return false;
	}
	else{
		return !(Escaped(content,index-1));
	}
}
vector<string> Split_get(string start,string token){
	vector<string> result;
	string buffer = start;
	string::size_type token_index;
	unsigned int pos = 0;
	while((token_index = buffer.find(token,pos)) != string::npos){
		if (Escaped(buffer,token_index)){
			if (token_index+1 < buffer.size()){
				break;
			}
			pos = token_index+1;
			continue;
		}
		if (token_index != 0){
			result.push_back(buffer.substr(0, token_index));
		}
		buffer = buffer.substr(token_index + 1);
	}
	
	result.push_back(buffer);
	return result;
}


string Escape_get(string start){
	ostringstream result;
	unsigned int index = 0;
	while (index < start.size()){
		if ((start[index] == *"&")
			|| (start[index] == *"%")
			|| (start[index] == *"=")
			|| (start[index] == *"?")){
			result << "%";
		}
		result << start[index];
		index++;
	}
	return result.str();
}

string Unescape_get(string start){
	ostringstream result;
	unsigned int index = 0;
	while (index < start.size()){
		if (start[index] == *"%"){
			index++;
		}
		result << start[index];
		index++;
	}
	return result.str();
}


string Replace(string start,const char* token,const char* replacement){
	ostringstream result;
	for (unsigned int index = 0;index<start.size();index++){
		if(start[index] == *token){
			result << *replacement;
		}
		else{
			result << start[index];
		}
	}
	return result.str();
}

string valid_filename(string filename){
	filename = Replace(filename,"é","e");
	filename = Replace(filename," ","_");
	filename = Replace(filename,"!","");
	filename = Replace(filename,"ç","c");
	filename = Replace(filename,"{","");
	filename = Replace(filename,"}","");
	filename = Replace(filename,"(","");
	filename = Replace(filename,")","");
	filename = Replace(filename,"&","");
	filename = Replace(filename,"@","");
	filename = Replace(filename,"\"","");
	filename = Replace(filename,"'","");
	filename = Replace(filename,"§","");
	filename = Replace(filename,"#","");
	filename = Replace(filename,"^","");
	filename = Replace(filename,"à","a");
	filename = Replace(filename,"°","");
	return filename;
}

string Serialize(map<string,string> content){
	ostringstream result;
	map<string,string>::iterator iterator;
	for (iterator=content.begin(); iterator!=content.end(); ++iterator){
		if(iterator!=content.begin()){
			result << "&";
		}
		result << Escape_get(string(iterator->first));
		result << "=";
		result << Escape_get(string(iterator->second));
	}
	return result.str();
}

map<string,string> Deserialize(string encoded){
	map<string,string> result;
	vector<string> pairs =  Split_get(encoded,"&");
	vector<string>::iterator iterator;
	for (iterator=pairs.begin(); iterator!=pairs.end(); ++iterator){
		string couple = *iterator;
		string attribute =  Unescape_get(Split_get(couple,"=")[0]);
		string value =  Unescape_get(Split_get(couple,"=")[1]);
		result.insert(pair<string,string>(attribute,value));
	}
	return result;
}
