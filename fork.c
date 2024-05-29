/*
 * fork.c 
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	
	pid_t pid; char *message; int n=0;
	
	printf("fork program starting\n");
	
	pid=fork();
	
	switch(pid){
		
		case -1:
		perror("fork failed");
		exit(1);	// non c'e' bisogno il break perche' gia' esce
		
		case 0:	// il figlio esegue 5 volte terminando dopo il padre
		message= "this is the child";  // fork ok
		n=5;
		break;
		
		default:	// il padre esegue 3 volte e termina prima del figlio, facendo ritornare la shell
		message="this is the parent";
		n=3;
		break;
	}	// fine switch
	
	for (; n>0; n--){
		puts(message);
		sleep(2);
		
	}
	exit(0);
}

