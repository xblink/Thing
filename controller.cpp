#include "controller.h"

Controller::Controller(Logger _log) {
	logger = _log;
}

Controller::~Controller() {

}

int Controller::command(string _command) {
	//TODO:: act on command
	return 0;
}

int Controller::player(string _player) {
	//TODO:: act on player/service part/join
	return 0;
}

int Controller::update(string _event) {
	//TODO:: act on event
	return 0;
}