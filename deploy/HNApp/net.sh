#!/bin/sh

ifconfig eth0 192.168.0.107 netmask 255.255.255.0 up
ifconfig wlan0 192.168.0.107 netmask 255.255.255.0 up
route add default gw 192.168.0.1 netmask 0.0.0.0 dev eth0
route add default gw 192.168.0.1 netmask 0.0.0.0 dev wlan0
echo nameserver 192.168.0.1 > /etc/resolv.conf
wpa_supplicant -B -Dwext -iwlan0 -c/etc/wpa_supplicant.conf
