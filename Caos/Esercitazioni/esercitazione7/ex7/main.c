#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "shared.h"

#define DEVICE_PATH "/dev/dummy_device"

#define MAX_INT 3

int main() {
    
    int array[MAX_INT] = {1,2,3};

    char write_array[MAX_INT*2];
    char read_array[MAX_INT*2];
    int file_desc;

    file_desc = open(DEVICE_PATH,O_RDWR);

    if(file_desc < 0){
        printf("Error during the opening of the file\n");
    }

    array_to_string(array,MAX_INT,write_array);

    write(file_desc,write_array,MAX_INT*2);

    read(file_desc,read_array,MAX_INT*2);

    printf("The product of the elements of array is : %s\n",read_array);

    close(file_desc);

    
    return 0;
}
