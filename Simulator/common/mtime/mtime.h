#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

namespace simulator {

	unsigned long long GetCurrentTimeMsec();

}


