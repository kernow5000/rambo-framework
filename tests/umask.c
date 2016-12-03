// get the PID

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{

   char dir[] = "./testdir";
   mode_t umask = 770;
  // what fucking umask is it?
   
   mkdir(dir,umask);
   
   return 0;
}
