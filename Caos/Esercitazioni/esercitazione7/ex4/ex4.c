#include <linux/module.h>     // Inclusione per i moduli del kernel
#include <linux/kernel.h>     // Inclusione per la gestione dei log del kernel (printk)
#include <linux/init.h>       // Inclusione per la gestione delle funzioni di inizializzazione e pulizia
#include <linux/delay.h>      // Inclusione per msleep (delays)

static int conta = 0;

static int __init init_f(void) {
    
    pr_info("Module loaded\n");

    for(int i = 0; i<10; i++){
        pr_info("Value: %d",conta);
        conta++;
        msleep(1000);
    }

    pr_info("Timer out\n");
    

    return 0;
}

static void __exit exit_f(void) {
    pr_info("Module exit\n");
}

module_init(init_f);
module_exit(exit_f);
MODULE_LICENSE("GPL");
