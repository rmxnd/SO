/*
 * ciclo_for.sh
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	pid_t pid; int n, stat_val, exit_code; char *message;
	
	pid=fork();
	
		switch(pid){
		
		case -1:
		perror("fork failed");
		exit(1);	// 1 !=0 ---> errore = fork fallita
		
		case 0:	// fork ok ---> figlio
		message="this is the child";
		n=5	// ripeti 5 volte
		exit_code=37; // un numero a caso
		break;
		
		default:	// padre che chiama la fork
		message="this is the parent";
		n=3;
		exit_code=0;
		break;	
		}
	
	for(; n>0; n--){
	puts(message);
	sleep(1);		
	}
	
	if(pid !=0){	// esegue il padre
		pid_t child_pid;
		child_pid = wait(&stat_val);	// il padre si blocca in attesa del figlio
		printf("child ha finito: PID = %d\n", child_pid);
		
		if ( WIFEXITED(stat_val) )
		printf("child exited with code: %d\n", WEXITSTATUS(stat_val));
	}
	
	
	exit(0);
}

