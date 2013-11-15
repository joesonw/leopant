#ifndef MMO_SERVER_USER
#define MMO_SERVER_USER
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
	User(string name):_name(name) {}
	~User() {}
	int getId() {return _id;}
	string getName() {return _name;}
};




#endif /*MMO_SERVER_USER*/
