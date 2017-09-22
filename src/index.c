#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include "index.h"
#include "utils.h"
#include "global.h"

static const char *current_dir = ".";

int a_ptof(char *filename, FILE *fd){
	struct stat attribs;
	char s_time[WAITT],s[STR_SIZE];
	time_t tstamp;
	size_t len;

	len= strlen(current_dir)+strlen("/")+strlen(filename)+1;
	char abstr[len];
	sprintf(abstr,"%s/%s",current_dir,filename);
	/* timestamp */
	stat(abstr, &attribs);
	tstamp= attribs.st_mtime;
	rfc822_from_tstamp(tstamp,s_time,WAITT);
	
	if((a_strtof(CMNT_T_TSTAMP,fd))<0)
		return -1;
	sprintf(s,"%ld", tstamp);
	if((a_strtof(s, fd))<0)
		return -1;
	if((a_strtof(CMNT_T_RFC822, fd))<0)
		return -1;
	if((a_strtof(s_time, fd))<0)
		return -1;
	if((a_strtof(CMNT_T_END, fd))<0)
		return -1;
	
	/* header,link,post,footer */
	if((a_ftof(POSTS_T_HEADER, fd))<0)
		return -1;
	if((a_strtof(POSTS_T_LINK, fd))<0)
		return -1;
	if((a_ftof(abstr, fd))<0)
		return -1;
	if((a_ftof(POSTS_T_FOOTER, fd))<0)
		return -1;
	return 0;
}

int a_datetof(char *date, FILE *fd){
	if((a_ftof(DATE_T_PREFIX, fd))<0)
		return -1;
	if((a_strtof(date,fd))<0)
		return -1;
	if((a_ftof(DATE_T_SUFFIX, fd))<0)
		return -1;
	return 0;
}

int a_pfdirtof(char *dirname, FILE *fd){
	//todo: check if ent is dir or file. on file continue on dir process
	struct dirent **dir_entries;
	int pcnt_d, i, n;
	size_t savepos, len;
	
	//save pos for possible rewind if no posts were added for this date
	if((savepos=ftell(fd))<0)
		return -1;
	len= strlen(current_dir)+strlen(".")+strlen(dirname) + 1;

	char abstr[len];
	sprintf(abstr,"%s/%s", current_dir, dirname);
	puts("ii:\t appending post:");
	if((a_datetof(dirname,fd))<0)
		return -1;
	if((a_ftof(DATE_T_BLCKHEADER,fd))<0)
		return -1;
	//let's add the posts for today
	pcnt_d = 0;
	if((i=n=scandir(abstr, &dir_entries, NULL, alphasort))<0)
		return -1;
	while (n--){
		if (dir_entries[n]->d_name[0] == '.')
			continue;
		current_dir= abstr;
		pcnt_d++;
		if((a_ptof(dir_entries[n]->d_name, fd))<0)
			return -1;
	}
	while(i--)
		free(dir_entries[i]);
	if((a_ftof(DATE_T_BLCKFOOTER, fd))<0)
		return -1;
	
	//if no posts were added for this date, let's rewind to the previous position
	//so we won't have an empty date header
	if (pcnt_d == 0)
		fseek(fd, savepos, SEEK_SET);
	puts("ok:\t done.");
	return 0;
}

int make_index(){
	struct dirent **dir_entries;
	int i,n;
	FILE *fd_out;
	
	puts("\nii:\t HTML PROCESSING\n\nii:\t build index.html");
	if((fd_out=fopen(INDEX_OUT,"wt"))<0)
		return ERR_INDEX_FOPEN;
	puts("ok:\t write header.");
	if((a_ftof(MAIN_T_HEADER, fd_out))<0){
		fclose(fd_out);
		return ERR_INDEX_FOPEN;
	}	
	if((i=n=scandir(POSTS_DIR, &dir_entries, NULL, alphasort))<0){
		fclose(fd_out);
		return ERR_INDEX_FOPEN;
	}
	puts("ok:\t begin to append posts.");
	
	//reverse dir iteration because blog posts are upside down (latest on top)
	while (n--){
		if (dir_entries[n]->d_name[0] == '.')
			continue;
		current_dir= POSTS_DIR;
		if((a_pfdirtof(dir_entries[n]->d_name, fd_out))<0){
			fclose(fd_out);
			return ERR_INDEX_FOPEN;
		}
	}
	puts("ok:\t all posts appended.");
	while(i--)
		free(dir_entries[i]);
	puts("ii:\t write footer.");
	if((a_ftof(MAIN_T_FOOTER, fd_out))<0){
		fclose(fd_out);
		return ERR_INDEX_FOPEN;
	}
	fclose (fd_out);
	puts("ok:\t built index.html, shalalala.");
	return 0;
}
