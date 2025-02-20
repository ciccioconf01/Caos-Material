//user_app.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/ioctl.h>

#define NAME "led" 
#define DEVICE_PATH "/dev/"NAME

int main (){

    int fd;
    fd = open(DEVICE_PATH,O_RDWR);

    if(fd < 0){
        printf("Error during opening file\n");
        return -1;
    }

    char interval[5];
    strcpy(interval,"1000");
    char stringF[5];
    char stringF2[5];
    char stringF3[5];

    write(fd,interval,5);

    read(fd,stringF,5);

    printf("Value is: %s\n",stringF);

    ioctl(fd,0,"2000"); //scrittura valore 2000
    read(fd,stringF2,5);

    printf("Value is: %s\n",stringF2);

    ioctl(fd,0,"1.300"); //scrittura valore 3000

    read(fd,stringF3,5);

    printf("Value is: %s\n",stringF3);

    return 0;
    
}