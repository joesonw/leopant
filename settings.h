#ifndef MMO_SERVER_SETTINGS
#define MMO_SERVER_SETTINGS

#include <boost/asio.hpp>

/***connection type***/
typedef boost::asio::ip::tcp conn_proc;
namespace conn{
	typedef boost::asio::ip::tcp protocol
};


#endif
