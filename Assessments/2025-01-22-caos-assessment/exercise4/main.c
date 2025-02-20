#include <linux/init.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/moduleparam.h> 
#include <linux/printk.h> 
#include <linux/stat.h> 

MODULE_LICENSE("GPL"); 

static int lenght = 0; 
static char *mystring = NULL; 
static int myintarray[20];
static int argc; 

module_param_array(myintarray, int, &argc, 0000); 
MODULE_PARM_DESC(myintarray, "An array of integers"); 
module_param(lenght, int, 0644); 
MODULE_PARM_DESC(lenght, "lenght of vector"); 
module_param(mystring, charp, 0644); 
MODULE_PARM_DESC(mystring, "A string"); 
 

static int __init init_f(void) 

{ 

    pr_info("Kernel module Init\n");

    //function implemented
    //print the char of string in position given by vector

    if(lenght == 0 || myintarray == NULL || mystring == NULL){
        pr_info("error during passing parameters\n");
        return -1;
    }

    for(int i = 0; i< lenght ; i++){
        pr_info("%c",mystring[myintarray[i]]);
    }
    pr_info("\n");
    return 0; 

} 

 

static void __exit exit_f(void) 

{ 

    pr_info("Kernel Module exit\n"); 

} 

 

module_init(init_f); 

module_exit(exit_f);