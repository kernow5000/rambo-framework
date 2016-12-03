# rambo daemon framework project makefile
# kernow september 2005

CC = gcc
CFLAGS = -Wall -I./include


# this is bullshit, I shouldn't need to hard-specify each module.. oh well
# read the makefile tutorial properly one day.
DAEMON_SRC = rambo.c
DAEMON_BIN = rambo
INPUT_SRC = rambo_input.c
INPUT_BIN = rambo_input.o
OUTPUT_SRC = rambo_output.c
OUTPUT_BIN = rambo_output.o
UTILS_SRC = utils.c
UTILS_BIN = utils.o

ARCHIVE = rambo-framework
#BACKUPPOINT = /mnt/stick/linux
BACKUPPOINT = ~/dev/

all: clean rambo

rambo:	   
	   $(CC) $(CFLAGS) -c $(UTILS_SRC)
	   $(CC) $(CFLAGS) -c $(INPUT_SRC)
	   $(CC) $(CFLAGS) -c $(OUTPUT_SRC)
	   $(CC) $(CFLAGS) $(INPUT_BIN) $(OUTPUT_BIN) $(UTILS_BIN) $(DAEMON_SRC) -o $(DAEMON_BIN)
	   strip $(DAEMON_BIN)
	      
utils:	      
	   $(CC) $(CFLAGS) -c $(UTILS_SRC)
    
clean:	      
	   rm -Rf *.o *~ include/*~ $(DAEMON_BIN)
	      
backup:		
	   tar cf $(ARCHIVE).tar *[^*.tar]
	   gzip $(ARCHIVE).tar
	   mv $(ARCHIVE).tar.gz $(BACKUPPOINT)
	      
	      
	     
      	       
