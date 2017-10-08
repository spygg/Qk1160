#!/bin/sh

#修改密码
passwd root<<EOF
4006186188
4006186188
EOF

#关闭SSH

#关闭HOTPLUG


#校准屏幕
/usr/bin/ts_calibrate

#发布版本的程序-完整包
/usr/bin/tar xzvf /mnt/usb_sda1/deploy.tar.gz -C /

#重启
reboot

