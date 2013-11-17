#include "room.h"
#include "session.h"

Room::Room(string name,unsigned cap):_capacity(cap),_size(0),_name(name) {
}
Room::~Room() {}
int Room::hasSession(Session* s) {
	for (unsigned i=0;i<_sessions.size();i++) {
		if (_sessions[i]==s)
			return 1;
	}
	return 0;
}
int Room::hasUser(User* u) { 
	for (vector<User*>::iterator i=_users.begin();i!=_users.end();i++) {
		if (*i==u)
			return 1;
	}
	return 0;
}

User* Room::getUserById(int id) {
	for (vector<User*>::iterator i=_users.begin();i!=_users.end();i++) {
		if ((*i)->getId()==id)
			return *i;
	}
	return 0;
}

User* Room::getUserByName(string name) {
	for (vector<User*>::iterator i=_users.begin();i!=_users.end();i++) {
		if ((*i)->getName()==name)
			return *i;
	}
	return 0;
}
int Room::loggedin(Session*s ) {
	return s->user()==0;
}
