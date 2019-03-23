#include <string.h>
#include <stdio.h>

char comports[22][13]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
                       "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
                       "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
                       "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5"};

int main(int argc, char *argv[]){
    if(argc < 2){
       return 0;
    }

    for(int i=0; i < 22;i++){
        if(!strcmp(argv[1],comports[i])){
            printf("equal with %d!\n",i);
            return 1;
        }
    }
    printf("no equal port!\n");
    return 0;
}
