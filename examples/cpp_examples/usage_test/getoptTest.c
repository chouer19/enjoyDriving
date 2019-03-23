#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

    int opt;

    while((opt = getopt(argc, argv, "a:bcdefg") ) != -1){
        switch(opt){
            case 'a':{
                printf("-a:%s\n",optarg);
                printf("-a:%s\n",atoi(optarg));
                break;
            }
            case 'b':{
                printf("-b:");
                printf("-b:");
                break;
            }

            default:{break;}
        }
    }
    return 0;
}

