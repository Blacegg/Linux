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

#define BEEP_CNT 1
#define BEEP_NAME "beep"

#define BEEP_ON 1
#define BEEP_OFF 0

struct beep_dev
{
	dev_t devid;
	struct cdev cdev;
	struct class *class;
	struct device *device;
	int major;
	int minor;
	struct device_node *np;
	int beep_gpio;
};

struct beep_dev beep;

static int beep_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &beep;
	return 0;
}

static ssize_t beep_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
	int ret;
	unsigned char databuf[1];
	unsigned char beepstatue;
	struct beep_dev *bp = filp->private_data;

	ret = copy_from_user(databuf, buf, cnt);
	if (ret < 0)
	{
		printk("kernel writer failed!\r\n");
		return -EFAULT;
	}

	beepstatue = databuf[0];

	if (beepstatue == BEEP_ON)
	{
		gpio_set_value(bp->beep_gpio, 0);
	}
	else
	{
		gpio_set_value(bp->beep_gpio, 1);
	}
	return 0;
}

static ssize_t beep_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
	return 0;
}

static int beep_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static struct file_operations beep_fops = {
	.owner = THIS_MODULE,
	.open = beep_open,
	.write = beep_write,
	.read = beep_read,
	.release = beep_release,
};

static int __init beep_init(void)
{
	int ret = 0;
	/* 创建设备 */
	/* 1、申请设备号 */
	if (beep.major)
	{
		beep.devid = MKDEV(beep.major, 0);
		ret = register_chrdev_region(beep.devid, BEEP_CNT, BEEP_NAME);
	}
	else
	{
		ret = alloc_chrdev_region(&beep.devid, 0, BEEP_CNT, BEEP_NAME);
		beep.major = MAJOR(beep.devid);
		beep.minor = MINOR(beep.minor);
	}
	if (ret < 0)
	{
		printk("failed to request deviceid!\r\n");
		goto fail_devid;
	}
	else
	{
		printk("dev major = %d, minor = %d\r\n", beep.major, beep.minor);
	}

	/* 2、初始化cdev */
	beep.cdev.owner = THIS_MODULE;
	cdev_init(&beep.cdev, &beep_fops);

	/* 3、添加cdev */
	ret = cdev_add(&beep.cdev, beep.devid, BEEP_CNT);
	if (ret < 0)
	{
		printk("failed to add cdev!\r\n");
		goto fail_cdev;
	}

	/* 4、创建类 */
	beep.class = class_create(THIS_MODULE, BEEP_NAME);
	if (IS_ERR(beep.class))
	{
		ret = PTR_ERR(beep.class);
		goto fail_class;
	}

	/* 5、创建设备 */
	beep.device = device_create(beep.class, NULL, beep.devid, NULL, BEEP_NAME);
	if (IS_ERR(beep.device))
	{
		ret = PTR_ERR(beep.device);
		goto fail_device;
	}

	/* 蜂鸣器初始化 */
	/* 1、读取设备节点 */
	beep.np = of_find_node_by_path("/beep");
	if (beep.np == NULL)
	{
		printk("failed to read node!\r\n");
		goto fail_node;
	}

	/* 2、获取GPIO属性 */
	beep.beep_gpio = of_get_named_gpio(beep.np, "beep-gpio", 0);
	if (beep.beep_gpio < 0)
	{
		printk("can not get gpio!\r\n");
		return -EINVAL;
	}

	/* 3、设置gpio方向 */
	ret = gpio_direction_output(beep.beep_gpio, 1);
	if (ret < 0)
	{
		printk("can not set gpio!\r\n");
	}

	return 0;
fail_node:
	device_destroy(beep.class, beep.devid);
fail_device:
	class_destroy(beep.class);
fail_class:
	cdev_del(&beep.cdev);
fail_cdev:
	unregister_chrdev_region(beep.devid, BEEP_CNT);
fail_devid:
	return ret;
}

static void __exit beep_exit(void)
{
	gpio_set_value(beep.beep_gpio, 1);
	device_destroy(beep.class, beep.devid);
	class_destroy(beep.class);
	cdev_del(&beep.cdev);
	unregister_chrdev_region(beep.devid, BEEP_CNT);
}

/* 驱动加载与卸载 */
module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("blacegg");