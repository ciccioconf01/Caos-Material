#include <linux/init.h> 
#include <linux/kernel.h> /* for ARRAY_SIZE() */ 
#include <linux/module.h> 
#include <linux/moduleparam.h> 
#include <linux/printk.h> 
#include <linux/stat.h> 

static int vet[10];
static int lenght = 0;
static char *string;
int arg;

module_param(string,charp,0644);
MODULE_PARM_DESC(string,"stringa");

module_param_array(vet,int,&arg,0644);
MODULE_PARM_DESC(vet,"vet of integers");

module_param(lenght,int,0644);
MODULE_PARM_DESC(lenght,"vet lenght");

static int __init init_func( void ){
    pr_info("Init function\n");

    if(vet == NULL || string== NULL || lenght == 0){
        pr_info("Error\n");
        return -1;
    }

    char res[20];
    for(int i=0; i<lenght; i++){
        res[i] = string [vet [i]];
    }

    pr_info("Final string: %s\n",res);
    return 0;
}

static void __exit exit_func(void){
    pr_info("Exiting\n");
}

module_init(init_func);
module_exit(exit_func);
MODULE_LICENSE("gpl");