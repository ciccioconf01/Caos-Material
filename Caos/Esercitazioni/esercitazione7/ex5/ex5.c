#include <linux/module.h>     // Inclusione per i moduli del kernel
#include <linux/kernel.h>     // Inclusione per la gestione dei log del kernel (printk)
#include <linux/init.h>       // Inclusione per la gestione delle funzioni di inizializzazione e pulizia
#include <linux/delay.h>      // Inclusione per msleep (delays)

static int val1 = -1;
static int val2 = -1;
static int operation = -1; //0 addition, 1 substraction, 2 multiplication, 3 division

module_param (val1,int,0644);
MODULE_PARM_DESC(val1,"first operand");

module_param (val2,int,0644);
MODULE_PARM_DESC(val2,"second operand");

module_param(operation,int,0644);
MODULE_PARM_DESC(operation,"operation");

static int __init f_init(void){
    int result;
    pr_info("Module loaded\n");

    if(val1==-1 || val2==-1 || operation==-1){
        pr_info("Insert the correct parameters from the command line\n");
        return 1;
    }

    if(operation==0){
        result = val1 + val2;
        pr_info ("%d + %d = %d\n",val1,val2,result);
    }
    else if(operation==1){
        result = val1 - val2;
        pr_info ("%d - %d = %d\n",val1,val2,result);
    }
    else if(operation==2){
        result = val1 * val2;
        pr_info ("%d * %d = %d\n",val1,val2,result);
    }
    else{
        result = val1 / val2;
        pr_info ("%d / %d = %d\n",val1,val2,result);
    }

    return 0;

}

static void __exit f_exit(void){
    pr_info("Module exiting\n");
}

module_init(f_init);
module_exit(f_exit);

MODULE_LICENSE("gpl");
