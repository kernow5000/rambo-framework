// user-side configuration for rambo .. yeah

// you probably need to edit these and recompile for your system
// at least, until I put command line parameters on in a later version
// and these just become default sensible values if no params are specified.. ^_^


// the amount of time the daemon sleeps for, then wakes up and does some work
// setting it to 30 would mean it sleeps for 30 seconds, then does some shit, then again
// sleeps, like a heartbeat, this way it doesnt consume 99% cpu all the time \\o
#define REFRESH_INTERVAL 15
