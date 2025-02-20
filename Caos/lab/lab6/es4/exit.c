/* Needed by all modules */
#include <linux/module.h>

/* Needed for pr_info() */
#include <linux/printk.h>

static void __exit congrats_module(void){
	/* Print sum*/
	pr_info("Congratulations! You created your first multi-file module\n");
}

module_exit(congrats_module);

MODULE_LICENSE("GPL");

