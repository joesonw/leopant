#ifndef MMO_SERVER_REQUEST
#define MMO_SERVER_REQUEST
#include <iostream>
#include <iomanip>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "packet.h"
#include "user.h"

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
using std::string;
class Session;

class Request {
protected:
	AnyArray _args;
	Session* _session;
public:
	Request(AnyArray a,Session* s):_args(a),_session(s) {}
	Request(Session* s):_session(s) {}
	AnyArray args() {return _args;}
	Session* session() {return _session;}
	virtual	~Request() {}
	virtual int type()=0;
	enum {
		PRINT_TO_SERVER,
		USER_CONNECT,
		USER_DISCONNECT,
		USER_JOIN_ROOM,
		USER_MESSAGE,
		PRINT_TO_SOCKET
	};
};
namespace request{
class PrintToServer:public Request {
public:
	PrintToServer(AnyArray a,Session* s):Request(a,s) {}
	~PrintToServer() {}
	int type() {return Request::PRINT_TO_SERVER;}
};
class UserConnect:public Request {
public:
	UserConnect(Session* s):Request(s) {}
	~UserConnect() {}	
	int type() {return Request::USER_CONNECT;}
};
class UserDisconnect:public Request {
public:
	UserDisconnect(Session* s):Request(s) {}
	~UserDisconnect() {}
	int type() {return Request::USER_DISCONNECT;}
};
class UserJoinRoom:public Request {
public:
	UserJoinRoom(AnyArray a,Session* s):Request(a,s){}
	~UserJoinRoom() {}
	int type() {return Request::USER_JOIN_ROOM;}
};
class UserMessage:public Request {
public:
	UserMessage(AnyArray a,Session *s):Request(a,s) {}
	~UserMessage() {}
	int type() {return Request::USER_MESSAGE;}
};
class PrintToSocket:public Request {
public:
	PrintToSocket(AnyArray a,Session* s):Request(a,s) {}
	~PrintToSocket() {}	
	int type() {return Request::PRINT_TO_SOCKET;}
};
}



#endif
