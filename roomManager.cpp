#include "roomManager.h"

RoomManager::RoomManager() {

}

RoomManager::~RoomManager(){

}

int RoomManager::fetch() {
	//TODO:: fetch updates
	return 0;
}

Room RoomManager::create() {
	//TODO:: create room
	return new Room;
}

int RoomManager::remove(int roomID) {
	//TODO:: remove room
	return 0;
}

int RoomManager::kill() {
	//TODO:: kill all rooms
	return 0;
}

int RoomManager::onEvent() {
	//TODO:: handle event
	return 0;
}

int RoomManager::onJoin() {
	//TODO:: handle new service
	return 0;
}

int RoomManager::onPart() {
	//TODO:: handle finished service
	return 0;
}

int RoomManager::onChat() {
	//TODO:: handle service activity
	return 0;
}

int RoomManager::start() {
	//TODO:: start/resume manager
	return 0;
}

int RoomManager::stop() {
	//TODO:: pause manager
	return 0;
}
