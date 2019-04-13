#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Kenji Seto");
MODULE_DESCRIPTION("Sample Driver #01");

static int my_module_init(void)
{
  printk(KERN_ALERT "sample_01 driver loaded\n");
  return 0;
}

static void my_module_exit(void)
{
  printk(KERN_ALERT "sample_01 driver unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
