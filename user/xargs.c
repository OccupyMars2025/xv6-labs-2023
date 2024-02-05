/**
 * https://pdos.csail.mit.edu/6.1810/2023/labs/util.html
 * 
 * Write a simple version of the UNIX xargs program for xv6: 
 * its arguments describe a command to run, it reads lines 
 * from the standard input, and it runs the command for each line, 
 * appending the line to the command's arguments. Your solution 
 * should be in the file user/xargs.c.
 * 
 * run:
 * $ sh < xargstest.sh
 * 
*/


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"


int
main(int argc, char *argv[])
{
  if(argc < 2) 
  {
    fprintf(2, "Error: 'xargs' needs at least 1 argument\n");
    exit(1);
  }

  /*Caution: exec(input_argv[0], input_argv);
  input_argv[0] should be argv[1]
  */
  char *input_argv[MAXARG + 1];
  int index = 0;
  for(int i=1; i<argc; ++i){
    if(index >= MAXARG) {
      fprintf(2, "Error: 'xargs' gets too many arguments\n");
      exit(1);
    }
    input_argv[index++] = argv[i];
  }
  int original_index = index;

  char input_char;
  char *one_argument = (char*)malloc(MAXSTRINGLENGTH + 1);
  int index002 = 0;
  while (read(0, &input_char, sizeof(input_char)) > 0)
  {
    if(' ' != input_char && '\t' != input_char && '\n' != input_char) { // append chars one by one to form an argument
      if(index002 >= MAXSTRINGLENGTH) {
        fprintf(2, "Error: xargs: string length of an argument exceeds maximum value\n");
        exit(1);
      }
      one_argument[index002++] = input_char;
      // printf("%c\n", one_argument[index002-1]);
    } else {  // now one argument has been read
      one_argument[index002] = '\0';
      // printf("%s\n", one_argument);
      if(index002 > 0) {
        input_argv[index++] = one_argument;
        one_argument = (char*)malloc(MAXSTRINGLENGTH + 1);
      }
      index002 = 0;

      if('\n' == input_char) { // now one line of arguments has been read, fork and exec
        input_argv[index] = 0;
        // for(int i=0; i<=index; ++i){
        //   printf("[arg:%s] ", input_argv[i]);
        // }
        // printf("\n");
        
        int pid = fork();
        if(0 == pid) {
          exec(input_argv[0], input_argv);
        } else {
          wait((int*)0);
          // free the memory allocated to store the arguments
          for(int i=original_index; i<index; ++i){
            free(input_argv[i]);
          }
          index = original_index;
        }
      }
    }
  }
  
  exit(0);
}
