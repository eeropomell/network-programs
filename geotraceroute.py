import requests
import sys
import socket
from icmplib import traceroute

## geotraceroute.py
## print location info for each ip address in traceroute
## info may not be 100% accurate


## $ geotraceroute.py google.com
## ip=69.69.69.69 country=Finland city=Helsinki
## ip=213.192.186.82 country=Finland city=Helsinki
## ip=213.192.186.81 country=Finland city=Helsinki rDNS=ae3.bbr1.hel2.fi.ip4.elisa.net
## ip=213.192.184.177 country=Finland city=Helsinki
## ip=142.250.168.220 country=United States city=Mountain View
## ip=142.250.36.209 country=United States city=Mountain View
## ip=142.250.36.210 country=United States city=Mountain View
## ip=64.233.174.67 country=United States city=Mountain View
## ip=108.170.238.38 country=United States city=Mountain View
## ip=142.251.245.207 country=United States city=Mountain View
## ip=72.14.239.244 country=United States city=Mountain View
## ip=108.170.252.65 country=United States city=Mountain View
## ip=142.250.225.77 country=United States city=Mountain View
## ip=142.250.185.206 country=Germany city=Frankfurt am Main rDNS=fra16s52-in-f14.1e100.net



trace = traceroute(sys.argv[1])

for host in trace:
    res = requests.get("http://ip-api.com/json/" + host._address).json()
    if "fail" not in res["status"]:
        print("ip={0} country={1} city={2} ".format(host._address, res["country"], res["city"]), end='')
        r = socket.getnameinfo((host._address, 0), 0)
        if r[0] not in host._address:
            print("rDNS={0}".format(r[0]), end='') # reverse DNS might show info about location
        print()

















