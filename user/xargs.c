#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(char argc, char *argv[])
{
sleep(10);
//获取标准化输入
char buf[MAXARG];
read(0,buf,MAXARG);


//截取输入参数echo
// echo hello too | xargs echo bye
// $ echo "1\n2" | xargs -n 1 echo line
// line 1
// line 2
char *p=buf;
int tag=0;
char *xargv[MAXARG];
for(int i=1;i<argc;++i)
{
    xargv[tag]= argv[i];
    tag++;
}


for(int i=0;i<MAXARG;++i)
{
    if(buf[i] == '\n')
    {
        if(fork()>0)
        {
            
            p = &buf[i+1];
            wait(0);

        }else{
            buf[i]=0;
            xargv[tag]=p;
            tag++;
            xargv[tag]=0;
            exec(xargv[0],xargv);
            exit(0);

        }
    }


}

exit(0);
}