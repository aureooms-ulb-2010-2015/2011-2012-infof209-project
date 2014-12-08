#include "../h/Chat_server.h"
#include "../../Library/Socket/SocketException.h"


vector<string> Split_s(string start,string token){
	vector<string> result;
	string buffer = start;

	string::size_type token_index = buffer.find(token);
	
	while(token_index != string::npos){
		result.push_back(buffer.substr(0, token_index));
		buffer = buffer.substr(token_index + 1);
		token_index = buffer.find(token);
	}
	
	result.push_back(buffer);

	return result;
}

Chat_server::~Chat_server(){

	vector<Chat_channel*>::iterator iterator;
    
	for(iterator = this->channels.begin(); iterator!=this->channels.end(); ++iterator){
		delete *iterator;
	}
}

Chat_server& Chat_server::receive_client_connection_to_channel() {
	return *this;
}

map<string,string> Chat_server::decode(string encoded){
	map<string,string> result;
	vector<string> pairs = Split_s(encoded,"&");
	vector<string>::iterator iterator;
	for (iterator=pairs.begin(); iterator!=pairs.end(); ++iterator){
		string couple = *iterator;
		string attribute = Split_s(couple,"=")[0];
		string value =  Split_s(couple,"=")[1];
		result.insert(pair<string,string>(attribute,value));
	}
	return result;
}


Chat_server& Chat_server::create_channel(string id){
	this->channels.push_back(new Chat_channel(id));
	return *this;
}

Chat_server& Chat_server::add_client_to_channel(Chat_client_manager *client, string id) {
	this->get_channel(id)->add_client(client);
	return *this;
}

Chat_server& Chat_server::remove_client_from_channel(Chat_client_manager &client, string id) {
	this->get_channel(id)->remove_client(client);
	return *this;
}

void* Chat_server::run(void*){
	try{
		cout << "1.0 - Create the accept socket."<< endl;
		ServerSocket server(30000);
		cout << "1.1 - Socket created." << endl;
		while ( true ){
	
			
			string data;
			cout << "2.0 - Create socket for new client."<< endl;
			ServerSocket *new_sock = new ServerSocket();
			
			cout << "2.1 - Waiting for connection."<< endl;
			server.accept(*new_sock);
			cout << "2.2 - New client connecting."<< endl;
			
			cout << "2.3 - Waiting for configs."<< endl;
			*new_sock >> data;
			cout << "2.4 - Data received '"<< data << "'." << endl;
			
			cout << "3.0 - Decoding.";
			map<string,string> pairs = this->decode(data);
			cout << ".";
			string channel_id = pairs.find("channel")->second;
			cout << ".";
			string pseudo = pairs.find("pseudo")->second;
			cout << endl;
			cout << "3.1 - Decoded."<< endl;
			
			cout << "4.0 - Make sure channel exists."<< endl;
			if(!this->channel_exists(channel_id)){
				cout << "4.1 - Doesn't exists '"<< channel_id << "'."<< endl;
				this->create_channel(channel_id);
			}
			else{
				cout << "4.1 - Already exists."<< endl;
			}
			cout << "5.0 - Manager creation."<< endl;
			
			

			cout << "5.0.1 - Sender socket creation."<< endl;
			ServerSocket *s_sock = new ServerSocket();	
			cout << "      - Waiting for connection."<< endl;
			server.accept(*s_sock);
			
			cout << "5.0.2 - Receiver socket creation."<< endl;
			ServerSocket *r_sock = new ServerSocket();
			cout << "      - Waiting for connection."<< endl;
			server.accept(*r_sock);
			

			
			Chat_client_manager *client = new Chat_client_manager(pseudo,this->get_channel(channel_id),*new_sock,*r_sock,*s_sock);
			cout << "5.0.3 - Manager created."<< endl;
			
			cout << "5.1 - Add client to channel." << endl;
			this->add_client_to_channel(client,channel_id);
			cout << "End." << endl;
			
		}
	}
	catch ( SocketException& e ){
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}


Chat_server& Chat_server::remove_channel(string id) {
	
	vector<Chat_channel*>::iterator iterator;
    
	for(iterator = this->channels.begin(); iterator!=this->channels.end(); ++iterator){
		if ((*iterator)->is(id)){
			this->channels.erase(iterator);
			break;
		}
	}
	return *this;
	
}

bool Chat_server::channel_exists(string id) {
	
	vector<Chat_channel*>::iterator iterator;
    
	for(iterator = this->channels.begin(); iterator!=this->channels.end(); ++iterator){
		if ((*iterator)->is(id)){
			return true;
		}
	}
	return false;
}


Chat_channel* Chat_server::get_channel(string id) {
	
	
	unsigned int index = 0;
	while (index < this->channels.size()){
		if (this->channels[index]->is(id)){
			return this->channels[index];
		}
		index++;
	}
	return this->channels[index];

}
