#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "utils.h"
#include "rss.h"
#include "global.h"

static const char *current_dir = ".";

int a_eltof(char *filename, FILE *fd){
	char title[STR_SIZE], s_time[WAITT];
	struct stat attribs;
	size_t len;
	FILE *el;

	/* header,description */
	if((a_ftof(ITEM_T_HEADER, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_DSCR_HEADER, fd))<0)
		return -1;
	/* post */
	len= strlen(current_dir)+strlen("/")+strlen(filename)+1;
	char abstr[len];
	sprintf(abstr,"%s/%s",current_dir,filename);
	if((a_ftof(abstr,fd))<0)
		return -1;

	/* desc end,title */
	if((a_ftof(ITEM_T_DSCR_FOOTER, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_TITLE_HEADER, fd))<0)
		return -1;
	if((el=fopen(abstr,"rw"))<0)
		return -1;
	fread(title,RSS_LEN_TITLE,1,el);

	// how would you add "..." to the title string?
	#ifdef __LITTLE_ENDIAN
		memset((char *)(title+RSS_LEN_TITLE-4),(char *)'\x00\x2e\x2e\x2e',4);
	#else
		memset((char *)(title+RSS_LEN_TITLE-4),(char *)'\x2e\x2e\x2e\x00',4);
	#endif

	//title[RSS_LEN_TITLE-4]='\0';

	fclose (el);
	if((a_strtof(title, fd))<0)
		return -1;

	/* title end,link */
	if((a_ftof(ITEM_T_TITLE_FOOTER, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_LINK_HEADER, fd))<0)
		return -1;
	if((a_strtof(RSS_T_HOST_STRING, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_LINK_FOOTER, fd))<0)
		return -1;

	/* guid */
	if((a_ftof(ITEM_T_GUID_HEADER, fd))<0)
		return -1;
	if((a_strtof(RSS_T_HOST_STRING, fd))<0)
		return -1;
	if((a_strtof(abstr, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_GUID_FOOTER, fd))<0)
		return -1;

	/* date,footer */
	if((a_ftof(ITEM_T_DATE_HEADER, fd))<0)
		return -1;
	stat(abstr, &attribs);
	if((rfc822_from_tstamp(attribs.st_mtime, s_time, WAITT))<0)
		return -1;
	if((a_strtof(s_time, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_DATE_FOOTER, fd))<0)
		return -1;
	if((a_ftof(ITEM_T_FOOTER, fd))<0)
		return -1;
	return 0;
}

int a_elfdtof(char *dirname, FILE *fd){
	//todo: check if ent is dir or file. on file continue on dir process
	int pcnt_d,n,i;
	struct dirent **dir_entries;
	size_t len, savepos;

	puts("ii:\t appending element.");
	if((savepos = ftell(fd))<0)
		return -1;
	pcnt_d = 0;
	len= strlen(current_dir)+strlen("/")+strlen(dirname)+1;
	char abstr[len];
	sprintf(abstr,"%s/%s", current_dir, dirname);

	//posts for today
	if((i=n=scandir(abstr, &dir_entries, 0, alphasort))<0)
		return -1;

	while (n--){
		if (dir_entries[n]->d_name[0] == '.')
			continue;
		current_dir = abstr;
		pcnt_d ++;
		a_eltof(dir_entries[n]->d_name, fd);
	}
	while(i--)
		free (dir_entries[i]);

	//if no posts were added for this date, let's rewind to the previous position
	//so we won't have an empty date header
	if (pcnt_d == 0)
		fseek(fd, savepos, SEEK_SET);
	puts("ok::\t done.");
	return 0;
}

int make_rss(){
	struct dirent **dir_entries;
	int i,n;
	FILE *fd_out;

	puts("\nii:\t RSS PROCESSING\n\nii:\t build rss.xml");
	if((fd_out=fopen(RSS_OUT, RSS_OUT_PERM))<0)
		return ERR_INDEX_FOPEN;
	puts("ok:\t write header.");
	if((a_ftof(RSS_T_HEADER, fd_out))<0)
		return ERR_INDEX_FOPEN;
	if((i=n=scandir(POSTS_DIR, &dir_entries, 0, alphasort))<0)
		return ERR_INDEX_FOPEN;
	puts("ok:\t begin to append elements.");

	while (n--){
		if (dir_entries[n]->d_name[0] == '.')
			continue;
		current_dir = POSTS_DIR;
		a_elfdtof(dir_entries[n]->d_name, fd_out);
	}
	puts("ok:\t all elements appended.");
	while(i--)
		free(dir_entries[i]);
	puts("ii:\t write footer.");
	if((a_ftof(RSS_T_FOOTER, fd_out))<0)
		return ERR_INDEX_FOPEN;
	fclose (fd_out);
	puts("ok:\t built rss.xml, shalalala.\n");
	return 0;
}
