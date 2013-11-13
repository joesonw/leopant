#include "Server.h"
#include <iostream>
#include "session.h"
using namespace std;
int main(int argc,char *argv[]) {
	Server s(atoi(argv[1]));
	s.start();
}
