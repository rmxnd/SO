/*
system.c
 */

#include <stdlib.h>

int main(int argc, char **argv)
{
	system("sudo apt update -y && sudo apt install unattended-upgrades -y && sudo apt full-upgrade -y && sudo apt autoremove && sudo apt autoclean");
	return 0;
}