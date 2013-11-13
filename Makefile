OBJ = Server.o session.o request.o
server: main.cpp ${OBJ}
	g++ main.cpp ${OBJ} -lboost_system -lboost_thread  -o server
Server.o: Server.cpp Server.h
	g++ -Wall -c Server.cpp
session.o: session.cpp session.h
	g++ -Wall -c session.cpp
request.o: request.cpp request.h
	g++ -Wall -c request.cpp
clean:
	rm -rf Server.o session.o server
