#ifndef RECIEVER_H
#define RECIEVER_H

#include <string>
#include "logger.h"
#include "controller.h"

class Reciever {
public:
	Reciever(Logger, Controller);
	~Reciever();
private:
	Logger logger;
	Controller controller;
	int onEvent(sEvent);
	int onCommand(string);
	int onJoin();
	int onPart();
};
#endif
