#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
pid_t pid;

// pid < ppid && ppid > pid
printf("prima della fork: pid = %d\tpid genitore = %d\n", getpid(), getppid());

if( (pid = fork()) < 0 ){
// errore
puts("errore_durante_fork");
}
else if(pid== 0){
// figlio
printf("[figlio] valore restituito dalla fork = %d\n", pid);    // = 0
printf("[figlio] pid = %d\tpid genitore = %d\n", getpid(), getppid());
}


else{
// genitore
printf("[genitore] valore restituito dalla fork = %d\n", pid);
printf("[genitore] pid = %d\tpid genitore = %d\n", getpid(), getppid());
printf("[genitore] il figlio ha pid = %d\n", pid);
}

return 0;
}
