#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>

#include "shared.h"

int main (){
    int size_vet1 = 4;
    int size_vet2 = 2;
    int vet1[size_vet1];
    for (int i = 0; i<size_vet1;i++){
        vet1[i] = i;
    }
    int vet2[size_vet2];
    for (int i = 0; i<size_vet2;i++){
        vet2[i] = i;
    }

    char stringa1[size_vet1*2];
    char stringa2[size_vet2*2];


    char stringaF[size_vet1*2 + size_vet2*2];

    int fd = open ("/dev/device", O_RDWR);
    if (fd < 0){
        printf("Error\n");
        return -1;
    }

    array_to_string(vet1,size_vet1,stringa1);

    write (fd,stringa1,strlen(stringa1)+1);

    array_to_string(vet2,size_vet2,stringa2);
    
    write (fd,stringa2,strlen(stringa2)+1);

    read(fd,stringaF,size_vet1*2 + size_vet2*2);

    char stringa3[size_vet2*2];
    ioctl(fd,0,stringa3);

    printf("List size: %s\n",stringa3);

    ioctl(fd,1,NULL);

    return 0;
}