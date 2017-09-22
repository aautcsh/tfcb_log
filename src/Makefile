#	tfcb_log - nifty little inbox based blog generator
#	dl@nosrv.org
#

CC=gcc
LIBS=
CFLAGS=-c -O2 -Wall
EXTS=

EXECNAME=genblog

install: build
all: install clean init 

build: cfiles
	$(CC) $(LIBS) *.o -o $(EXECNAME)
	mv $(EXECNAME) ../$(EXECNAME)

cfiles:
	$(CC) $(CFLAGS) $(EXTS) *.c

clean:
	rm -rf *.o $(EXECNAME)
	echo -e "\n\n\ntfcb_log::\tBUILD SUCCEEDED. You may now want to run make init to initialize the blog. In order to install the man page for tfcb_log, please cp the 'tfcb_log.1' file within the src directory to into '/usr/local/share/man/man1/' by yourself."

init:
	cd ../bin && ./make i
