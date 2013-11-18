#include "session.h"
#include "Server.h"
void Session::headHandler(boost::system::error_code ec,char* head) {
	if (!_running) {
		return;
	}
	if (ec || !head) {
		std::cout<<_socket->remote_endpoint().address()<<" disconnected"<<std::endl;
		if (_room!=NULL) {
			_room->eventHandler(new event::UserLeft(this));
		}
		remove(this);
		return;
	} else {
		std::istringstream iss(head);
		int size;
		iss>>std::hex>>size;
		char *msg = new char[size];
		async_read(*_socket,buffer(msg,size),boost::bind(&Session::bodyHandler,this,placeholders::error,msg,size));
	}
}
void Session::bodyHandler(boost::system::error_code ec,char *body,int size) {
	if (!_running) {
		return;
	}
	if (ec || !body) {
		std::cout<<_socket->remote_endpoint().address()<<" disconnected"<<std::endl;
		if (_room!=NULL)
			_room->eventHandler(new event::UserLeft(this));
		remove(this);
		return;
	} else {
		std::string msg(body,size);
		AnyArray args=Packet::unpack(msg);
		int cmd=-1;
		if (args.hasKey("request_type")) {
			cmd=args.readInt("request_type");
		}
		switch (cmd) {
			case Request::PRINT_TO_SERVER:
				std::cout<<args.readString("message")<<std::endl;
				quit();
				remove(this);
				break;
			case Request::USER_JOIN_ROOM:
				for (unsigned i=0;i<rooms->size();i++) {
					if (rooms->at(i)->getName()==args.readString("room")) {
						_room=rooms->at(i);
						rooms->at(i)->eventHandler(new event::UserJoined(this));
					}
				}		
				break;
			case Request::USER_MESSAGE:
				if (args.readString("target")=="room") {
					for (unsigned i=0;i<rooms->size();i++) {
						if (this->rooms->at(i)->getName()==args.readString("room")) {
							if (rooms->at(i)->hasSession(this)) {
								rooms->at(i)->eventHandler(new event::UserMessage(args,this));
							}
						}
					}
				}
				break;
		}
		char * head=new char[8];
		async_read(*_socket,buffer(head,8),boost::bind(&Session::headHandler,this,placeholders::error,head));
	}
}
void Session::start() {
	_running=true;	
	char * head=new char[8];
	async_read(*_socket,buffer(head,8),boost::bind(&Session::headHandler,this,placeholders::error,head));
}
void Session::write(AnyArray p) {
	using namespace boost::asio;
	std::string bufs=Packet::pack(p);
	boost::system::error_code ec;
	ostringstream oss;
	oss<<std::setw(Packet::header_length)<<std::hex<<bufs.length();
	std::string header=oss.str();
	boost::asio::write(*_socket,buffer(header,8),ec);	
	boost::asio::write(*_socket,buffer(bufs,bufs.length()),ec);
}
void Session::quit() {
		string ip=_socket->remote_endpoint().address().to_string();
		_running=false;
		_socket->close();
		if (_room!=NULL) {
			_room->remove(this);
		}
		std::cout<<ip<<" has been kicked"<<std::endl;
	}
