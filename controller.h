#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

struct sEvent {
	char type;
	string desc;
};

class Controller {
public:
	Controller(Logger);
	~Controller();
	int command(string);
	int player(string);
	int update(sEvent);
private:
	Logger logger;
};

#endif