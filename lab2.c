#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  printf(1, "\n Lab 2 Tests! \n");
  printf(1, "\n");

  int priorities[3] = {16, 11, 6};
  setpriority(1);

  int i, j, k;
  int pid;

  for (i = 0; i < 3; i++) {
    pid = fork();

    // error
    if (pid < 0) {
		    printf(2," \n Error \n");
		}
    // child
	  else if (pid == 0) {
      setpriority(priorities[i]);	

      // add some wait period between prints
	    for (j = 0; j< 100000; j++) {
        for(k = 0 ; k < 10000; k++) {
          asm("nop"); 
        }
      }

      printf(1, "\n Process with pid#%d with priority#%d finished! \n", getpid(), priorities[i]);
      exit(0);
    }
    // parent
    else {
	    continue;
    }
  }

  if (pid > 0) {
    for (i = 0; i < 3; i++) {
      // wait all parent procs
      wait(0);
    }
  }

  exit(0);
  return 0;
}
