#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main(char argc,char *argv[])
{
    if(argc != 2)
    {
        printf("sleep error\n");
        exit(1);
    }else
    {
        
        sleep(atoi(argv[1]));
        printf("nothing happens for a little while");
        exit(0);
    }
    
}