#ifndef MMO_SERVER_ROOM
#define MMO_SERVER_ROOM
#include "user.h"
#include "event.h"
#include "application.h"
#include "onetoone.h"
#include <vector>
#include <map>
#include <string>

class Server;
class UserVariable;
class Room;

using namespace std;
class Room {
private:
	Server* _server;	
	vector<User*> _users;
	unsigned _capacity;
	unsigned _size;
	string _id;
	string _name;	
	void _notifyAll(Event);
	map<User*,UserVariable> _roomUserVariables;
public:
	Room(string,unsigned);
	~Room();
	void addUser(User*);
	int hasUser(User*);
	User* getUserById(int);
	User* getUserByName(string);
	vector<User*> getAllUsers() {return _users;}
	//-----------------------------------
	//------------------------------------
	unsigned capacity() {return _capacity;}
	unsigned size() {return _size;}
	string getId() {return _id;}
	string getName() {return _name;}
	bool isEmpty() {return _size==0;}
	bool isFull() {return _capacity==_size;}

};
class UserVariable {
public:
	UserVariable() {}
	~UserVariable() {}
};


#endif /*MMO_SERVER_ROOM*/
