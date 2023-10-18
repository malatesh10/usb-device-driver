/* A simple usb device driver to understand usb device driver structure 
 * Before insert this module, request to remove mas storage driver with command like
 * $sudo rmmod uas usb_storage;
 * Only by removing usb_storage, probe function will be called 
 * Incase of any doubt send out email to malatesh10@gmail.com
 * Incase you feel this device driver is useful please click on star in github and 
 * you can share comments in linkedin https://www.linkedin.com/in/malatesh-ankasapur-48a08837/
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/init.h>

MODULE_DESCRIPTION("Simple USB device driver"); 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("malatesh10@gmail.com");
MODULE_VERSION("0.1");

//Probe function will be called when the vid and pid match with attached device
static int skel_usb_probe(struct usb_interface *iface, const struct usb_device_id *id)  {
	printk(KERN_INFO "---> Driver probe function called\n");

	return 0;
}

static void skel_usb_disconnect(struct usb_interface *iface) {
	printk(KERN_INFO "----> Driver disconnect function called and USB device disconnected\n");
}

//Step IV: Add device vid and pid. To get vid and pid, connect usb pheriphercal device( Ex: printer or camera) to host machine
//run $sudo dmesg
static struct usb_device_id skel_id_table[] = {
	{USB_DEVICE(0x0781, 0x5581)}, //VID and PID of pendrive
	{}
};
MODULE_DEVICE_TABLE(usb, skel_id_table);

//Step V: Create driver supported functions and register with usb subsystem in init function 
//and unregister in exit function to unregister driver from usb subsystem
static struct usb_driver skel_usb_driver = {
	.name = "usb-test-1",
	.probe = skel_usb_probe,
	.disconnect = skel_usb_disconnect,
	.id_table = skel_id_table,
};

//Step I: Write init function. Init function will be called when the module get inserted to running kernel
static int __init skel_usb_init(void) {
	int result = 0;

	result = usb_register(&skel_usb_driver);
	if(result) {
		printk(KERN_ALERT "Driver registration with usb subsystem is failed with error: %d\n", result );
	}
	return result;
}
//Step II: Write exit function. Exit function will be called when the module get exit from running kernel
static void __exit skel_usb_exit(void) {
	usb_deregister(&skel_usb_driver);
	printk(KERN_INFO "Driver de registration success\n");
}
//Step III: Add init and exit function to kernel subsystem get identify 
module_init(skel_usb_init);
module_exit(skel_usb_exit);
