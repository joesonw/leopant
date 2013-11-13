#ifndef MMO_SERVER_MAIN
#define MMO_SERVER_MAIN
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>
#include "request.h"

class Session;

using namespace boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
class Server {
private:
	io_service	_ios;
	int _port;
	ip::tcp::endpoint endpoint;	
	ip::tcp::acceptor acceptor;


	boost::mutex requests_mutex;
	boost::condition_variable requests_cond;


	std::vector<bool> reading;


	std::vector<Session*> sessions;
	std::queue<Request*> requests;
	
	void start_accept();
	void accept_handler(socket_ptr s,boost::system::error_code ec);
	void requests_handler() {
		for (;;) {
			boost::unique_lock<boost::mutex> lock(requests_mutex);
			while(requests.empty()) {
				requests_cond.wait(lock);
			}
			Request* r=requests.front();
			requests.pop();
			r->run();
		}
	}

public:
	Server(int port):_port(port),endpoint(ip::tcp::v4(),port),acceptor(_ios,endpoint) {
	}
	void start() {
		std::cout<<"Server start at port "<<_port<<std::endl;
		boost::thread t1(boost::bind(&Server::requests_handler,this));
		start_accept();
		_ios.run();
	}
	void remove(Session* s) {
		sessions.erase(std::find(sessions.begin(),sessions.end(),s));
	}
	void stop() {
	}
	void push_request(Request* r) {
		boost::unique_lock<boost::mutex> lock(requests_mutex);
		requests.push(r);
		requests_cond.notify_one();
	}
};

#endif
