// get the PID

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[])
{

   pid_t p = getpid();
   
   printf("this process is running with processID %i\n", p);
   
   return 0;
}
