#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static char *stringa1 = NULL;
static char *stringa2 = NULL;

static int vet[2] = {-1,-1};
int arg;

static char stringaF[20];

module_param(stringa1,charp,0644);
MODULE_PARM_DESC(stringa1,"stringa1");

module_param(stringa2,charp,0644);
MODULE_PARM_DESC(stringa2,"stringa2");

module_param_array(vet,int,&arg,0644);
MODULE_PARM_DESC(vet,"vet of int");


static int __init init_f(void){
    pr_info("Module Loaded\n");

    if (stringa1 == NULL || stringa2 == NULL || vet[0] == -1 || vet[1] == -1){
        pr_info("You have to load the parameters\n");
        return -1;
    }
    int index=0;
    for(int i = 0; i<vet[0]; i++){
        stringaF[index] = stringa1[i];
        index++;
    }

    for(int i = 0; i<vet[1]; i++){
        stringaF[index] = stringa2[i];
        index++;
    }

    stringaF[index] = '\0';

    pr_info("%s\n",stringaF);

    return 0;

}

module_init(init_f);
MODULE_LICENSE("gpl");