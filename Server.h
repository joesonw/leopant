#ifndef MMO_SERVER_MAIN #define MMO_SERVER_MAIN
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>
#include "request.h"
#include "room.h"

class Session;

using namespace boost::asio;
using std::vector;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<std::vector<Room*> > room_ptr;
class Server {
private:
	io_service	_ios;
	int _port;
	ip::tcp::endpoint endpoint;	
	ip::tcp::acceptor acceptor;


	boost::mutex requests_mutex;
	boost::condition_variable requests_cond;


	std::vector<Session*> sessions;
	std::vector<Room*> rooms;
	std::queue<Request*> requests;
	
	void start_accept();
	void accept_handler(socket_ptr s,boost::system::error_code ec);
	void requests_handler();
public:
	Server(int port):_port(port),endpoint(ip::tcp::v4(),port),acceptor(_ios,endpoint) {
	}
	void start() {
		std::cout<<"Server start at port "<<_port<<std::endl;
		for (unsigned i=0;i<rooms.size();i++)
			rooms[i]->start();
		//boost::thread t1(boost::bind(&Server::requests_handler,this));
		start_accept();
		_ios.run();
	}
	void remove(Session* s) {
		sessions.erase(std::find(sessions.begin(),sessions.end(),s));
	}
	void stop() {}
	void join_room(Room* r) {
		r->push_request=boost::bind(&Server::push_request,this,_1);
		rooms.push_back(r);
	}
	void user_join_room(Session* s,string name);
	void push_request(Request* r) {
		boost::unique_lock<boost::mutex> lock(requests_mutex);
		requests.push(r);
		requests_cond.notify_one();
	}
};

#endif
