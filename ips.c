#include <arpa/inet.h>
#include <endian.h>
#include <math.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>

/*
  given an ip address and network mask
  get:
  - netmask
  - netmask length
  - host mask
  - host mask length
  - network address
  - first usable host address
  - last usable host address
  - network broadcast address
  - total host addresses
  - usable host addresses
 */

int
main(int argc, char** argv)
{
  unsigned int a, netmask, netmasklen = 0, networkaddr, hostmask, hostmasklen,
                           firstusable, lastusable, broadcast, totalhosts,
                           totalusable;
  a = inet_network(argv[1]);
  netmask = inet_network(argv[2]);

  netmasklen = 32 - (ffs(netmask) - 1);

  hostmask = ~netmask; // eg ~255.255.255.0
  hostmasklen = 32 - netmasklen;

  networkaddr = a & netmask;          // netmask & ip addr
  broadcast = networkaddr | hostmask; // eg 192.168.1.0 | 0.0.0.255

  firstusable = networkaddr + 1;
  lastusable = broadcast - 1;

  double pow(double, double);
  totalhosts = pow(2, hostmasklen);
  totalusable = totalhosts - 2;

  /* -netmask - netmask length - host mask - host mask length - network address
   -

   first usable host address - last usable host address -
    network broadcast address - total host addresses -
    usable host addresses
  */

#define iptoa(ip) (inet_ntoa((struct in_addr){ htobe32((ip)) }))

  printf(" host address: %s\n netmask: %s\n netmask length: %d\n host mask: "
         "%s\n hostmask len: %d\n",
         argv[1],
         argv[2],
         netmasklen,
         iptoa(hostmask),
         hostmasklen);
  printf(" network address: %s\n", iptoa(networkaddr));
  printf(" first usable host: %s\n", iptoa(firstusable));
  printf(" last usable host: %s\n", iptoa(lastusable));
  printf(" total hosts: %d\n", totalhosts);
  printf(" total usable hosts: %d\n", totalusable);
}
