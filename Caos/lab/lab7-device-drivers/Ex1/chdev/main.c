#include <stdio.h>
/* Include open */ 
#include <fcntl.h>
/* Include close */ 
#include <unistd.h>
/* Include exit */ 
#include <stdlib.h>

#include "shared.h"


int main(){
    int file_desc; 
	int bytes_read;
    int array_size = 5;
	int array[array_size];
    int result[array_size];

    char write_buffer[array_size*2];
    char read_buffer[array_size*2];
	
    for(int i = 0; i < 5; i++) {
        array[i] = i + 1;  // Aggiungi i numeri da 1 a 5
    }

    file_desc = open(DEVICE_PATH, O_RDWR);

    if (file_desc < 0) { 

        printf("Can't open device file: %s, error:%d\n", DEVICE_PATH,file_desc); 

        exit(EXIT_FAILURE); 
    } 

    array_to_string(array, array_size, write_buffer);

    printf("The array is: %s\n", write_buffer);
    
    write(file_desc, write_buffer, array_size*2);

    read(file_desc,read_buffer,array_size*2);

    printf("The sum is: %s\n", read_buffer);

    close(file_desc);
    return 0;

}