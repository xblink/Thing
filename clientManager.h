#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "util.h"

class ClientManager {
    private:
        process **updateQueue;
        int kill();
        bool isRoom();
        int addRoom();
        int removeRoom();
        int createRoom();
        int informRoomManager();
        
    public:
        ClientManager();
        ~ClientManager();
        int fetchUpdates();
        int push();

}; // end ClientManager
#endif