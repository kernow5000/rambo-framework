// just some general utility functions for rambo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>


// checks if a resource exists
int f_exists(char *thing) {
   int infile = 0;
   if ( (infile = open(thing, O_RDONLY)) == -1)
     {
	//printf("infile is : %i on failure.\n", infile);
	close (infile);
	return -1;
     }
   else
     {
	//printf("infile is : %i on success.\n", infile);
	close (infile);
	return 0;
     }
}
// I'm sure a function exists to do this already in libc
