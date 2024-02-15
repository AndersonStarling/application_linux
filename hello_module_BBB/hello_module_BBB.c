#include <linux/module.h>
#include <linux/init.h>

/* Module Init */
static int __init hello_module_init(void)
{
    pr_info("Hello Module BBB init\n");

    return 0;
}

/* Module Exit */
static void __exit hello_module_exit(void)
{
    pr_info("Hello Module BBB exit\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tai nguyen - tai.nguyen24816@gmail.com");
MODULE_DESCRIPTION("Hello Kenel Module");