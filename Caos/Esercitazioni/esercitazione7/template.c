#include <linux/module.h>     // Inclusione per i moduli del kernel
#include <linux/kernel.h>     // Inclusione per la gestione dei log del kernel (printk)
#include <linux/init.h>       // Inclusione per la gestione delle funzioni di inizializzazione e pulizia
#include <linux/fs.h>         // Inclusione per la gestione dei file system, se necessario
#include <linux/slab.h>       // Inclusione per l'allocazione dinamica della memoria (kmalloc, kfree)
#include <linux/delay.h>      // Inclusione per msleep (delays)
#include <linux/uaccess.h>    // Inclusione per la gestione dei dati tra spazio utente e spazio kernel


// Definizione della licenza del modulo
MODULE_LICENSE("GPL");             // La licenza deve essere sempre GPL per i moduli kernel
MODULE_AUTHOR("Your Name");        // Sostituire con il proprio nome
MODULE_DESCRIPTION("Base Kernel Module Template");  // Una breve descrizione del modulo

// Funzione di inizializzazione del modulo
static int __init my_module_init(void)
{
    printk(KERN_INFO "Module loaded: Hello, Kernel!\n");
    // Inizializzazione e altre operazioni vanno qui
    return 0;  // Se la funzione di inizializzazione va a buon fine, deve restituire 0
}

// Funzione di pulizia del modulo
static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Module unloaded: Goodbye, Kernel!\n");
    // Operazioni di pulizia vanno qui, come il rilascio delle risorse allocate
}

// Macro per dichiarare la funzione di inizializzazione e di pulizia
module_init(my_module_init);  // Imposta la funzione di inizializzazione
module_exit(my_module_exit);  // Imposta la funzione di pulizia

