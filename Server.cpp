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


