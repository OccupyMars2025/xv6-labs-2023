/* 
Implement a user-level sleep program for xv6, along the lines of the UNIX sleep command. 
Your sleep should pause for a user-specified number of ticks. 
A tick is a notion of time defined by the xv6 kernel, 
namely the time between two interrupts from the timer chip. 
*/

#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(2 != argc) {
    printf("Error: there should be one argument ! Usage example: sleep 10\n");
    exit(1);
  }

  int sleep_time = atoi(argv[1]);
  sleep(sleep_time);

  exit(0);
}
