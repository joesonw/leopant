#ifndef MMO_SERVER_SESSION
#define MMO_SERVER_SESSION
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/any.hpp>
#include <iomanip>
#include <map>
#include <vector>
#include "user.h"
#include "request.h"

class Server;
class Room;

using namespace boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr< std::vector<Room*> > rooms_ptr;
class Session {
private:
	Server* _server;
	Room* _room;
	socket_ptr _socket;
	User* _user;	
	bool _running;
	void bodyHandler(boost::system::error_code ec,char *body,int size);
	void headHandler(boost::system::error_code ec,char* head);
public:
	boost::function<void(Session*)> remove;
	rooms_ptr rooms;	
	bool reading;
	Session(Server* server,socket_ptr s):_server(server),_socket(s) {
		_room=0;
		_user=0;
		_running=false;
	}
	~Session() {}
	socket_ptr socket() {return _socket;}
	User* user() {return _user;}
	Room* room() {return _room;}
	void setRoom(Room* r) {_room=r;}
	void setUser(User *u) {_user=u;}
	void write(AnyArray);
	void start();
	void quit();	
};



#endif
