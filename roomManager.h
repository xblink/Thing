#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <vector>

struct Room {
	int roomID;
};

class RoomManager{
private:
	RoomManager();
	~RoomManager();
	int fetch();
	Room create();
	int remove(int);
	int kill();
	int onEvent();
	int onJoin();
	int onPart();
	int onChat();
public:
	int start();
	int stop();

};

#endif