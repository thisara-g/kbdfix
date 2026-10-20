#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>
#include <linux/input.h>

#define MAX_BAD 16

static int bad[MAX_BAD];
static int nbad;
module_param_array(bad, int, &nbad, 0444);
MODULE_PARM_DESC(bad, "Comma-separated keycodes to block, e.g. bad=30,45");

static int kbdfix_connect(struct input_handler *handler, struct input_dev *dev,
			  const struct input_device_id *id)
{
	pr_info("offered: %s\n", dev->name);
	return -ENODEV;
}

static void kbdfix_disconnect(struct input_handle *handle)
{
}

static const struct input_device_id kbdfix_ids[] = {
	{
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},
	{ },	/* terminator */
};

static struct input_handler kbdfix_handler = {
	.name		= "kbdfix",
	.id_table	= kbdfix_ids,
	.connect	= kbdfix_connect,
	.disconnect	= kbdfix_disconnect,
};

static int __init kbdfix_init(void)
{
	int i;

	if (nbad == 0)
		pr_info("no keys to block\n");
	else
		pr_info("blocking %d key(s)\n", nbad);

	for (i = 0; i < nbad; i++)
		pr_info("key %d\n", bad[i]);

	return input_register_handler(&kbdfix_handler);
}

static void __exit kbdfix_exit(void)
{
	input_unregister_handler(&kbdfix_handler);
	pr_info("unloaded\n");
}

module_init(kbdfix_init);
module_exit(kbdfix_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thisara Gunawardana");
MODULE_DESCRIPTION("Block broken keys on a laptop keyboard");