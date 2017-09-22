#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "utils.h"
#include "rss.h"
#include "index.h"

int main (int argc, char **argv){
	int errc=0;
	if((errc=make_index())!=0)
		panic(errc);
	if((errc=make_rss())!=0)
		panic(errc);
	return 0;
}
