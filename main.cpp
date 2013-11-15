#include "Server.h"
#include <iostream>
#include <algorithm>
#include "session.h"
using namespace std;
/**
class Hall: public Room {

public:
	Hall(string a,int b):Room(a,b) {}
	~Hall() {}

	void requestHandler(Request* r) {

	}
	void eventHandler(Event* e) {
		switch (e->type()) {
			case Event::UserJoined:
				if (loggedin(e->session())) {
					Packet p;
					p.writeString("event","USER_UPDATE_ADD");
					AnyArray info;
					info.push("name",e->session()->user()->getName());
					p.writeVector("user",info);
					for (unsigned i=0;i<_sessions.size();i++) {
						_server->push_request(new PrintToSocket(p,_sessions[i]));
					}
					_sessions.push_back(e->session());
				}
				break;
			case Event::UserLeft:
				if (loggedin(e->session())) {
					Packet p;
					p.writeString("event","USER_UPDATE_LEAVE");
					AnyArray info;
					info.push("name",e->session()->user()->getName());
					p.writeVector("user",info);
					_sessions.erase(std::find(_sessions.begin(),_sessions.end(),e->session()));
					for (unsigned i=0;i<_sessions.size();i++) {
						_server->push_request(new PrintToSocket(p,_sessions[i]));
					}
				}
				break;
			case Event::UserMessage:
				Packet args=e->args();
				string type=args.readString("type");
				if (type=="BROADCAST") {
					if (loggedin(e->session())) {
						Packet p;
						p.writeString("event","BROADCAST");
						p.writeString("name",e->session()->user()->getName());
						p.writeString("message",args.readString("message"));
						for (unsigned i=0;i<_sessions.size();i++) {
							_server->push_request(new PrintToSocket(p,_sessions[i]));
						}						
					}
				}
		}
	}

};
**/

int main(int argc,char *argv[]) {
	Server s(atoi(argv[1]));
	s.start();
}
