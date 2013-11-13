#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{
        using namespace boost::asio;
        boost::system::error_code ec;
		try {
        io_service iosev;
        ip::tcp::socket socket(iosev);
        ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), atoi(argv[1]));
        socket.connect(ep,ec);
		
		while(1) {
			std::string msg;
			std::cin>>msg;
			std::ostringstream ss;
			ss<<std::setw(8)<<std::hex<<msg.length();
			std::string header=ss.str();
			std::cout<<header<<std::endl;
			socket.write_some(boost::asio::buffer(header,8),ec);
			socket.write_some(boost::asio::buffer(msg,msg.length()),ec);
			if(ec)
        	{
                std::cout << boost::system::system_error(ec).what() << std::endl;
                return -1;
        	}
		}
		} catch (std::exception &e) {
			std::cout<<e.what()<<std::endl;
		}	
        

        return 0;
}
