// Test file
#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h" // printf()
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int stdout = 1;

// Exittest function
// This function is used to test our exit and wait system calls
//
void exittest() {
	printf(stdout, "exittest started\n");
	int pid;
	if ((pid = fork()) == 0) {
		// in child
		
		printf(stdout, "hello from child\nexiting child with status: %d\n", 1);
		exit(2);
	}
	else {
		// in parent
		printf(stdout, "hello from parent\n");
		
		int exitStatus;
		int childpid = wait(&exitStatus);
		
		if (childpid > 0) {
			if (exitStatus >= 0) {
				printf(stdout, "exit status of child pid %d: %d\n", childpid, exitStatus);
			}
			else {
				printf(stdout, "Error in pid %d; no exit status\n", childpid);
				exit(0);
			}
		}
		else {
			printf(stdout, "error: process had no children\n");
		}
		
		exit(0);
		
	}
}

void waittest(void) {
	//int pid;
	
	printf(stdout, "waittest started\n");
	
}

// Waitpidtest function
// This function is used to test our waitpid system call.  Can also be used to test exit
//
void waitpidtest(void) {
	//int i, pid;
	printf(stdout, "waitpidtest started\n");
	int pid1, pid2; // We can choose which pid we are going to wait for

	if ((pid1 = fork())==0){
		// First Child
		printf(stdout, "This is the first child created, pid(%d)\n",(int)getpid());
		exit(0); // First child exits
	}
	else if ((pid2 = fork())==0){

		// Second Child

		printf(stdout, "This is the second child created, pid(%d)\n", (int)getpid());
		exit(0); // Second child exits
	}
	else{
		// This is the parent process
		printf(stdout, "This is the parent process\n");
		int exitStatus; // The exitStatus that gets updated by the waitpid function
		int termpid = waitpid(pid1,&exitStatus,0);
		printf(stdout, "Waited and now it's back\n");
		
		if(termpid > 0 && exitStatus >=0){
			printf(stdout, "exit status of the pid(%d): %d\n", termpid,exitStatus);
		}
		else{
			printf(stdout, "error: process did not return correctly\n");
		}
		
		int exitStatus2;
		printf(stdout, "Now waiting for 2nd child process to exit\n");
		if (waitpid(pid2, &exitStatus2, 0) >= 0) {
			printf(stdout, "2nd child exited pid(%d) with exit status: %d\n", pid2, exitStatus2);
		}
		
		
		exit(0); // The parent exits
	}
}

int main() {
	//printf(stdout, "in tests.c main function\n");
	
	//exittest();
	printf(stdout, "Testing waitpid function\n");
	waitpidtest();
	
	exit(0);
}
