import requests
import sys
import socket
from icmplib import traceroute


a = traceroute(sys.argv[1])


for h in a:
    res = requests.get("http://ip-api.com/json/" + h._address).json()
    if "fail" not in res["status"]:
        print("ip={0} country={1} city={2} ".format(h._address, res["country"], res["city"]), end='')
        r = socket.getnameinfo((h._address, 0), 0)
        if r[0] not in h._address:
            print("rDNS={0}".format(r[0]), end='')
        print()

















