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
		USER_LOGIN,
		JOIN_ROOM,
		PRINT_TO_SOCKET,
		USER_DC
	};
};
class PrintToServer:public Request {
public:
	PrintToServer(AnyArray a,Session* s):Request(a,s) {}
	~PrintToServer() {}
	int type() {return Request::PRINT_TO_SERVER;}
};
class UserLogin:public Request {
public:
	UserLogin(AnyArray a,Session* s):Request(a,s) {}
	~UserLogin() {}	
	int type() {return Request::USER_LOGIN;}
};
class UserDisconnected:public Request {
public:
	UserDisconnected(Session* s):Request(s) {}
	~UserDisconnected() {}
	int verbose() {return Request::USER_DC;}
};

//-----from server-to-client
class PrintToSocket:public Request {
public:
	PrintToSocket(AnyArray a,Session* s):Request(a,s) {}
	~PrintToSocket() {}	
	int type() {return Request::PRINT_TO_SOCKET;}
};



#endif
