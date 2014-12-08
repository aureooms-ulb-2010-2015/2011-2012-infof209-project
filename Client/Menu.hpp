#ifndef CLIENT_MENU
#define CLIENT_MENU

#include <string>
#include <vector>
#include <iostream> 

using namespace std;
  
    class Menu{
        private:
            vector<string> _fields;
            vector<Menu *> _subMenus;
            vector<string> _subQuestions;
            vector<string> _questionTags;
            vector<string> _answers;
            vector<int>    _questionByField;
            vector<string> _ans;
            string _title;
        public:
            Menu();
            Menu(string);
            Menu(const char *);
            virtual void addField(string);
            virtual void addField(const char *);
            virtual void addQuestion(string);
            virtual void addAnswer(string);
            virtual void addTag(string);
            virtual void addSubMenu(Menu *, int);
            virtual string get(string);
            virtual string get(const char *);
            virtual string getAnswer(unsigned int i=0);
            virtual void set(const char * tag, const char * question, int);
            virtual void display();
            virtual void ask(vector<string> * ans =NULL);
            virtual void setTitle(string);
            virtual void setTitle(const char *);   
        protected:
            virtual string getTitle();
    };

#endif
