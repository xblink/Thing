#include "reciever.h"

Reciever::Reciever(Logger _log, Controller _contr) {
	logger = _log;
	controller = _contr;
}

Reciever::~Reciever() {

}

int Reciever::onEvent(sEvent e) {
	if (e.type == 'p') {
		// log player event
		logger.log(e.desc);
	}
	else if (e.type == 'b') {
		// log but ignore misc event
		logger.log(e.desc);
		return 0;
	}
	//return status from controller
	return controller.update(e);
}


int Reciever::onCommand(string command) {
	if (command.find("p'") == 1) {
		logger.log(command.substr(2));
		return 0;
	}
	
	else if (command.find("c'") == 1) {
		//return status from controller
		return controller.command(command.substr(2));
	}

	//return -1 for doing nothing
	return -1;
}

int Reciever::onJoin() {
	//TODO:: recieve join
	return 0;
}

int Reciever::onPart() {
	//TODO:: recieve part
	return 0;
}