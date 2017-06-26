#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <vector>

class RoomManager{
    private:

        int fetch();
        int create();
        int remove();
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