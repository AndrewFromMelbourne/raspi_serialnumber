# Raspberry Pi Serial Number
This repository contains example C code to retrieve the Raspberry Pi Serial Number

# serialnumber_cpuinfo.c

Read the serial number from /proc/cpuinfo

# serialnumber_sysfs.c

Read the serial number from /sys/firmware/devicetree/base/serial-number

# serialnumber_mailbox.c

Get the serial number using the Raspberry Pi Mailbox interface

# serialnumber_vcgencmd_using_bcm_host.c

Get the serial number using vcgencmd using libbcm_host

# serialnumber_vcgencmd_via_ioctl.c

Get the serial number using vcgencmd using ioctl

# build

	cd raspi_serialnumber
	mkdir build
	cd build
	cmake ..
	make

