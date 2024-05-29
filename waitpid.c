/*
 * waitpid.c
 * waitpid() NON bloccante tramite uso di WNOHANG per fare controllare al padre se il figlio ha terminato
 WNOHANG = 0 se il figlio NON ha terminato;
 * 		 = pid_del_figlio se il figlio ha terminato;
 * 		 = -1 errore
 * WIFEXITED e' !=0 se il figlio termina normalmente
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid; char *message; int n, stat_val, exit_code;
	
	pid = fork();
	
	switch (pid) 
	{
		case -1:
		perror("fork failed");
		exit(1);
		
		case 0:
		message="this is the child";
		n=3;
		exit_code=37; //numero a caso
		break;
		
		default:
		message="this is the parent";
		n=5;
		exit_code=0;
		break;
	}
	
	for(; n>0; n--){
		printf("PID: %d ", getpid());
		puts(message);
		sleep(1);	
	}
	
	if (pid != 0) { // codice processo padre
		pid_t child_pid;
		
		child_pid= waitpid(pid, &stat_val, WNOHANG);
		/* pid = ritornato dalla fork, stat_val= stato terminazione del figlio, 
		 WNOHANG=0 <---> child ha finito oppure = PID_del_figlio <---> child ha finito */
			
			if (child_pid)
			{
			printf("child has finished: PID= %d\n", child_pid);
			
			if( WIFEXITED(stat_val)) 
			printf("child exited with code %d\n", WEXITSTATUS(stat_val));
			else 
			printf("child terminated abnormally \n");
			}
	exit(exit_code);
	}
	
	return 0;
}

