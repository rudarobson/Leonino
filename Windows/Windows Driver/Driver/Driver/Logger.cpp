#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef LOGGER_CPP
#define LOGGER_CPP

VOID Logger::Log(int message){
	char s[10];
	itoa(message,s,10);
	Logger::Log(s);
}

VOID Logger::Log(char *message){
	UNREFERENCED_PARAMETER(message);
	
	FILE* f = fopen("D:/PROGRAMMERDRIVER.txt","a");
	fprintf(f,"%s",message);
	fclose(f);
	/*DWORD numWritten;
	HANDLE file_tracer = CreateFile("D:/PROGRAMMERDRIVER.txt",
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	SetFilePointer(file_tracer,0,NULL,FILE_END);

	WriteFile(file_tracer,
		message,
		length,
		&numWritten,
		NULL);

	CloseHandle(file_tracer);*/
}

#endif