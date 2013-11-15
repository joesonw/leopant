#ifndef MMO_SERVER_EVENT
#define MMO_SERVER_EVENT
#include "packet.h"


class Session;
class Event {
protected:
	AnyArray _args;
	Session* _session;
public:
	enum {
		UserJoined,
		UserLeft,
		UserMessage
	};
	Event(Session* s):_session(s) {}
	Event(AnyArray a,Session* s):_args(a),_session(s) {}
	virtual ~Event() {}
	AnyArray args() {return _args;}
	Session* session() {return  _session;}
	virtual int type()=0;
};
class UserJoined:public Event {
public:
	UserJoined(Session* s):Event(s) {}
	~UserJoined() {}
	int type() {return Event::UserJoined;}
};
class UserLeft:public Event {
public:
	UserLeft(Session* s):Event(s) {}
	~UserLeft() {}
	int type() {return Event::UserLeft;}
};
class UserMessage:public Event {
public:
	UserMessage(AnyArray a,Session* s):Event(a,s) {}
	~UserMessage() {}
	int type() {return Event::UserMessage;}
};






#endif
