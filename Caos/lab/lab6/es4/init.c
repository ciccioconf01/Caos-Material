/* Needed by all modules */
#include <linux/module.h>

/* Needed for pr_info() */
#include <linux/printk.h>

#include "string_rev.h"
static char stringa[] = "porcodio";


static int __init init_e4(void)
{
    pr_info("Original string: %s\n",stringa);
    rev_string(stringa);

    pr_info("Reversed string: %s\n",stringa);
    return 0;
}

module_init(init_e4);
MODULE_LICENSE("GPL");
