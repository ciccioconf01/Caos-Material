#include <linux/init.h>
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

static int value = -1;

module_param(value, int, 0644);  // Parametro del modulo
MODULE_PARM_DESC(value, "An integer parameter");

// Funzione di inizializzazione del modulo
static int __init mio_modulo_init(void)
{
    pr_info("Modulo caricato!\n");  // Messaggio di log

    if (value == -1) {
        pr_info("The user did not insert a number.\n");
    } else {
        pr_info("The number inserted by the user is: %d\n", value);
    }

    return 0;  // Successo
}

// Funzione di uscita del modulo
static void __exit mio_modulo_exit(void)
{
    pr_info("Modulo scaricato!\n");  // Messaggio di log
}

// Specifica le funzioni di inizializzazione ed uscita
module_init(mio_modulo_init);
module_exit(mio_modulo_exit);

// Definisce alcune informazioni sul modulo
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tuo Nome");
MODULE_DESCRIPTION("Modulo di esempio con parametro");
