#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"




int main(char argc,char *argv[])
{
    int p1[2],p2[2];
    char buf1[16],buf2[16];

    pipe(p1);
    pipe(p2);
    if(fork()==0)
    {
        int pid_child =getpid();
        close(p1[1]);
        read(p1[0],buf1,sizeof(buf1));
        printf("%d : %s\n", pid_child,buf1);
        close(p2[0]);
        write(p2[1],"received pong",sizeof(buf2));
        exit(0);

    }else{
        close(p1[0]);
        write(p1[1],"received ping",sizeof(buf2));
        close(p2[1]);
        int pid_father = getpid();
        read(p2[0],buf2,sizeof(buf2));
        wait(0);
        printf("%d : %s\n",pid_father,buf2);
        exit(0);
       
       
    }
  
}
