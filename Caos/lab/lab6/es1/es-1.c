#include <linux/init.h>
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

static char *mystring = "Nothing";

module_param(mystring, charp, 0644);
MODULE_PARM_DESC(mystring,"A name of a person");

static int __init es1_init(void){

    pr_info("The person: %s, is great\n",mystring);
    return 0;

}

static void __exit es1_exit(void){

    pr_info("Es1 exit\n");

}

module_init(es1_init);
module_exit(es1_exit);

