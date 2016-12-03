// output related functions for rambo daemon
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <syslog.h>

// my headers.
#include <rambo_input.h>              // input side
#include <rambo_output.h>             // output side
#include <utils.h>                    // just some general utilities
#include <config.h>                   // user level rambo configuration 


// function prototypes
void rambo_output();


// theres not much done here really yet
void rambo_output() 
{
syslog(LOG_NOTICE,"rambo output side commences\n");
}
