#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

void Prime(int *p);

int main(char argc,char *argv[])
{
    int p[2];
    pipe(p);
    int i;
    for( i=2;i<=35;i++)
    {
        write(p[1],&i,sizeof(i));
    }
    close (p[1]);

    if(fork()==0)
    {
        Prime(p);
        exit(0);
    }else{
        close (p[0]);
        wait(0);
        exit(0);
    }
}


void Prime(int *p)
{
    int prime_numb;
    int len;
    len =read(p[0],&prime_numb,sizeof(prime_numb));
    if(len ==0)
    {   
        close (p[0]);
        exit(0);
    }else{
        printf("preme %d\n",prime_numb);
    }


    int p_next [2];
    pipe(p_next);
    int num;

    if(fork()==0)
    {
        close (p[0]);
        close (p_next[1]);
        Prime(p_next);
        exit(0);
    }else{
       
        close (p_next[0]);
        while(read(p[0],&num,sizeof(num)))
        {
            if(num%prime_numb!=0)
            {
                write(p_next[1], &num,sizeof(num));
            }
            
        }
        close (p_next[1]);
        wait(0);
        exit(0);
    }
}