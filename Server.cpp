#include "Server.h"
#include "session.h"

void Server::start_accept() {
	//_ios.run();
	ip::tcp::socket *s=new ip::tcp::socket(_ios);
	socket_ptr sp(s);	
	acceptor.async_accept(*sp,boost::bind(&Server::accept_handler,this,sp,placeholders::error));
}

void Server::accept_handler(socket_ptr s,boost::system::error_code ec) {
	Session* ss=new Session(this,s);
	sessions.push_back(ss);
	std::cout<<ss->socket()->remote_endpoint().address()<<" connected"<<std::endl;
	if (!ec) {
		ss->start();
	}
//	_ios.reset();
	start_accept();
}
void Server::user_join_room(Session* s,string name) {
		for (unsigned i=0;i<rooms.size();i++) {
			if (rooms[i]->getName()==name) {
				rooms[i]->eventHandler(new UserJoined(s));
				std::cout<<s->socket()->remote_endpoint().address()<<" joined room:"<<name<<std::endl;
			}	
		}
}
void Server::requests_handler() {
	for (;;) {
			boost::unique_lock<boost::mutex> lock(requests_mutex);
			while(requests.empty()) {
				requests_cond.wait(lock);
			}
			Request* r=requests.front();
			requests.pop();
			switch(r->type()) {
				case Request::PRINT_TO_SERVER:
					std::cout<<r->args().readString("message")<<std::endl;
					break;
			}
		}
}
