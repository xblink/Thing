#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "log.h"

template <typename T>

class Logger {
public:
	Logger();
	~Logger();
	int log(int, T);
	string fetch(int);
	string fetch(int, int);
private:
};

#endif