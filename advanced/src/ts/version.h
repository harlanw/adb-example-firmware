#ifndef _TS_VERSION_H
#define _TS_VERSION_H

#define TS_VERSION (0x001)

#define TS_VERSION_MAJOR ((TS_VERSION >> 8) & 0x00F)
#define TS_VERSION_MINOR ((TS_VERSION >> 4) & 0x00F)
#define TS_VERSION_PATCH ((TS_VERSION >> 0) & 0x00F)

#endif
