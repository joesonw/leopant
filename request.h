#ifndef MMO_SERVER_REQUEST
#define MMO_SERVER_REQUEST
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "packet.h"
#include "user.h"

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class Session;

class Request {
public:
	Request() {}
	virtual	~Request() {}
	virtual void run()=0;
};
class UnknownRequest:public Request {
public:
	UnknownRequest() {}
	~UnknownRequest() {}
	void run() {
		std::cout<<"\t***Error: unknown request***"<<std::endl;
	}
};
class WriteToScreen:public Request {
private:
	std::string msg;
public:
	WriteToScreen(std::string m):msg(m) {}
	~WriteToScreen() {}
	void run() {
		std::cout<<msg<<std::endl;
	}
};

class UserLogin:public Request {
private:
	std::string msg;
	Session* s;
public:
	UserLogin(std::string m,Session* session):msg(m),s(session) {}
	~UserLogin() {}	
	void run();	
};
class JoinRoom:public Request {
private:
	std::string msg;
	Session* session;
public:
	JoinRoom(std::string m,Session* s):msg(m),session(s) {}
	~JoinRoom() {}
	void run();

};
//-----from server-to-client
class PrintToSocket:public Request {
private:
	std::string msg;
	Session* s;
public:
	PrintToSocket(string m,Session* session):msg(m),s(session) {}
	~PrintToSocket() {}	
	void run();
};



#endif
