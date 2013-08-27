#include <Windows.h>

#ifndef LOGGER_H
#define LOGGER_H

//used for common user CreateFile() ReadFile() WriteFile() Logger debugging
#define LOGGER_DEBUGING

#ifdef LOGGER_DEBUGING
class Logger 
{
public:
	static VOID Log(char* message);
	static VOID Log(int message);
};
#endif
#endif