#include <Windows.h>

#ifndef LOGGER_H
#define LOGGER_H
class Logger 
{
public:
	static VOID Log(char* message);
	static VOID Log(int message);
};

#endif