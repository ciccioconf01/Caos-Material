#include <linux/module.h>     // Inclusione per i moduli del kernel
#include <linux/kernel.h>     // Inclusione per la gestione dei log del kernel (printk)
#include <linux/init.h>       // Inclusione per la gestione delle funzioni di inizializzazione e pulizia
#include <linux/delay.h>      // Inclusione per msleep (delays)
#include <linux/string.h>

char *stringa;

module_param(stringa,charp,0644);
MODULE_PARM_DESC(stringa,"stringa");

static int __init f_init(void){
    pr_info("Module loaded\n");

    pr_info("The lenght of the passed string is: %d\n",strlen(stringa));

    return 0;
}

static void __exit f_exit(void){
    pr_info("Module exit\n");
}

module_init(f_init);
module_exit(f_exit);

MODULE_LICENSE("gpl");
