#include "session.h"
#include "Server.h"
void Session::headHandler(boost::system::error_code ec,char* head) {
	if (ec==error::eof) {
		std::cout<<_socket->remote_endpoint().address()<<" disconnected"<<std::endl;
		_server->remove(this);
		return;
	}	
	std::istringstream iss(head);
	int size;
	iss>>std::hex>>size;
	char *msg = new char[size];
	async_read(*_socket,buffer(msg,size),boost::bind(&Session::bodyHandler,this,placeholders::error,msg));
}
void Session::bodyHandler(boost::system::error_code ec,char *body) {
	std::string msg=body;
	AnyArray ary=Packet::unpack(body);
	int cmd=ary.readInt("cmd");
	switch (cmd) {
		case Request::PRINT_TO_SERVER:
			_server->push_request(new PrintToServer(ary,this));
			break;
	}
	char * head=new char[8];
	async_read(*_socket,buffer(head,8),boost::bind(&Session::headHandler,this,placeholders::error,head));
}
void Session::start() {
	char * head=new char[8];
	AnyArray args;
	AnyArray argItem;
	args.write("item1",string("message1"));
	args.write("item2",2);
	args.write("item3",3.3);
	argItem.write("item1",string("message2"));
	argItem.write("item2",2);
	argItem.write("item3",3.3);
	args.write("array",argItem);
	Session::write(args);	
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
