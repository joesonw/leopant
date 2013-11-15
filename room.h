#ifndef MMO_SERVER_ROOM
#define MMO_SERVER_ROOM
#include "user.h"
#include <vector>
#include <map>
#include <string>
#include "event.h"
#include "request.h"

class Server;
class UserVariable;
class Room;

using namespace std;
class Room {
protected:
	vector<User*> _users;
	vector<Session*> _sessions;
	unsigned _capacity;
	unsigned _size;
	string _id;
	string _name;	
	//map<User*,OneToOne<string,void*> > _roomUserVariables;
	//OneToOne<string,void*> _roomVariables;

	int loggedin(Session* s);
public:
	Room(string,unsigned);
	~Room();
	void addUser(User*);
	int hasUser(User*);
	User* getUserById(int);
	User* getUserByName(string);
	vector<User*> getAllUsers() {return _users;}
	//-----------------------------------
	virtual void start()=0;
	virtual void requestHandler(Request*)=0;	
	virtual void eventHandler(Event*)=0;
	//------------------------------------
	unsigned capacity() {return _capacity;}
	unsigned size() {return _size;}
	string getId() {return _id;}
	string getName() {return _name;}
	bool isEmpty() {return _size==0;}
	bool isFull() {return _capacity==_size;}

};


#endif /*MMO_SERVER_ROOM*/
