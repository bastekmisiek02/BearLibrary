#pragma once

#ifdef _DEBUG
	#define DEBUG
#elif defined NDEBUG
	#define RELEASE
#endif

#ifdef _WIN64
	#define	WIN64
	#define WINDOWS_ACTIVE
#elif defined _WIN32
	#define WIN32
	#define WINDOWS_ACTIVATE
#elif defined __linux__
	#define LINUX
#else
	#error "OS is not supported"
#endif

#include "Exceptions.h"

typedef unsigned char UChar;

typedef unsigned short int USInt;
typedef short int SInt;

typedef unsigned int UInt;

#if defined WIN64 || LINUX
	typedef unsigned long long int ULInt;
	typedef long long int LInt;
#else
	typedef unsigned int ULInt;
	typedef int LInt;
#endif