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
	//Parent - Process A
	for(int i = 0; i < atoi(argv[1]); i++){
		pid = fork();
	}
	if(pid<0){
		printf("Error in Fork\n");
	}
	else if(pid==0){
		//Child - Process D
		sleep(10);
		exit(D);
	}
	else{
		//Parent - Process B
		int status;
		pid_t pid3 = wait(&status);
		if(getpid() == parent_pid){
			printf("Terminated\n");
		}
		exit(B);
	}
}
