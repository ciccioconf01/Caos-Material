//exit.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static void __exit exit_f(void){
    pr_info("Exit Module\n");
}

module_exit(exit_f);
MODULE_LICENSE("GPL");