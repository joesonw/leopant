#ifndef MMO_SERVER_SESSION
#define MMO_SERVER_SESSION
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <iomanip>
#include <map>
#include "user.h"
#include "request.h"

class Server;

using namespace boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
class Session {
private:
	Server* _server;
	socket_ptr _socket;
	User* _user;	
	void bodyHandler(boost::system::error_code ec,char *body);
	void headHandler(boost::system::error_code ec,char* head);
public:
	bool reading;
	Session(Server* server,socket_ptr s):_server(server),_socket(s) {}
	~Session() {}
	socket_ptr socket() {return _socket;}
	User* user() {return _user;}
	void setUser(User *u) {_user=u;}
	void write(AnyArray);
	void start();
};



#endif
