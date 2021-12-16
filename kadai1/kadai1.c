#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>

MODULE_AUTHOR("Ryuichi Ueda & Kentarou Kawauchi");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static int gpio[8] = {1,2,3,4,5,6,7,8};
static int n;
static int i;

static ssize_t led_write(struct file* filp,const char* buf, size_t count, loff_t* pos)
{
	char c;
	if(copy_from_user(&c, buf, sizeof(char)))
		return -EFAULT;
	//n = c - '0';
	printk(KERN_INFO"receive %d\n", n);
	if(c=='0'){
	for( i = 1; i < 9 ; i++){
		gpio_base[10] = 1 << i;
		}
	}else if(c == '1'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
		gpio_base[7] = 1 << 1;
	}else if(c=='2'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
            	gpio_base[7] = 1 << 2;
        }else if(c=='3'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
                gpio_base[7] = 1 << 3;
        }else if(c=='4'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
                gpio_base[7] = 1 << 4;
        }else if(c=='5'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
                gpio_base[7] = 1 << 5;
        }else if(c=='6'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
                gpio_base[7] = 1 << 6;
        }else if(c=='7'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
                gpio_base[7] = 1 << 7;
        }else if(c=='8'){
		for( i = 1; i < 9 ; i++){
                gpio_base[10] = 1 << i;
                }
                gpio_base[7] = 1 << 8;
        }
	n = c - '0';

	return 1;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write=led_write

};
static int __init init_mod(void)
{
	int retval;
	retval = alloc_chrdev_region(&dev, 0, 1, "kadai1");
	if(retval<0){
		printk(KERN_ERR "alloc_chrdev_region failed. \n");
		return retval;
	}
	printk(KERN_INFO"%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval<0){
		printk(KERN_ERR" cdev_add failed. major:%d, major:%d", MAJOR(dev),MINOR(dev));
		return retval;

	}
	
	cls = class_create(THIS_MODULE, "kadai1");
	if(IS_ERR(cls)){
                printk(KERN_ERR "class_createfailed. ");
                return PTR_ERR(cls);
	}
	
	device_create(cls, NULL, dev, NULL, "kadai1%d", MINOR(dev));
	
	gpio_base = ioremap(0xfe200000, 0xA0);
	for(i = 1; i < 9; i++){
		const u32 led = i;
		const u32 index = led/10;
		const u32 shift = (led%10)*3;
		const u32 mask = ~(0x7 <<shift);
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
	}
	return 0;
}
static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO"%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);

