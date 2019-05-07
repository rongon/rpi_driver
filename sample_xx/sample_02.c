#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define DRIVER_NAME "sample_02_driver"
#define DEVICE_NAME "sample_02_device"

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Kenji Seto");
MODULE_DESCRIPTION("Sample Driver #02");

static int __init my_module_init(void);
static void __exit my_module_exit(void);
static int my_open(struct inode* inode, struct file* filp);
static int my_close(struct inode* inode, struct file* filp);
static ssize_t my_read(struct file* file, char* buff, size_t count, loff_t* pos);
static ssize_t my_write(struct file* file, const char * buff, size_t count, loff_t *pos);
static long my_ioctl(struct file* filp, unsigned int cmd, unsigned long arg);

static const unsigned int MINOR_NUMBER_START = 0; /* the minor number starts at */
static const unsigned int NUMBER_MINOR_NUMBER = 1; /* the number of minor numbers */
static unsigned int major_number; /* the major number of the device */
static struct cdev my_char_dev; /* character device */
static struct class* my_char_dev_class = NULL; /* class object */

struct file_operations my_file_ops = {
  .owner          = THIS_MODULE,
  .open           = my_open,
  .release        = my_close,
  .read           = my_read,
  .write          = my_write,
  .unlocked_ioctl = my_ioctl, /* 64 bits */
  .compat_ioctl   = my_ioctl, /* 32 bits */
};

static int my_module_init(void)
{
  int alloc_ret;
  int cdev_err;
  dev_t dev;

  /* get not assigned major numbers */
  alloc_ret = alloc_chrdev_region(&dev, MINOR_NUMBER_START, NUMBER_MINOR_NUMBER, DRIVER_NAME);
  if (alloc_ret != 0) {
    printk(KERN_ERR "failed to alloc_chrdev_region()\n");
    return -1;
  }

  /* get one number from the not-assigend numbers */
  major_number = MAJOR(dev);
  printk("major_number:%d\n", major_number);

  /* initialize cdev and function table */
  cdev_init(&my_char_dev, &my_file_ops);
  my_char_dev.owner = THIS_MODULE;

  /* register the driver */
  cdev_err = cdev_add(&my_char_dev, dev, NUMBER_MINOR_NUMBER);
  if (cdev_err != 0) {
    printk(KERN_ERR "failed to cdev_add()\n");
    unregister_chrdev_region(dev, NUMBER_MINOR_NUMBER);
    return -1;
  }

  /* register a class */
  my_char_dev_class = class_create(THIS_MODULE, DEVICE_NAME);
  if (IS_ERR(my_char_dev_class)) {
    printk(KERN_ERR "class_create()\n");
    cdev_del(&my_char_dev);
    unregister_chrdev_region(dev, NUMBER_MINOR_NUMBER);
    return -1;
  }

  /* create "/sys/class/my_device/my_device" */
  device_create(my_char_dev_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);

  printk(KERN_ALERT "sample_02 driver loaded\n");
  return 0;
}

static void my_module_exit(void)
{
  dev_t dev = MKDEV(major_number, MINOR_NUMBER_START);

  /* remove "/sys/class/my_device/my_device_*" */
  device_destroy(my_char_dev_class, MKDEV(major_number, 0));

  /* remove class */
  class_destroy(my_char_dev_class);

  /* remove driver */
  cdev_del(&my_char_dev);

  /* release the major number */
  unregister_chrdev_region(dev, NUMBER_MINOR_NUMBER);

  printk(KERN_ALERT "sample_02 driver unloaded\n");
}

static int my_open(struct inode* inode, struct file* filp)
{
  printk(KERN_ALERT "sample_02 driver opend\n");
  return 0;
}

int my_close(struct inode *inode, struct file *filp)
{
  printk(KERN_ALERT "sample_02 driver closed\n");
  return 0;
}

static long my_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
{
  printk(KERN_ALERT "sample_02 driver ioctl\n");
  return 0L;
}

static ssize_t my_write(struct file* file, const char __user* buff, size_t count, loff_t *pos)
{
  printk(KERN_ALERT "sample_02 driver write\n");
  return count;
}

static ssize_t my_read(struct file* file, char __user* buff, size_t count, loff_t *pos)
{
  printk(KERN_ALERT "sample_02 driver read\n");
  return count;
}

module_init(my_module_init);
module_exit(my_module_exit);
