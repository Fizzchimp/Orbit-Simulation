#pragma once

#include <iostream>
#include <GL/glew.h>


#ifdef NDEBUG
#define GLCALL(func) func;
#else
#define GLCALL(func) clearErrors();\
		func;\
		if (!logCall(#func, __FILE__, __LINE__)) {__debugbreak();}
#endif


// Clears all the errors from the error queue
void clearErrors();

// Logs the first error on the error queue
bool logCall(const char* function, const char* file, int line);