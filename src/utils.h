#ifndef _UTILS_H
#define _UTILS_H

#include <time.h>

#define RFC822_FORMAT_INFO "%a, %d %b %Y %H:%M:%S %z"

extern int rfc822_from_tstamp (time_t, char *, size_t );

extern char *r_ftob(int *);
extern int a_ftof(char *, FILE *);
extern int a_strtof(char *, FILE *);
extern void panic(unsigned const short);

/*
 * ERROR OPCODES
 */
#define ERR_INDEX_FOPEN 0x01
#define ERR_INDEX_WRHEADER 0x02
#define ERR_INDEX_SCANDIR 0x03
#define ERR_INDEX_PFROMDIR 0x04
#define ERR_INDEX_WRFOOTER 0x05
#define ERR_BUILD_BUILD 0x06

#define ERR_RSS_FOPEN 0xA1
#define ERR_RSS_WRHEADER 0xA2
#define ERR_RSS_SCANDIR 0xA3
#define ERR_RSS_PFROMDIR 0xA4
#define ERR_RSS_WRFOOTER 0xA5
#define ERR_RSS_BUILD 0x06
#endif

/* EOF */
