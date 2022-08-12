//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangutil/sys/YangCTime.h>
#include <yangutil/yangavtype.h>

#include <time.h>
#include <stdlib.h>


#ifdef _MSC_VER
int gettimeofday(struct timeval *tp, void *tzp)
{
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
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

#include <sys/timeb.h>
static uint64_t _getCurrentTimeMillis()
{
    struct timeb t;
    ftime(&t);
    return t.time * 1000 + t.millitm;
}
#endif

int64_t yang_get_system_micro_time(){
#ifdef _MSC_VER
    int64_t tmp = _getCurrentTimeMillis();
    int64_t ret = tmp*1000;
    return ret;
#else
    return yang_get_micro_time();
#endif
}

int64_t yang_get_system_milli_time(){
#ifdef _MSC_VER
    return _getCurrentTimeMillis();
#else
    return yang_get_milli_time();
#endif
}

//weimiao
int64_t yang_get_micro_time() {
    struct timeval time;
    gettimeofday(&time, 0);
    int64_t res = time.tv_sec;
    return res * 1000000 + time.tv_usec ;
}
//haomiao
int64_t yang_get_milli_time() {
    struct timeval time;
    gettimeofday(&time, 0);
    // long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}


const uint64_t kMagicNtpFractionalUnit = ((uint64_t)1) << 32;



void yang_ntp_from_time_ms(YangNtp* ntp,uint64_t ms)
{

	 ntp->system_ms = ms;
	    ntp->ntp_second = ms / 1000;
	    ntp->ntp_fractions = ((double)(ms % 1000 / 1000.0)) * kMagicNtpFractionalUnit;
	    ntp->ntp = ((uint64_t)(ntp->ntp_second) << 32) | ntp->ntp_fractions;
}

void yang_ntp_to_time_ms(YangNtp* ntp,uint64_t pntp)
{

	ntp->ntp =pntp;
	    ntp->ntp_second = (pntp & 0xFFFFFFFF00000000ULL) >> 32;
	    ntp->ntp_fractions = (pntp & 0x00000000FFFFFFFFULL);
	    ntp->system_ms = ((uint64_t)(ntp->ntp_second) * 1000) +
	            ((double)((uint64_t)(ntp->ntp_fractions) * 1000.0) / kMagicNtpFractionalUnit);

}
