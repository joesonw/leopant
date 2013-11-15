OBJ = Server.o session.o room.o
server: main.cpp ${OBJ}
	g++ main.cpp ${OBJ} -lboost_system -lboost_thread  -o server
Server.o: Server.cpp Server.h room.h request.h session.h packet.h event.h
	g++ -Wall -c Server.cpp
session.o: session.cpp session.h Server.h user.h request.h packet.h
	g++ -Wall -c session.cpp
room.o: room.cpp room.h user.h event.h request.h session.h
	g++ -Wall -c room.cpp
clean:
	rm -rf $(OBJ) server
