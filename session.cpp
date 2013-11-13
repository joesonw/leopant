#include "session.h"
#include "Server.h"
void Session::headHandler(boost::system::error_code ec,char* head) {
	if (ec==error::eof) {
		std::cout<<_socket->remote_endpoint().address()<<" disconnected"<<std::endl;
		_server->remove(this);
		return;
	}	
	std::istringstream iss(head);
	int size;
	iss>>std::hex>>size;
	char *msg = new char[size];
	async_read(*_socket,buffer(msg,size),boost::bind(&Session::bodyHandler,this,placeholders::error,msg));
}
void Session::bodyHandler(boost::system::error_code ec,char *body) {
	std::string msg=body;
	char * cmdc=new char[2];
	cmdc[0]=msg[0];
	cmdc[1]=msg[1];
	std::string cmd=cmdc;
	msg.erase(0,2);
	if (cmd=="00") {
		_server->push_request(new WriteToScreen(msg));
	} else if (cmd=="01") {
		_server->push_request(new UserLogin(msg,this));
	}

	char * head=new char[8];
	async_read(*_socket,buffer(head,8),boost::bind(&Session::headHandler,this,placeholders::error,head));
}
void Session::start() {
	char * head=new char[8];
	_server->push_request(new PrintToSocket("welcome",this));
	async_read(*_socket,buffer(head,8),boost::bind(&Session::headHandler,this,placeholders::error,head));
}
