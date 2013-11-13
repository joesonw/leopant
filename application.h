#ifndef MMO_SERVER_APPLICATION
#define MMO_SERVER_APPLICATION
#include "request.h"
#include "user.h"

class Application {
public:
	Application() {}
	virtual ~Application()=0;
	virtual init()=0;
	virtual requestHandler(User*,Request*)=0;
	virtual eventHandler(User*,Request*)=0;
};



#endif
