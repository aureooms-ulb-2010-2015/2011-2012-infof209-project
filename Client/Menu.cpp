#include "Menu.hpp"
#include <stdlib.h>
Menu::Menu(){
    this->_title = "";
}

Menu::Menu(string title){
    this->_title = title;
}

Menu::Menu(const char * title){
    this->_title = title;
}

void Menu::addField(string field){
    this->_fields.push_back(field);
    this->_subMenus.push_back(NULL);
}

void Menu::addField(const char * field){
    this->_fields.push_back(field);
    this->_subMenus.push_back(NULL);
}

void Menu::addQuestion(string s){
    this->_subQuestions.push_back(s);
}

void Menu::addAnswer(string a){
    this->_answers.push_back(a);
}

void Menu::addTag(string t){
    this->_questionTags.push_back(t);
}

void Menu::addSubMenu(Menu * m, int i){
    this->_subMenus[i-1]=m;
}

void Menu::set(const char * tag, const char * question, int i){
    string t = tag;
    string q = question;
    string a = "";
    this->addTag(t);
    this->addQuestion(q);
    this->addAnswer(a);
    this->_questionByField.push_back(i);   
}

string Menu::get(string s){
    unsigned int i =0;
    while(i<this->_questionTags.size()){
        if(this->_questionTags[i] == s){
            return this->_answers[i];
        }
        ++i;
    }
    for(unsigned int i=0; i<this->_subMenus.size();++i){
        if(this->_subMenus[i]){
            if(this->_subMenus[i]->get(s) != ""){
                return this->_subMenus[i]->get(s);
            }
        }
    }
    string e = "";
    return e;
}

string Menu::get(const char * c){
    string s = c;
    return get(s);
}

void Menu::display(){
    cout<<"___________________________________________________"<<endl;
    cout<<endl;
    cout<<this->getTitle()<<endl;
    cout<<"___________________________________________________"<<endl;
    for(unsigned int i=0; i<this->_fields.size();++i){
        cout<<"\t"<<i+1<<". "<<this->_fields[i]<<endl;
    }
    cout<<"___________________________________________________"<<endl;
    cout<<"___________________________________________________"<<endl;
    cout<<"Enter your choice : "<<endl;
}

void Menu::ask(vector<string> * ans){
    this->display();
    this->_ans.clear();
    string message="0";
    if(!ans){
        ans = &(this->_ans);
    }
    while(atoi(message.c_str())==0 || atoi(message.c_str())> (int)this->_fields.size()){
        getline(cin,message);
    }
    ans->push_back(message);
    int number = atoi(message.c_str());
    string buffer;
    for(unsigned int i =0; i< this->_questionByField.size(); ++i){
        if(this->_questionByField[i] == number || this->_questionByField[i]==0){
            cout<<"\t*"<<this->_subQuestions[i]<<endl;
            cout<<"\t";
            getline(cin, buffer);
            this->_answers[i]=buffer;
        }
    }
    if(this->_subMenus[number-1]){
        this->_subMenus[number-1]->display();
        this->_subMenus[number-1]->ask(ans);
    }
}

string Menu::getAnswer(unsigned int i){
    if(i<this->_ans.size()){
        return this->_ans[i];
    }
    string message="0";
    return message;
}

string Menu::getTitle(){
    return this->_title;
}

void Menu::setTitle(string t){
    this->_title=t;
}

void Menu::setTitle(const char * t){
    this->_title=t;
}
