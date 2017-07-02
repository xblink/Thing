#ifndef LOG_H
#define LOG_H

template <typename T>

class Log {
	public:
		Log();
		~Log();
	private:
		int write(T);
		int read(int);
};

#endif