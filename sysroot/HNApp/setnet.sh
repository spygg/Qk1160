#!/bin/sh                                                                       
       
ifconfig eth0 0.0.0.0 up    
ifconfig eth0 192.168.0.104 netmask 255.255.255.0 up   
                                                                  
ip route | awk '{print $1}' | while read line; do ip route del $line; done                                                                                
route add default gw 192.168.0.1 netmask 0.0.0.0 dev eth0      

                
echo nameserver 192.168.0.1 > /etc/resolv.conf                                 
                                                                                
