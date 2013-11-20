#include "Server.h"
#include <iostream>
#include <algorithm>
#include "session.h"
using namespace std;
class Hall: public Room {

public:
	Hall(string a,int b):Room(a,b) {}
	~Hall() {}
	void eventHandler(Event* e) {
		switch (e->type()) {
			case Event::UserJoined: {
				_sessions.push_back(e->session());
				break;
			}
			case Event::UserLeft: {
				AnyArray p;
				p.write("message",string("left"));
				_sessions.erase(std::find(_sessions.begin(),_sessions.end(),e->session()));
				for (unsigned i=0;i<_sessions.size();i++) {
					_sessions[i]->write(p);
				}
				break;
			}
			case Event::UserMessage: {
				AnyArray args=e->args();
				AnyArray p;	
				p.write("event_type",2);
				p.write("message",args.readString("message"));
				for (unsigned i=0;i<_sessions.size();i++) {
					if (_sessions[i]!=e->session())	
						_sessions[i]->write(p);
				}
				break;
			}
		}
	}
	void start() {}

};

int main(int argc,char *argv[]) {
	Server s(atoi(argv[1]));
	s.join_room(new Hall("Hall",0));
	s.start();
}
