/* 

 * chardev.c: Creates a read-only char device that says how many times 

 * you have read from the dev file 

 */ 

 

#include <linux/atomic.h> 

#include <linux/cdev.h> 

#include <linux/delay.h> 

#include <linux/device.h> 

#include <linux/fs.h> 

#include <linux/init.h> 

#include <linux/kernel.h> /* for sprintf() */ 

#include <linux/module.h> 

#include <linux/printk.h> 

#include <linux/types.h> 

#include <linux/uaccess.h> /* for get_user and put_user */ 

#include <linux/version.h> 

 

#include <asm/errno.h> 

 

/*  Prototypes - this would normally go in a .h file */ 

static int device_open(struct inode *, struct file *); 

static int device_release(struct inode *, struct file *); 

static ssize_t device_read(struct file *, char __user *, size_t, loff_t *); 

static ssize_t device_write(struct file *, const char __user *, size_t, 

                            loff_t *); 

static long device_ioctl(struct file *file, unsigned int ioctl_num,unsigned long ioctl_param);

 

#define SUCCESS 0 

#define DEVICE_NAME "chardev" /* Dev name as it appears in /proc/devices   */ 

#define BUF_LEN 80 /* Max length of the message from the device */ 

 

/* Global variables are declared as static, so are global within the file. */ 

 

static int major; /* major number assigned to our device driver */ 

static int counter = 0;
 

enum { 

    CDEV_NOT_USED, 

    CDEV_EXCLUSIVE_OPEN, 

}; 

 

/* Is device open? Used to prevent multiple access to device */ 

static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED); 

 

static char msg[BUF_LEN + 1]; /* The msg the device will give when asked */ 

 

static struct class *cls; 

 

static struct file_operations chardev_fops = { 

    .read = device_read, 

    .write = device_write, 

    .open = device_open, 

    .release = device_release, 

    .unlocked_ioctl = device_ioctl, 

}; 

 

static int __init chardev_init(void) 

{ 

    major = register_chrdev(0, DEVICE_NAME, &chardev_fops); 

 

    if (major < 0) { 

        pr_alert("Registering char device failed with %d\n", major); 

        return major; 

    } 

 

    pr_info("I was assigned major number %d.\n", major); 

 

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0) 

    cls = class_create(DEVICE_NAME); 

#else 

    cls = class_create(THIS_MODULE, DEVICE_NAME); 

#endif 

    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME); 

 

    pr_info("Device created on /dev/%s\n", DEVICE_NAME); 

 

    return SUCCESS; 

} 

 

static void __exit chardev_exit(void) 

{ 

    device_destroy(cls, MKDEV(major, 0)); 

    class_destroy(cls); 

 

    /* Unregister the device */ 

    unregister_chrdev(major, DEVICE_NAME); 

} 

 

/* Methods */ 

 

/* Called when a process tries to open the device file, like 

 * "sudo cat /dev/chardev" 

 */ 

static int device_open(struct inode *inode, struct file *file) 

{ 

    static int counter = 0; 

 

    if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN)) 

        return -EBUSY; 

 

    sprintf(msg, "I already told you %d times Hello world!\n", counter++); 

    try_module_get(THIS_MODULE); 

 

    return SUCCESS; 

} 

 

/* Called when a process closes the device file. */ 

static int device_release(struct inode *inode, struct file *file) 

{ 

    /* We're now ready for our next caller */ 

    atomic_set(&already_open, CDEV_NOT_USED); 

 

    /* Decrement the usage count, or else once you opened the file, you will 

     * never get rid of the module. 

     */ 

    module_put(THIS_MODULE); 

 

    return SUCCESS; 

} 

 

/* Called when a process, which already opened the dev file, attempts to 

 * read from it. 

 */ 

static ssize_t device_read(struct file *filp, /* see include/linux/fs.h   */ 

                           char __user *buffer, /* buffer to fill with data */ 

                           size_t length, /* length of the buffer     */ 

                           loff_t *offset) 

{ 

    /* Number of bytes actually written to the buffer */ 

    int bytes_read = 0; 

    const char *msg_ptr = msg; 

 

    if (!*(msg_ptr + *offset)) { /* we are at the end of message */ 

        *offset = 0; /* reset the offset */ 

        return 0; /* signify end of file */ 

    } 

 

    msg_ptr += *offset; 

 
    char str[20];
    int i=0;
    snprintf(str,sizeof(str),"%d",counter);

    while (str[i]!='\0') { 

        put_user(str[i], buffer+i); 
        bytes_read++;
        i++;

    } 

 
    put_user('\0', buffer+i); 
    return bytes_read; 

} 

 

/* Called when a process writes to dev file: echo "hi" > /dev/hello */ 

static ssize_t device_write(struct file *filp, const char __user *buff, size_t len, loff_t *off) 

{ 
    char str[len];
    int byte_write=0;

    for(int i = 0; i < len; i++){
        get_user(str[i],buff+i);
        byte_write++;
    }

    if(buff[0] == 'u' && buff[1]== 'p'){
        counter++;
    }

    else{
        counter--;
    }

    return byte_write;

} 

static long device_ioctl(struct file *file, unsigned int ioctl_num,unsigned long ioctl_param) 

{ 
    long ret = SUCCESS;

    switch (ioctl_num) { 

    case 0: { 

        char value[5];
        value[0] = 'u';
        value[1] = 'p';
        counter = 0;
        for(int i = 0; i < ioctl_param; i++){
            device_write(file,value,5,0);
        }
        break; 

    } 

    case 1: { 

        counter = 0;

        break; 

    } 


    } 
 

    return ret; 

} 

 

module_init(chardev_init); 

module_exit(chardev_exit); 

 

MODULE_LICENSE("GPL");