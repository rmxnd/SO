/*
 * prova_fork_waitpid.c
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv)
{
	pid_t pid1;
	const char *message_fail = "fork fallita\n";
	
	pid1 = fork();
	
	if (pid1 > 0){
		// padre attende terminazione figlio
		int status;
		printf("fork andata a buon fine con pid >0\n");
		waitpid(pid1, &status, 0);
		
		
				// esecuzione secondo figlio
				pid_t pid2;
				
				pid2= fork();
				
				if (fork > 0){
					int status2;
					printf("seconda fork ok, pid >0\n");
					waitpid(pid2, &status2, 0);
				} else if (pid2 == 0){
					printf("seconda fork ok pid ==0\n");
				} else if (pid2 == -1){
					puts(message_fail);
					exit(1);
					} else printf("caso non previsto");
				// fine secondo figlio
			
		printf("sono il padre con pid = %d\nattendo terminazione del figlio con pid: %d e status = %d\n"
		"eseguo upgrade\n\n", getpid(), pid1, status);
		execl("/bin/sudo", "sudo", "apt", "full-upgrade", NULL);
		printf("exec fallita"); // esegue solo se la exec fallisce
		exit(1); 
	} 
	else if (pid1 == -1) {
		puts(message_fail);
		exit(1);
		}
		else if (pid1 == 0) {
		printf("fork andata a buon fine con pid =0\n"
		"il figlio ha pid = %d\n", getpid());
		execl("/bin/sudo", "sudo", "apt", "update", NULL);
		printf("exec fallita"); // esegue solo se la exec fallisce
		exit(1); 
		}
	else printf("caso non previsto");
	
	return 0;
}

