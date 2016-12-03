// killall sigkill = SIGTERM
// WTF... what does sigkill do exactly then?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sigterm_cleanup(int sig) 
{
   printf("signal %d caught - cleaning up and exiting.\n", sig);
   (void) signal(SIGTERM, SIG_DFL);   // reset to default signal handler
   
   printf("clean temp files\n");
   printf("close file handles\n");
   
   exit(0);
}


int main(int argc, char *argv[])
{
   //chain signal to ctrl_c() function
   (void) signal(SIGTERM, sigterm_cleanup);
   
   printf ("running forever until we get a signal\n");
   
   while (1) 
     {
     }
   
   return 0;
}
