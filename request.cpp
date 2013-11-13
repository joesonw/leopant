#include "request.h"
#include "session.h"
#include <queue>

void UserLogin::run() {
	if (msg=="djwong") {
		User* u=new User(1,"qiaosen huang");
		s->setUser(u);
		std::cout<<"welcome, "<<u->getName()<<std::endl;
	} else {
		std::cout<<"login refused"<<std::endl;
	}
	
}
void PrintToSocket::run() {
	using namespace boost::asio;
	Packet p;
	p.writeString(msg);
	std::queue<Buf> bufs=p.getBuffers();
	boost::system::error_code ec;
	while(!bufs.empty()) {
		Buf b=bufs.front();
		write(*s->socket(),buffer(b.msg,b.length),ec);
		bufs.pop();
	}
}
void JoinRoom::run() {
	
}
