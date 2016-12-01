#/bin/sh

cp hcsr04-00A0.dtbo /lib/firmware
echo hcsr04 > /sys/devices/platform/bone_capemgr/slots
cat /sys/devices/platform/bone_capemgr/slots