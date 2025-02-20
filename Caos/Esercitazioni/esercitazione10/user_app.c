#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/ioctl.h>


int main (){

    int fd;
    char str[10];
    strcpy(str,"up");
    char str2[10];
    strcpy(str2,"down");

    char strF[10];

    fd = open("/dev/chardev",O_RDWR);

    if(fd<0){
        printf("Errore nell'apertura del file\n");
        return -1;
    }
    else{
        printf("file aperto\n");
    }

    
    write(fd,str,strlen(str));
    read(fd,strF,strlen(strF));
    printf("counter value: %s\n",strF);

    write(fd,str2,strlen(str2));
    read(fd,strF,strlen(strF));
    printf("counter value: %s\n",strF);

    write(fd,str,strlen(str));
    write(fd,str,strlen(str));
    read(fd,strF,strlen(strF));
    printf("counter value: %s\n",strF);

    ioctl(fd,0,5); //set the counter to 5
    read(fd,strF,strlen(strF));
    printf("counter value: %s\n",strF);

    int nope = 0;
    ioctl(fd,1,nope); //reset the counter
    read(fd,strF,strlen(strF));
    printf("counter value: %s\n",strF);

}