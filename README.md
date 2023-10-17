# usb-device-driver
Repository helps to understand usb device driver concepts and how to write simple usb device driver
This is open source driver code, can be used to your project or modify as your usage without any restrictions

Incase of any  error related to
**1. "License Module can not be loaded" to load custom module****
      disable secure boot 
              or
      # echo 1 > /proc/sys/kernel/sysrq
      # echo x > /proc/sysrq-trigger
