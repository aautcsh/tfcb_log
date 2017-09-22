#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

/* Createsa rfc822'ish timestamp */

int rfc822_from_tstamp (time_t timestamp, char *out_buffer, size_t bufsize){
	size_t l;
	struct tm *timeinfo = localtime(&timestamp);
	mktime(timeinfo);
	return (l=strftime(out_buffer, bufsize-1, RFC822_FORMAT_INFO, timeinfo));
}

/* Reads a file into a dynamiccaly allocated buffer */
/* TODO: Fix memory leak */

char *r_ftob(int *fd){
	char *b;
	long n=lseek(*fd,0L,SEEK_END);
	lseek(*fd, 0L, SEEK_SET);
	if((b=(char *)malloc((n)+1))<0)
		return NULL;
	while((read(*fd,b,n))>0)
		;
	return (b)?b:NULL;
}

/* Append file to file */

int a_ftof(char *filename, FILE *fd_out){
	int f_in;
	char *b;
	
	if((f_in=open(filename,O_RDONLY,0))<0)
		return -1;
	if((b=r_ftob(&f_in))==NULL){
		if(b)
			free(b);
		close(f_in);
		return -1;
	}
	close(f_in);
	return ((fprintf(fd_out,"%s",b))<0)?-1:0;
}

/* Append string to file */

int a_strtof(char *b, FILE *fd){
	return ((fprintf(fd,"%s",b))<0)?-1:0;
}

/* Global error handling */
void panic(unsigned const short hitme){
	switch(hitme){
		case ERR_INDEX_FOPEN:
			fprintf(stderr, "ee:\t couldn't open index.html.");
			break;		
		case ERR_INDEX_WRHEADER:
			fprintf(stderr, "ee:\t couldn't write html header.");
			break;		
		case ERR_INDEX_WRFOOTER:
			fprintf(stderr, "ee:\t couldn't write html footer.");
			break;		
		case ERR_INDEX_SCANDIR:
			fprintf(stderr, "ee:\t couldn't scan subdirs.");
			break;		
		case ERR_INDEX_PFROMDIR:
		case ERR_RSS_FOPEN:
		case ERR_RSS_WRHEADER:
		case ERR_RSS_WRFOOTER:
		case ERR_RSS_SCANDIR:
		case ERR_RSS_PFROMDIR:
			fprintf(stderr, "ee:\t something bad happened within the generating process.");
			break;			
		default:
			break;
	}
	exit(-1);
}
