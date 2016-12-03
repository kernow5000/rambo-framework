#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// this test works exactly how I presumed .. now
// to incorporate it into rambo_init.. one day
// 
// not yet though.. not Just yet..


int main(int argc, char *argv[])
{
   
   pid_t pid;
   
   
   printf("Parent process has pid %d.\n",getpid());
   
   
   // try to fork
   pid = fork();

   // check process id
   if(pid < 0)
     {
	printf("Error forking, exiting.\n");
	exit (1);
     }
   
   if(pid > 0) 
     {
	printf("Fork ok! Exiting parent process.\n");
	exit(0);
     }
   

   // so are we the child process now then?
   // 
   
   printf("Child process forked off with pid %d\n", getpid());
   
   // spin forever
   while(1) 
     {
     }
   

}
