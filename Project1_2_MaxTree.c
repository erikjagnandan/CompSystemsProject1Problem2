#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void explain_wait_status(pid_t pid, int status){
	if (WIFEXITED(status))
		fprintf(stderr, "Child with PID = %ld terminated normally, exit status = %d\n", (long)pid, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		fprintf(stderr, "Child with PID = %ld was terminated by a signal, signo = %d\n", (long)pid, WTERMSIG(status));
	else if (WIFSTOPPED(status))
		fprintf(stderr, "Child with PID = %ld has been stopped by a signal, signo %d\n", (long)pid, WSTOPSIG(status));
	else {
		fprintf(stderr, "%s: Internal error: Unhandled case, PID = %ld, status = %d\n", __func__, (long)pid, status);
		exit(1);
	}
	fflush(stderr);
}

void main(int argc, char* argv[]){
	if(argc<1){
		printf("Not Enough Command Line Arguments");
		return;
	}
	int A = 2;
	int B = 4;
	int C = 6;
	int D = 10;
	char cmd[50];
	pid_t pid;
	pid_t parent_pid = getpid();
	//Initial Parent
	for(int i = 0; i < atoi(argv[1]); i++){
		printf("Process with PID = %ld - Start and Forking Child\n", (long)getpid());
		pid = fork();
	}
	if(pid<0){
		printf("Error in Fork\n");
	}
	else if(pid==0){
		//Child
		printf("Process with PID = %ld - Start and Entering sleep() Call\n", (long)getpid());
		sleep(10);
		printf("Process with PID = %ld - Exiting sleep() Call and Terminating With Status %d\n", (long)getpid(), D);
		exit(D);
	}
	else{
		//Parent
		int status;
		printf("Process with PID = %ld - Entering wait() Call to Wait on its Descendant\n", (long)getpid());
		if(getpid() == parent_pid){
			sprintf(cmd,"pstree -np -C age %d", parent_pid);
			int result = system(cmd);
			if(result < 0) fprintf(stdout, "Error in pstree Command");
		}
		pid_t pid3 = wait(&status);
		explain_wait_status(pid3, status);
		printf("Process with PID = %ld - Exiting wait() Call and Terminating With Status %d Because its Descendant Terminated\n", (long)getpid(), B);
		exit(B);
	}
}
