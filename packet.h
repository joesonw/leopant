#ifndef MMO_SERVER_PACKET
#define MMO_SERVER_PACKET
#include <boost/asio.hpp>
#include <queue>
#include <iomanip>
#include <sstream>
#include <string>
struct Buf {
	const char * msg;
	int length;
	Buf(const char * m,int l):msg(m),length(l) {}
};

struct Packet {
	enum { header_length=8};
	enum { type_length=1};
	std::queue<Buf> buffers;
	Packet() {}
	~Packet() {
	}	
	void writeString(std::string str) {
		std::ostringstream oss;
		oss<<std::setw(header_length)<<std::hex<<str.length();
		buffers.push(Buf(oss.str().c_str(),8));
		buffers.push(Buf(str.c_str(),str.length()));
	}
	std::queue<Buf> getBuffers() {return buffers;}
	
	
};
#endif
