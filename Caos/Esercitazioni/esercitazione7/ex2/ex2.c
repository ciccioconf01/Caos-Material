#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>


static int delay = -1;
module_param(delay,int,0644);
MODULE_PARM_DESC(delay,"ms of delay");

static int __init init_f(void){

    pr_info("Module loaded\n");
    if(delay==-1){
        pr_info("The user have to insert the delay value\n");
    }

    else{
        pr_info("Starting loop...\n");
        for (int i=0;i<10;i++){
            pr_info("Cycle n: %d\n",i);
            msleep(delay);
        }
    }

    return 0;

    
}

static void __exit exit_f(void){

    pr_info("Exiting Module\n");

}

module_init(init_f);
module_exit(exit_f);

MODULE_LICENSE("gpl");
