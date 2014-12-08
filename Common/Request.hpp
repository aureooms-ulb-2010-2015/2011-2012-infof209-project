#ifndef REQUEST
#define REQUEST

#include <string>
#include <vector>

class GenericCommunicator;

using namespace std;    

class Request{
    private:
        string _type;
        string _name;
        string _commands;
        GenericCommunicator * _gc;
        vector<string> _attributes;
    public:
        Request(GenericCommunicator *);
        
        virtual bool isEmpty();
        virtual void clear();
        virtual void parseString(string);
        virtual unsigned int loadNextCommand();
        virtual string addSlashes(string);
        virtual string slashChar(string ,char);
        virtual void makeRequest(string, string);
        virtual void makeRequest(const char *, const char *);
        virtual void makeRequest(const char *, string);
        virtual void flush();
        
        //Requetes synchrones
        virtual void getRequest(string name, string attr);
        virtual void set(string, string=".");
        virtual void set(const char * ,string=".");
        virtual void set(const char *, const char *);
        virtual void set(const char *, int);
        virtual void set(string, int);
        
        virtual string get(string, string str = ".");
        virtual string get(const char *, string str = ".");
        virtual string get(const char *, const char *);
        virtual int getInt(string, string str = ".");
        virtual int getInt(const char *, string str = ".");
        virtual int getInt(const char *, const char *);
        virtual bool getBool(string, string str = ".");
        virtual bool getBool(const char *, string str = ".");
        virtual bool getBool(const char *, const char *);
        
        //Getters
        virtual string getType(){return _type;}
        virtual string getName(){return _name;}
        virtual string getCommands(){return _commands;}
        virtual string getSequence();
        virtual GenericCommunicator * getCommunicator(){return _gc;}
        virtual vector<string> getAttributes(){return _attributes;}
        
        //Setters
        virtual void setCommunicator(GenericCommunicator * gc){_gc = gc;}
        virtual void setCommands(string c){_commands = c;}
        virtual void setType(string t);
        virtual void setType(const char *);
        virtual void setName(string n);
        virtual void setName(const char *);
        virtual void addAttribute(string);
        virtual void addAttribute(int);
        virtual void addAttribute(const char *);
        
};

#endif
