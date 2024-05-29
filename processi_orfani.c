#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char** argv){
pid_t pid;

printf("%p && %p\n", getpid(), getppid());

if ((pid = fork()) <0){
// errore
puts("error");
}
else if(pid==0){
// figlio
printf("[figlio] pid figlio= %d\t pid genitore = %d\n", getpid(), getppid());
}

else{
//genitore
sleep(3);
printf("[genitore] pid= %d\t pid genitore %d\n", getpid(), getppid());
printf("[genitore] pid figlio = %d\n", pid);
}


return 0;
}
