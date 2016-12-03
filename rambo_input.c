// input side source module for rambo daemon
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/stat.h>

// my headers.
#include <rambo_input.h>              // input side functions
#include <rambo_output.h>             // output side functions
#include <utils.h>                    // just some general utilities
#include <config.h>                   // user level rambo configuration


// function prototypes
void rambo_input();



// this doesnt do much either.
void rambo_input() 
{
   syslog(LOG_NOTICE,"rambo input side commences\n");
}

