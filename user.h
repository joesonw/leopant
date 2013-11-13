#ifndef MMO_SERVER_USER
#define MMO_SERVER_USER
#include "event.h"
#include <string>

class User;
class BuddyList {
public:
	BuddyList() {}
	~BuddyList() {}
};

using namespace std;
class User {
private:
	BuddyList _buddyList;
	int _id;		
	string _name;
public:
	User(int id,string name):_id(id),_name(name) {}
	~User() {}
	void dispatch(Event) {}
	int getId() {return _id;}
	string getName() {return _name;}
};




#endif /*MMO_SERVER_USER*/
