/*
 * aggiorna.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf ("eseguendo 'sudo apt update -y'\n\n");
	system("sudo apt update -y");
	puts("\n\n");

	printf ("eseguendo 'sudo apt list --upgradable'\n\n"
	"i pacchetti upgradabili sono:\n");
	system("sudo apt list --upgradable");
	puts("\n\n");

	printf ("eseguendo 'sudo apt full-upgrade -y'\n\n");
	system("sudo apt full-upgrade -y");
	puts("\n\nFINE\n\n");

	exit(EXIT_SUCCESS);
}
