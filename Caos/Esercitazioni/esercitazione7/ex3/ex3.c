#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/string.h>

int arg=0;

char *array_of_string[20]; //format stringa:value
module_param_array(array_of_string,charp,&arg,0644);
MODULE_PARM_DESC(array_of_string,"array of strings");

int lenght=0;
module_param(lenght,int,0644);
MODULE_PARM_DESC(lenght,"lengh of array");


static int __init init_f(void){

    pr_info("Module loaded\n");

    if(lenght==0 || array_of_string==NULL){
        pr_info("The user have to be initialize the parameters\n");
    }

    else{
        for(int i = 0; i< lenght; i++){
            pr_info("Element %d: %s\n",i,array_of_string[i]);
        }
    }

    return 0;

}

static void __exit exit_f(void){
    int param;
    char str[20];
    int acc=0;

    for(int i = 0; i< lenght; i++){
        sscanf(array_of_string[i], "%19[^:]:%d", str, &param);
        acc +=param;
    }

    pr_info("Sum: %d\n",acc);

    pr_info("Module exit\n");

}

module_init(init_f);
module_exit(exit_f);
MODULE_LICENSE("gpl");