#ifndef _GLOBAL_H
#define _GLOBAL_H
/* 
 * GLOBAL CONFIGURATION SETTINGS 
 */

/*
GNU/Linux workaround:
#ifndef _POSIX_SOURCE
	#define st_atime st_atimespec.tv_sec
  #define st_mtime st_mtimespec.tv_sec
  #define st_ctime st_ctimespec.tv_sec
#endif
*/
#ifndef __linux__
#define _POSIX_SOURCE
#endif

#define SPLIT_DIR 0x2F
#define START_DIR 0x2E
#define WAITT 		255
#define STR_SIZE 	32

/*  DEBUGGING  */
#define PRINT_PROCESSING

#ifndef PRINT_PROCESSING
#define puts(a) 0x90
#endif

/* 
 * HTML CONFIGURATION SETTINGS 
 */

#define TMPL_NAME "minimalistic"

#define INDEX_PERM "wt"
#define POSTS_DIR "posts"
#define INDEX_OUT "out/index.html"
#define MAIN_T_HEADER "templates/"TMPL_NAME"/header.template"
#define MAIN_T_FOOTER "templates/"TMPL_NAME"/footer.template"
#define POSTS_T_HEADER "templates/"TMPL_NAME"/post/header.template"
#define POSTS_T_FOOTER "templates/"TMPL_NAME"/post/footer.template"
#define POSTS_T_LINK "[&#923;] "
#define DATE_T_PREFIX "templates/"TMPL_NAME"/date/prefix.template"
#define DATE_T_SUFFIX "templates/"TMPL_NAME"/date/suffix.template"
#define DATE_T_BLCKHEADER "templates/"TMPL_NAME"/date/blockheader.template"
#define DATE_T_BLCKFOOTER "templates/"TMPL_NAME"/date/blockfooter.template"
#define CMNT_T_TSTAMP "<!-- timestamp: "
#define CMNT_T_RFC822 "-- > <!-- rfc 822: "
#define CMNT_T_END " -->\n"

/* 
 * RSS CONFIGURATION SETTINGS 
 */

#define RSS_PERM "rt"
#define RSS_OUT_PERM "wt"
#define RSS_OUT "out/rss.xml"
#define RSS_LEN_TITLE 28
#define RSS_T_HOST_STRING "http://www2.nosrv.org"
#define RSS_T_HEADER "templates/rss/header.template"
#define RSS_T_FOOTER "templates/rss/footer.template"
#define ITEM_T_HEADER "templates/rss/element/header.template"
#define ITEM_T_FOOTER "templates/rss/element/footer.template"
#define ITEM_T_DSCR_HEADER "templates/rss/element/description_header.template"
#define ITEM_T_DSCR_FOOTER "templates/rss/element/description_footer.template"
#define ITEM_T_TITLE_HEADER "templates/rss/element/title_header.template"
#define ITEM_T_TITLE_FOOTER "templates/rss/element/title_footer.template"
#define ITEM_T_LINK_HEADER "templates/rss/element/link_header.template"
#define ITEM_T_LINK_FOOTER "templates/rss/element/link_footer.template"
#define ITEM_T_GUID_HEADER "templates/rss/element/guid_header.template"
#define ITEM_T_GUID_FOOTER "templates/rss/element/guid_footer.template"
#define ITEM_T_DATE_HEADER "templates/rss/element/date_header.template"
#define ITEM_T_DATE_FOOTER "templates/rss/element/date_footer.template"

#endif

/* EOF */
