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

void main(){
	int A = 2;
	int B = 4;
	int C = 6;
	int D = 10;
	char cmd[50];
	//Parent - Process A
	printf("Process A (PID = %ld) - Start and Forking Child (Process B)\n", (long)getpid());
	pid_t pid = fork();
	if(pid<0){
		printf("Error in Fork\n");
	}
	else if(pid==0){
		//Child - Process B
		printf("Process B (PID = %ld) - Start and Forking Child (Process D)\n", (long)getpid());
		pid_t pid2 = fork();
		if(pid2<0){
			printf("Error in Fork\n");
		}
		else if(pid2==0){
			//Child - Process D
			printf("Process D (PID = %ld) - Start and Entering sleep() Call\n", (long)getpid());
			sleep(10);
			printf("Process D (PID = %ld) - Exiting sleep() Call and Terminating With Status %d\n", (long)getpid(), D);
			exit(D);
		}
		else{
			//Parent - Process B
			int status;
			printf("Process B (PID = %ld) - Entering wait() Call to Wait on its Descendant (Process D)\n", (long)getpid());
			pid_t pid3 = wait(&status);
			explain_wait_status(pid3, status);
			printf("Process B (PID = %ld) - Exiting wait() Call and Terminating With Status %d Because its Descendant (Process D) Terminated\n", (long)getpid(), B);
			exit(B);
		}
	}
	else {
		//Parent - Process A
		printf("Process A (PID = %ld) - Forking Second Child (Process C)\n", (long)getpid());
		pid_t pid4 = fork();
		if(pid4<0){
			printf("Error in Fork\n");
		}
		else if(pid4==0){
			//Child - Process C
			printf("Process C (PID = %ld) - Start and Entering sleep() Call\n", (long)getpid());
			sleep(10);
			printf("Process C (PID = %ld) - Exiting sleep() Call and Terminating With Status %d\n", (long)getpid(), C);
			exit(C);
		}
		else{
			//Parent - Process A
			int status;
			printf("Process A (PID = %ld) - Entering wait() Call to Wait on its Descendants (All Other Processes)\n", (long)getpid());
			sprintf(cmd,"pstree -np -C age %d", pid4);
			int result = system(cmd);
			if(result < 0) fprintf(stdout, "Error in pstree Command");
			pid_t pid5 = wait(&status);
			explain_wait_status(pid5, status);
			printf("Process A (PID = %ld) - Exiting wait() Call and Terminating With Status %d Because One of its Descendants (Any Other Process) Terminated\n", (long)getpid(), A);
			exit(A);
		}
	}
}
