/*
 * exec.c
 * 
 * Copyright 2023  <>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int scelta;
	char *msg="operazione fallita";
	char *const argument[] = {"ls", "-l", NULL};	// vettore di argomenti per la 3 + 4
	char *const envp[] = {"PATH=/bin:/usr/bin", NULL};	// vettore variabili d'ambiente PATH per la 4
	
	printf("\t\tMENU\n1: date (execl)\n2: ls -l (execlp)\n3: ls -l (execv)\n4: ls -l (execve)\n\n");
	scanf("%d", &scelta);
	
	switch(scelta){
		case 1:
		execl("/bin/date", "date", NULL);
		puts(msg);	//se la exec fallisce, si esegue la puts e la exit
		exit(1);

		case 2:
		execlp("ls", "ls", "-l", NULL);
		puts(msg);
		exit(1);
		
		case 3:
		execv("/bin/ls", argument);	//execV ---> Vettore di argomenti
		puts(msg);
		exit(1);
		
		case 4:
		execve("/bin/ls", argument, envp);
		puts(msg);
		exit(1);
	}
	
	return 0;
}

