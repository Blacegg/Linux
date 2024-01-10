#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/atomic.h>

#define GPIOLED_CNT 1
#define GPIOLED_NAME "atomicled"

#define LEDON 1
#define LEDOFF 0

/* 设备结构体 */
struct gpioled_dev
{
	dev_t devid;
	struct cdev cdev;
	struct class *class;
	struct device *device;
	struct device_node *nd;
	int led_gpio;
	int major;
	int minor;
	atomic_t lock;
};

struct gpioled_dev gpioled;

static int gpioled_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &gpioled;

	if (!atomic_dec_and_test(&gpioled.lock))
	{
		atomic_inc_return(&gpioled.lock);
		return -EBUSY;
	}

	return 0;
}

static ssize_t gpioled_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{

	return 0;
}

static ssize_t gpioled_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
	int retvalue;
	unsigned char databuf[1];
	unsigned char ledstatus;
	struct gpioled_dev *dev = filp->private_data;

	retvalue = copy_from_user(databuf, buf, cnt);
	if (retvalue < 0)
	{
		printk("kernel write failed!\r\n");
		return -EFAULT;
	}

	ledstatus = databuf[0];
	if (ledstatus == LEDON)
	{
		gpio_set_value(dev->led_gpio, 0);
	}
	else if (ledstatus == LEDOFF)
	{
		gpio_set_value(dev->led_gpio, 1);
	}

	return 0;
}

static int gpioled_release(struct inode *inode, struct file *filp)
{
	struct gpioled_dev *dev = filp->private_data;
	atomic_add(1, &dev->lock);
	return 0;
}

static struct file_operations gpioled_fops = {
	.owner = THIS_MODULE,
	.open = gpioled_open,
	.read = gpioled_read,
	.write = gpioled_write,
	.release = gpioled_release,
};

/* 驱动入口 */
static int __init gpioled_init(void)
{
	int ret = 0;

	atomic_set(&gpioled.lock, 1);

	/* 创建设备 */
	/* 1、申请设备号 */
	if (gpioled.major)
	{
		gpioled.devid = MKDEV(gpioled.major, 0);
		ret = register_chrdev_region(gpioled.devid, GPIOLED_CNT, GPIOLED_NAME);
	}
	else
	{
		ret = alloc_chrdev_region(&gpioled.devid, 0, GPIOLED_CNT, GPIOLED_NAME);
		gpioled.major = MAJOR(gpioled.devid);
		gpioled.minor = MINOR(gpioled.devid);
	}

	if (ret < 0)
	{
		printk("failed to request device id\r\n");
		goto failed_devid;
	}
	else
	{
		printk("devid major = %d , minor = %d\r\n", gpioled.major, gpioled.minor);
	}

	/* 2、初始化cdev */
	gpioled.cdev.owner = THIS_MODULE;
	cdev_init(&gpioled.cdev, &gpioled_fops);

	/* 3、添加cdev */
	ret = cdev_add(&gpioled.cdev, gpioled.devid, GPIOLED_CNT);
	if (ret < 0)
	{
		printk("failed to add cdev\r\n");
		goto failed_addcdev;
	}

	/* 4、创建类 */
	gpioled.class = class_create(THIS_MODULE, GPIOLED_NAME);
	if (IS_ERR(gpioled.class))
	{
		ret = PTR_ERR(gpioled.class);
		printk("failed to create class\r\n");
		goto failed_class;
	}

	/* 5、创建设备 */
	gpioled.device = device_create(gpioled.class, NULL, gpioled.devid, NULL, GPIOLED_NAME);
	if (IS_ERR(gpioled.device))
	{
		ret = PTR_ERR(gpioled.device);
		printk("failed to create device\r\n");
		goto failed_device;
	}

	/* 设置LED所使用的GPIO */
	/* 1、获取设备节点 */
	gpioled.nd = of_find_node_by_path("/gpioled");
	if (gpioled.nd == NULL)
	{
		printk("gpioled node can not found!\r\n");
		ret = -EINVAL;
		goto failed_nd;
	}

	/* 2、获取节点GPIO属性，得到LED所使用的GPIO编号 */
	gpioled.led_gpio = of_get_named_gpio(gpioled.nd, "led-gpio", 0);
	if (gpioled.led_gpio < 0)
	{
		printk("can not get led-gpio!\r\n");
		ret = -EINVAL;
		goto failed_gpio;
	}
	printk("led-gpio num = %d\r\n", gpioled.led_gpio);

	/* 3、设置GPIO1_03为输出模式，并且输出高电平，默认关闭LED灯 */
	ret = gpio_direction_output(gpioled.led_gpio, 1);
	if (ret < 0)
	{
		printk("failed to init gpio!\r\n");
		goto failed_gpio;
	}

	/* 打开LED */
	gpio_set_value(gpioled.led_gpio, 0);

	return 0;

failed_gpio:
failed_nd:
	device_destroy(gpioled.class, gpioled.devid);
failed_device:
	class_destroy(gpioled.class);
failed_class:
	cdev_del(&gpioled.cdev);
failed_addcdev:
	unregister_chrdev_region(gpioled.devid, GPIOLED_CNT);
failed_devid:
	return ret;
}

/* 驱动出口 */
static void __exit gpioled_exit(void)
{
	/* 关闭LED */
	gpio_set_value(gpioled.led_gpio, 1);

	device_destroy(gpioled.class, gpioled.devid);
	class_destroy(gpioled.class);
	cdev_del(&gpioled.cdev);
	unregister_chrdev_region(gpioled.devid, GPIOLED_CNT);
}

/* 驱动的加载与卸载 */
module_init(gpioled_init);
module_exit(gpioled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("blacegg");