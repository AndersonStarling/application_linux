#include <linux/module.h>
#include <linux/init.h>
#include <linux/serdev.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static int serial_user_probe(struct serdev_device *pdev);
static void serial_user_remove(struct serdev_device *pdev);

static ssize_t serial_user_write(struct file *file, const char __user *buf, size_t len, loff_t *pos);
static ssize_t serial_user_read(struct file *file, char __user *buf, size_t len, loff_t *pos);
static int serial_user_open(struct inode *inode, struct file *file);
static int serial_user_close(struct inode *inodep, struct file *filp);

/* Matching table */
static const struct of_device_id serial_user_BBB_of_match[] = {
	{ .compatible = "serial-user-demo"},
    {}
};

static const struct file_operations serial_user_fops = 
{
    .owner			= THIS_MODULE,
    .write			= serial_user_write,
	.read			= serial_user_read,
    .open			= serial_user_open,
    .release		= serial_user_close
};

struct miscdevice serial_user_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "serial_user_dev",
    .fops = &serial_user_fops,
};

static ssize_t serial_user_write(struct file *file, const char __user *buf, size_t len, loff_t *pos)
{
    char * dynamic_ptr = NULL;
    int int_value = 0;
    int ret = -1;

    pr_info("%d %s\n", __LINE__, __func__);

    return 1;
}

static ssize_t serial_user_read(struct file *file, char __user *buf, size_t len, loff_t *pos)
{
    pr_info("%d %s\n", __LINE__, __func__);

    return 1;
}

static int serial_user_open(struct inode *inode, struct file *file)
{
    pr_info("%d %s\n", __LINE__, __func__);

    return 0;
}

static int serial_user_close(struct inode *inodep, struct file *filp)
{
    pr_info("%d %s\n", __LINE__, __func__);

    return 0;
}


static struct serdev_device_driver serial_user_driver = 
{
	.probe		= serial_user_probe,
    .remove     = serial_user_remove,
	.driver		= {
		.name	= "serial_user",
		.of_match_table = serial_user_BBB_of_match,
	},
};

static int serial_user_probe(struct serdev_device *pdev)
{
    int ret = -1;

    pr_info("probe is called\n");


    /* Create misc module */
    ret = misc_register(&serial_user_device);
    if (ret) {
        pr_err("can't misc_register\n");
        return -1;
    }

    return 0;
}

static void serial_user_remove(struct serdev_device  *pdev)
{
    int ret = -1;

    pr_info("remove serial module\n");

    /* deregister pwm device */
    misc_deregister(&serial_user_device);

    return 0;
}

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init serial_module_init(void) 
{
	pr_info("serial module - Loading the driver...\n");
	if(serdev_device_driver_register(&serial_user_driver)) {
		pr_info("serdev_echo - Error! Could not load driver\n");
		return -1;
	}
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit serial_module_exit(void) 
{
	pr_info("serial module - Unload driver");
	serdev_device_driver_unregister(&serial_user_driver);
}

module_init(serial_module_init);
module_exit(serial_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Serial Led kernel module");














