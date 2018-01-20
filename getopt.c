#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  
#include <time.h>  
  
#ifdef _WIN32  
#include "getopt.h"  
#include <windows.h>  
#include <direct.h>  
#include <io.h>  
#else  
#include <unistd.h>  
#include <getopt.h>  
#endif  
  
#include <iostream>  
using namespace std;  
 
const int N = 300;

int clients=1;
static void usage(void)
{
   fprintf(stderr,
	"TEST [option]... TEST\n"
	"  -f|--force               TEST TEST TEST.\n"
	"  -r|--reload              TEST TEST TEST.\n"
	"  -t|--time <sec>          TEST TEST TEST.\n"
	);
};


void do_command(char *command){
    char line[N];
    FILE *fp;
    const char *sysCommand ;
      sysCommand = command;
    if ((fp = popen(sysCommand, "r")) == NULL) {
        cout << "error" << endl;
        return;
    }
    while (fgets(line, sizeof(line)-1, fp) != NULL){
        cout << line ;
    }
    pclose(fp);
}


int main(int argc, char *argv[])  
{  
    int ch;  
    //printf("%4d",clients);
    while ((ch = getopt(argc,argv,"a:b:c:de"))!=-1)  
    {  
        switch(ch)  
        {  
        case 'a':  
           printf("option a=%s\n",optarg);  
            break;  
        case 'b':  
            printf("option b=%s\n",optarg);  
            break;  
        case 'c':  
            printf("option c=%s\n",optarg); 
            do_command(optarg);
            break;  
        case '?':  
            printf("无效的选项字符 \'%c\'!\n", (char)optopt);  
            break;  
        case ':':  
            printf("缺少选项参数！\n");  
            break;  
        default:  
            printf("other option=%c\n",ch);  
            break;  
        }  
    } 

    // printf("%5d what s this \n",optind);
    if(optind==1) {
        fprintf(stderr,"no args\n");
        usage();
        return 2;
     } 
}
