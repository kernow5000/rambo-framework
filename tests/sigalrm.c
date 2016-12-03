// sigalrm handler

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


#define TIMEOUT 3

// this fires off every timeout, as long as you set it to
void sigalrm_handler(int sig) 
{
   //printf("signal %d caught - handling things\n", sig);
   
   // request new smbtree
   // parse the smbtree
   // do the symlinking and config editing
   // 
   printf("rambo input side commences\n");
   printf("rambo output side commences\n");
   
   // set another alarm, we want this continuous
   alarm(TIMEOUT);
  
}


int main(int argc, char *argv[])
{
   //chain signal to ctrl_c() function
   (void) signal(SIGALRM, sigalrm_handler);
   
   
   // set the initial alarm
   alarm(TIMEOUT);
   
   while (1) 
     {
     }
   
   return 0;
}
