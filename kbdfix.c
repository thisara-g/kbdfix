#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>

static int __init kbdfix_init(void)
{
	pr_info("loaded\n");
	return 0;
}

static void __exit kbdfix_exit(void)
{
	pr_info("unloaded\n");
}

module_init(kbdfix_init);
module_exit(kbdfix_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thisara Gunawardana");
MODULE_DESCRIPTION("Block broken keys on a laptop keyboard");