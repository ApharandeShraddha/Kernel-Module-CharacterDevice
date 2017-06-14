#include "process_list.h"
#include <linux/fs.h> 	 
#include <linux/kernel.h>    
#include <linux/errno.h>     
#include <linux/module.h>  
#include <asm/uaccess.h>  
#include <linux/miscdevice.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/init.h> 
#include <linux/cdev.h>
#include <linux/compiler.h> 

#define EFAULT 14 

__must_check int register_device(void); 
void unregister_device(void); 

//Pointer to interate through each process
struct task_struct *iter;

//buffer to store processes data
struct my_buf kbuf[MAX_BUF_SIZE];

//Number of processes
int cnt;

/*  This function is called whenever device is being read from user space
 *  copy_to_user() function to send the buffer string to the user and captures any errors
 *  @param file_ptr A pointer to a file object (defined in linux/fs.h)
 *  @param user_buffer The pointer to the buffer to which this function writes the data
 *  @param count
 *  @param offset 
 */
static ssize_t device_file_read(struct file *file_ptr, char __user *user_buffer, size_t count, loff_t *possition)
{
    int error_count =0;

    for_each_process(iter)
    {
     
       kbuf[cnt].pid=iter->pid;
       kbuf[cnt].ppid=iter->parent->pid;
       kbuf[cnt].state = iter->state;
       kbuf[cnt].cpu = task_cpu(iter);

       cnt++;
    }
      error_count = copy_to_user((struct my_buf*)user_buffer, kbuf, MAX_BUF_SIZE);

      if (error_count != 0){      
      
      printk(KERN_INFO "kernel: Failed to send %d characters to the user\n", error_count);
      return -EFAULT;              
  }

   return cnt;
}//end of device_file_read


/*  This function is called each time the device is opened
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param file A pointer to a file object (defined in linux/fs.h)
 */
static int my_open(struct inode *inodep, struct file *file) { 
    
       printk(KERN_INFO "Device has been successfully opened\n");

   return 0;
}//end of my_open


/* This function is called whenever the device is closed by the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param file A pointer to a file object (defined in linux/fs.h)
 */
static int my_close(struct inode *inodep, struct file *file){
     
  printk(KERN_INFO "Device has been successfully closed\n");

    return 0;
}

// Declaration of the file operations struct .Devices are represented as file structure in the kernel.
static struct file_operations my_fops = 
{
   .open    = my_open,
   .read    = device_file_read,
   .release = my_close,
};

// Declaration of a device struct
static struct miscdevice my_misc_device = { 
    .minor = MISC_DYNAMIC_MINOR, 
    .name = "process_list",
    .fops = &my_fops
};




//This function register the device with kernel
int register_device(void)
{
      int result = 0;
      result =misc_register(&my_misc_device);
    
      if( result < 0 )
      {
         printk( KERN_WARNING "Device regitsration failed with errorcode = %i", result );
         return result;
      }

      printk( KERN_NOTICE "Character Device registered Successfully");

      return 0;
}//end of register_device

//This function unregister the device from kernel
void unregister_device(void)
{
   printk( KERN_NOTICE "character device unregistered" );
   misc_deregister(&my_misc_device);
}

//This is initialization function at insertion time of kernel module
static int processList_init(void)
{
      int result = 0;
      printk( KERN_NOTICE "process_list :Initialization started" );

        result = register_device();
      return result;
}

//This is initialization function at removal(cleanup) time of kernel module
static void processList_exit(void)
{
    printk( KERN_NOTICE "process_list: Exiting" );
    unregister_device();
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shraddha");
module_init(processList_init);
module_exit(processList_exit);