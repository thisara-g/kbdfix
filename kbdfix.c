#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>

#define MAX_BAD 16

static int bad[MAX_BAD];
static int nbad;
module_param_array(bad, int, &nbad, 0444);
MODULE_PARM_DESC(bad, "Comma-separated keycodes to block, e.g. bad=30,45");

static int __init kbdfix_init(void)
{
	int i;

	if (nbad == 0) {
		pr_info("no keys to block\n");
		return 0;
	}

	pr_info("blocking %d key(s)\n", nbad);
	for (i = 0; i < nbad; i++)
		pr_info("key %d\n", bad[i]);

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