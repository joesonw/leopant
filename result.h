#ifndef MMO_SERVER_RESULT
#define MMO_SERVER_RESULT
#include <boost/asio.hpp>
#include <queue>

using namespace boost::asio;

class Result {
public:
	Result() {}
	virtual ~Result() {}
	virtual std::queue<const_buffer> get()=0;
};

class Echo:public Result {
private:
	char * msg;
public:
	Echo(char * m):msg(m) {}
	std::queue<const_buffer> get() {}	
};

#endif
