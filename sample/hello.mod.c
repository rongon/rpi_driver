#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x8eb427c3, "module_layout" },
	{  0x414e5, "class_destroy" },
	{ 0xbe7c8d55, "device_destroy" },
	{ 0x1604dd93, "device_create" },
	{ 0xcd215df2, "cdev_del" },
	{ 0x2eeac73b, "__class_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe92ec844, "cdev_add" },
	{ 0x57ec239, "cdev_init" },
	{ 0x7c32d0f0, "printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xe97c4103, "ioremap" },
	{ 0xedc03953, "iounmap" },
	{ 0xbb72d4fe, "__put_user_1" },
	{ 0x28118cb6, "__get_user_1" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3A5078B2DEBF0BB56288D66");
