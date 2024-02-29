#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/time.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/miscdevice.h>
#include <linux/pwm.h>
#include <linux/kernel.h>

static int pwm_user_probe(struct platform_device *pdev);
static int pwm_user_remove(struct platform_device *pdev);

static ssize_t pwm_user_write(struct file *file, const char __user *buf, size_t len, loff_t *pos);
static ssize_t pwm_user_read(struct file *file, char __user *buf, size_t len, loff_t *pos);
static int pwm_user_open(struct inode *inode, struct file *file);
static int pwm_user_close(struct inode *inodep, struct file *filp);

/* Matching table */
static const struct of_device_id pwm_user_BBB_of_match[] = {
	{ .compatible = "led-pwm-demo"},
    {}
};

static const struct file_operations pwm_user_fops = 
{
    .owner			= THIS_MODULE,
    .write			= pwm_user_write,
	.read			= pwm_user_read,
    .open			= pwm_user_open,
    .release		= pwm_user_close
};

struct miscdevice pwm_user_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "pwm_user_dev",
    .fops = &pwm_user_fops,
};

struct pwm_device *pwm;

static ssize_t pwm_user_write(struct file *file, const char __user *buf, size_t len, loff_t *pos)
{
    char * dynamic_ptr = NULL;
    int int_value = 0;
    int ret = -1;

    pr_info("%d %s\n", __LINE__, __func__);

    dynamic_ptr = (char *) kzalloc(len, GFP_KERNEL);
    copy_from_user(dynamic_ptr, buf, len);

    /* Convert ASCII to integer number */
    ret = kstrtol(dynamic_ptr, 10, (long *)&int_value);
    if(ret < 0)
    {
        pr_info("Convert string failed\n");
        return -1;
    }

    /* Configure PWM period */
    ret = pwm_config(pwm, int_value / 4, int_value);
    if(ret < 0)
    {
        pr_info("pwm_config failed\n");
        return -1;
    }

    return 1;
}

static ssize_t pwm_user_read(struct file *file, char __user *buf, size_t len, loff_t *pos)
{
    pr_info("%d %s\n", __LINE__, __func__);

    return 1;
}

static int pwm_user_open(struct inode *inode, struct file *file)
{
    pr_info("%d %s\n", __LINE__, __func__);

    return 0;
}

static int pwm_user_close(struct inode *inodep, struct file *filp)
{
    pr_info("%d %s\n", __LINE__, __func__);

    return 0;
}


static struct platform_driver pwm_user_driver = 
{
	.probe		= pwm_user_probe,
    .remove     = pwm_user_remove,
	.driver		= {
		.name	= "user_pwm",
		.of_match_table = pwm_user_BBB_of_match,
	},
};

static int pwm_user_probe(struct platform_device *pdev)
{
    int ret = -1;

    pwm = pwm_get(&pdev->dev, "led-pwm");
    if (IS_ERR(pwm))
    {
        pr_info("pwm failed\n");
        return -1;
    }

    pr_info("Period: %d\n", pwm->args.period);

    /* Create misc module */
    ret = misc_register(&pwm_user_device);
    if (ret) {
        pr_err("can't misc_register\n");
        return -1;
    }

    ret = pwm_config(pwm, pwm->args.period / 2, pwm->args.period);
    if(ret < 0)
    {
        pr_info("pwm_config failed\n");
        return -1;
    }

    ret = pwm_enable(pwm);
    if(ret < 0)
    {
        pr_info("pwm_enable failed\n");
        return -1;
    }
    
    return 0;
}

static int pwm_user_remove(struct platform_device *pdev)
{
    int ret = -1;

    pr_info("remove pwm module\n");

    /* disable pwm */
    pwm_disable(pwm);
    pwm_put(pwm);

    /* deregister pwm device */
    misc_deregister(&pwm_user_device);

    return 0;
}


module_platform_driver(pwm_user_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Pwm Led kernel module");







