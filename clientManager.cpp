#include "clientManager.h"

ClientManager::ClientManager(RoomManager _rm) {
    rManager = _rm
}


ClientManager::~ClientManager() {

}


int ClientManager::kill() {
    //TODO: close all lobbies
    return 0;
}


bool ClientManager::isRoom() {
    //TODO: return True if room exists
    return false;
}


int ClientManager::addRoom() {
    //TODO: add room
    return 0;
}


int ClientManager::removeRoom() {
    //TODO: remove room
    return 0;
}


int ClientManager::createRoom() {

}


int ClientManager::fetch() {
    //TODO: get updates from queue
    return 0;
}

int ClientManager::push() {
    //TODO: push update to queue
    return 0;
}

int ClientManager::inform() {

}