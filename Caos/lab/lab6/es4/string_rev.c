/* String manipulation */
#include <linux/string.h>
#include <linux/printk.h>
#include <linux/module.h>
#include "string_rev.h"

#include "string_rev.h"



int rev_string(char* stringa){
    char tmp;
    int n = strlen(stringa);

    for(int i = 0;i<n/2;i++){
        tmp = stringa[i];
        stringa[i] = stringa[n-i-1];
        stringa[n-i-1]=tmp; 

    }
    return 0;
    
}

MODULE_LICENSE("GPL");

