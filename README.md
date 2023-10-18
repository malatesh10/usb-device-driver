# usb-device-driver
Repository helps to understand usb device driver concepts and how to write simple usb device driver
This is open source driver code, can be used to your project or modify as your usage without any restrictions

Info I: Incase of any  error like "License Module can not be loaded" while loading driver
      disable secure boot 
              or
      $echo 1 > /proc/sys/kernel/sysrq
      $echo x > /proc/sysrq-trigger
      
InfoII: Before insert this module, request to remove mas storage driver with command like
      $sudo rmmod uas usb_storage;
      Only by removing usb_storage, probe function will be called
