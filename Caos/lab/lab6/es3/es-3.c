#include <linux/init.h>
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

static int myintarray[5] = { 0, 1, 0, 2, 3 };
static int sum = 0;
static int arr_argc = 0;

module_param_array(myintarray,int,&arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init es2_init(void){
    pr_info("Es3 init\n");
    for(int i = 0; i<5; i++){
        sum = sum + myintarray[i];
    }

    return 0;
}

static void __exit es2_exit(void){
    pr_info("Sum: %d",sum);
    pr_info("Es3 exit\n");
}

module_init(es2_init);
module_exit(es2_exit);