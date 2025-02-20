#include <linux/init.h>
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static int myint = 10;
static int n = 20;

module_param(myint,int,0644);
MODULE_PARM_DESC(myint,"integer");

module_param(n,int,0644);
MODULE_PARM_DESC(n,"number of cycles");

static int __init es2_init(void){
    for(int i = 0; i<n; i++){
        pr_info("Number: %d\n",myint);
        msleep(1000);
    }

    return 0;
}

static void __exit es2_exit(void){
    pr_info("Es2 exit\n");
}

module_init(es2_init);
module_exit(es2_exit);