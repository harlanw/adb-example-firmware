#ifndef _TS_TIME_H
#define _TS_TIME_H

#include <stdint.h>

struct time
{
	uint16_t ms;
	uint8_t s;
	uint8_t m;
	uint8_t h;
};

typedef struct time time_t;

void ts_time_init(void);
time_t hwclock(void);

#endif
