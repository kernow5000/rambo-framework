// rambo daemon framework for .... something
// edit config.h to suit your settings for now
// kernow september 2005

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <syslog.h>

// my headers.
#include <rambo.h>                    // system specific rambo shit
#include <rambo_input.h>              // input side functions
#include <rambo_output.h>             // output side functions
#include <utils.h>                    // just some general utilities
#include <config.h>                   // top level user configuration header

// globals
int quit = 0;                         // quit flag


// function prototypes
extern void rambo_usage();     // usage information, on -h? 
int rambo_init();              // daemon initialization
void rambo_run();              // run the daemon
void rambo_cleanup();          // cleanup on daemon finish
void sigterm_handler();        // deals with SIGTERM
void sigint_handler();         // deals with ctrl-c, just cleans up.


void sigterm_handler() 
{
  
  syslog(1,"SIGTERM caught - cleaning up and exiting.\n");
  (void) signal(SIGTERM, SIG_DFL);   // reset to default signal handler
  
  // run the daemons cleanup function
  rambo_cleanup();
  
  // finally, exit
  exit(0);
}


// I'm not even sure this is needed anymore, when is a ctrl-c (sigint) going to happen
// when theres no terminal connected? O_o
void sigint_handler()
{
  syslog(1,"SIGINT caught - cleaning up and exiting.\n");
  (void) signal(SIGINT, SIG_DFL); // reset to default signal handler
  
  // run the daemons cleanup function
  rambo_cleanup();
  
  // finally, exit
  exit(0);
}


// daemon initialisation
int rambo_init() {
  // forks off properly too	  
  // process id for child
  pid_t pid;
  // session id for child (else it just becomes an orphan over time)
  pid_t sid;
  
  // fork off the child process.. or try to
  pid = fork();
  
  // check the pid to see if it was a success
  if(pid < 0)
    {
      printf("Error forking off child process, exiting.\n");
      exit (1);
    }
  if(pid > 0)
    {
      //printf("Fork ok! Exiting parent process.\n");
      exit(0);
    }
  
  // strange, maybe the parent process should do all these checks before forking
  // and not just letting the child process do it, but then, is this way cleaner
  // and more self contained?
  // 
  // this is now the CHILD process code.
  printf("rambo - Child process forked with pid %d\n", getpid());
  
  // this logs to /var/log/syslog by default, not dmesg, is that kernel messages?
  syslog(LOG_NOTICE,"Initialising Daemon");
  
  
  // setup a umask of nothing. i.e 0777
  umask(0);
  
  // maybe open my own log in /var/log here? or not bother and use syslog? 
  // Create a new SID for the child process, creates a new process group etc or something
  sid = setsid();
  if (sid < 0) 
    {	
      syslog(LOG_ERR,"Unable to get a session ID, exiting.\n");
      exit(1);
    }
  
  
  // now we change the current working directory to something.. sensible
  if ((chdir("/")) < 0) 
    {
      syslog(LOG_ERR,"Unable to change current working directory, exiting.\n");
      exit(1);
    }
  
  
  // Close out the standard file descriptors
  // they are a security risk and don't need to be open for a daemon
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  // now, every printf below will not be seen, not useful for debugging eh?.. not
  // 
  // ignore terminal based signals
  signal(SIGTTOU, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  
  // ignore nohup too? I heard it was good to, to prevent any 'grandchildren' wtf?
  signal(SIGHUP, SIG_IGN);
  
  // this is where we do any last minute resource checks on files or directories
  // or maybe even config files
  // however there is nothing to do at present so just say we initialised ok.
  
  // if we are here, init ran ok because nothing returned -1
  return 0;
  // that means, we can move on!
}




void rambo_run() {
  
  // this is where we run the daemon eh.. 
  syslog(LOG_NOTICE,"Daemon running.\n");

  // enter loop, sleep until wakeup after REFRESH_INTERVAL (defined in config.h)  
  do
    {
      // sleep .. until we wake up.
      sleep(REFRESH_INTERVAL);
      
      // begin input/output cycle for this timeout period
      // you'll notice theres no input/output specific stuff in here
      // thats so the input and output are abstracted nicely.

      // if theres any errors on input, complain like hell and do something about it 
      rambo_input();
      
      // if theres any errors on output, complain like hell and do something about it
      rambo_output();
      // then sleep again, at the top of this loop
    }
  while(quit != 1);
}


void rambo_cleanup() {
  syslog(LOG_NOTICE,"Cleaning up on Daemon exit.\n");
  // delete the temp files.. anything else?
  // what about the state of the symlink base and the automounter config?
  exit(0);
}



int main(int argc, char *argv[]) {
  
  
  // maybe add command line arguments for config/basedir locations in a future version.
  if(argc == 2) 
    {
      if(!strcmp(argv[1],"-h"))
	rambo_usage();
      return 0;
    }
  
  // chain term signal to cleanup function
  (void) signal(SIGTERM, sigterm_handler);
  
  // chain ctrl-c signal to cleanup function
  (void) signal(SIGINT, sigint_handler);
  
  // initialise the daemon
  if (rambo_init() != 0) 
    {
      printf("Initialisation failed.. exiting.\n");
      return -1;
    }
  else printf("Initialisation OK.. running Daemon.\n");
  // I don't think these printf's are needed anymore.. they never get shown
  // 
  // if we are here, we can assume the init completed ok :)
  // start the main daemon loop part
  rambo_run();
  
  // just cleanup and exit if we get here.
  rambo_cleanup();
  
  return 0;
}
// end of rambo.c
// kernow
