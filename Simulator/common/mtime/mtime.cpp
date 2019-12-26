#include "common/mtime/mtime.h"

namespace simulator {
	unsigned long long GetCurrentTimeMsec()
	{
#ifdef _WIN32
		struct timeval tv;
		time_t clock;
		struct tm tm;
		SYSTEMTIME wtm;

		GetLocalTime(&wtm);
		tm.tm_year = wtm.wYear - 1900;
		tm.tm_mon = wtm.wMonth - 1;
		tm.tm_mday = wtm.wDay;
		tm.tm_hour = wtm.wHour;
		tm.tm_min = wtm.wMinute;
		tm.tm_sec = wtm.wSecond;
		tm.tm_isdst = -1;
		clock = mktime(&tm);
		tv.tv_sec = clock;
		tv.tv_usec = wtm.wMilliseconds * 1000;
		return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#endif
	}

}