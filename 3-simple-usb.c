/* Print Interface Desription parameters */
/* Before insert this module, request to remove mas storage driver with command like 
 * $sudo rmmod uas usb_storage; 
 * Only by removing usb_storage, probe function will be called */
//INFO: Before going to this device driver I would request to understand
//1-simple-usb.c and read README.md file for more understanding
#include<linux/init.h>
#include<linux/module.h>
#include<linux/usb.h>

MODULE_DESCRIPTION("Simple Driver read parameters of interface descriptor");
MODULE_AUTHOR("malatesh10@gmail.com");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");

static int skel_usb_probe(struct usb_interface *intf, const struct usb_device_id *id) {
	struct usb_device *dev	= interface_to_usbdev(intf);
	struct usb_host_interface *interface; //store device current or present using interface
	struct usb_endpoint_descriptor *endpoint;

	printk(KERN_INFO "---->skel_usb_probe function called\n");

	//interface structure holds the pointer to presently using interface
	//usb_interface is structure array, contains the N number of interfaces of device config descriptor
	interface = intf->cur_altsetting;

	//Print idVendor and idProduct	
	printk(KERN_ALERT "Current Interface:%d\n", interface->desc.bInterfaceNumber);
	printk(KERN_INFO "Current Alternate Setting:%d\n", interface->desc.bAlternateSetting);
	printk(KERN_NOTICE "Device contains Endpoints:%d no\n", interface->desc.bNumEndpoints);
	printk(KERN_DEBUG "Interface Class:%d\n", interface->desc.bInterfaceClass);
	printk(KERN_INFO "Interface Sub Class:0x%d\n", interface->desc.bInterfaceSubClass);
	printk(KERN_INFO "Interface Protocol: %u\n", interface->desc.bInterfaceProtocol);

	endpoint = &interface->endpoint[0].desc; //Access interface 0, endpoint no 0 descriptor
	printk(KERN_INFO "------------- endpoint descriptor-0 --------------" );
	printk(KERN_INFO "Desc Length: %d\n", endpoint -> bLength);
	printk(KERN_INFO "Address: %02X\n", endpoint -> bEndpointAddress);
	printk(KERN_INFO "MaxPacketSize: %d\n", endpoint -> wMaxPacketSize);
	printk(KERN_INFO "bDescriptorType:%d\n", endpoint -> bDescriptorType);
	printk(KERN_INFO "bInterval:0x%d\n", endpoint -> bInterval);
	printk(KERN_INFO "bInterval:%d\n", endpoint -> bmAttributes);

	endpoint = &interface->endpoint[1].desc; //Access interface 0, endpoint no 1 descriptor
	printk(KERN_INFO "------------- endpoint descriptor-1--------------" );
	printk(KERN_INFO "Desc Length: 0x%x\n", endpoint -> bLength);
	printk(KERN_INFO "Address: 0x%x\n", endpoint -> bEndpointAddress);
	printk(KERN_INFO "MaxPacketSize: %x\n", endpoint -> wMaxPacketSize);
	printk(KERN_INFO "bDescriptorType:0x%x\n", endpoint -> bDescriptorType);
	printk(KERN_INFO "bInterval:0x%x\n", endpoint -> bInterval);
	printk(KERN_INFO "bInterval:0x%x\n", endpoint -> bmAttributes);

	return 0;
}
static void skel_usb_disconnect(struct usb_interface *iface) {
	printk(KERN_INFO "----> skel_usb_disconnect function called\n");
}

//Get the vendor id and device id, by running the $dmesg command after connecting
//your pheripheral device(like pendrive or mouse or keyboard or webcam or etc)
static struct usb_device_id skel_id_table[] = {
	{USB_DEVICE(0x0781, 0x5581)}, //Pendrive
	//{USB_DEVICE(0x46d, 0x082c)}, //HD Webcam C615
	//{USB_DEVICE(0x413c, 0x301a)}, //Mouse
	//{USB_DEVICE(0x413c, 0x2113)}, //Keyboard
	//{USB_DEVICE(0x1ea7, 0x0064)},
	//{USB_DEVICE(0x03f0, 0x5a07)},
	{}
};
MODULE_DEVICE_TABLE(usb, skel_id_table);

static struct usb_driver skel_usb_driver = {
	.name = "test-mouse-driver",
	.probe = skel_usb_probe,
	.disconnect = skel_usb_disconnect,
	.id_table = skel_id_table,
};
static int __init skel_module_init(void) {
	int result;
	printk(KERN_INFO "---->test usb deriver init function called\n");
	result = usb_register(&skel_usb_driver);
	if( result) {
		printk(KERN_ERR "---->usb-test-2 driver registration failed with %d\n", result);
		return result;
	}

	return 0;
}
static void __exit skel_module_exit(void) {
	usb_deregister(&skel_usb_driver);
	printk(KERN_INFO "----> usb-test-2 driver exit function called success\n");
}
module_init(skel_module_init);
module_exit(skel_module_exit);
