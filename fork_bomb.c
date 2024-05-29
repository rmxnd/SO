#include <stdio.h>
#include <unistd.h>

int main()
{
    while(1){
 if(fork() <0){ // quando la memoria sar' esaurta, fork sara' <0
    printf("Hello World");
   return 0;    // senno blocca tutto
}
}
    return 0;
}
