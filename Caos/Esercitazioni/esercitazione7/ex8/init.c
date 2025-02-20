//init.c
#include <linux/module.h>     // Inclusione per i moduli del kernel
#include <linux/kernel.h>     // Inclusione per la gestione dei log del kernel (printk)
#include <linux/init.h>       // Inclusione per la gestione delle funzioni di inizializzazione e pulizia

static int n = -1;

module_param(n,int,0644);
MODULE_PARM_DESC(n,"integer");

static int __init init_f (void){
    pr_info ("Module loaded\n");

    if(n == -1){
        pr_info ("Insert N\n");
        return -1;
    }

    int a = 0;
    pr_info("%d\n",a);
    int b = 1;
    pr_info("%d\n",b);
    int sum;
    for(int i = 0; i<n-2; i++){
        sum = a+b;
        pr_info("%d\n",sum);
        a = b;
        b = sum;
    }

    return 0;
}

module_init (init_f);

MODULE_LICENSE("GPL");