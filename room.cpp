#include "room.h"
#include "session.h"

Room::Room(string name,unsigned cap):_capacity(cap),_size(0),_name(name) {
}
Room::~Room() {

}
void Room::addUser(User* u) {
	_users.push_back(u);
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
