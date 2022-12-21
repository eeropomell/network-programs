#include "cksum.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>

/*
  Traceroute

  Send icmp echo requests to destination but until an echo reply is received
  Start with ttl 1 and keep incrementing it
  Routers will generate a icmp time exceeded error but the destination will do a
  echo reply

 */

int
main(int argc, char** argv)
{
  int n, s, ttl, ttlmax = 30;
  struct icmphdr icmp;
  struct sockaddr_in sin;
  struct ip ip;
  memset(&sin, 0, sizeof sin);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(33434);
  inet_aton(argv[1], &sin.sin_addr);

  if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    return -1;

  printf("traceroute to %s, %d hops max\n", inet_ntoa(sin.sin_addr), ttlmax);

  ttl = n = 0;
  while (ttl++ < ttlmax) {
    if (setsockopt(s, IPPROTO_IP, IP_TTL, &ttl, sizeof ttl) < 0)
      return -1;

    icmp.type = ICMP_ECHO;
    icmp.code = 0;
    icmp.checksum = 0;
    icmp.un.echo.id = 0;
    icmp.un.echo.sequence = 0;
    icmp.checksum = in_cksum((u_short*)&icmp, sizeof icmp, 0);

    if (sendto(s, &icmp, sizeof icmp, 0, (struct sockaddr*)&sin, sizeof sin) <
        0)
      return -1;

    recv(s, &ip, sizeof ip + sizeof icmp, 0);
    icmp = *(struct icmphdr*)(&ip + 1);

    printf(" %d  %s\n", n++, inet_ntoa(ip.ip_src));
    if (icmp.type == 0) {
      break;
    }
  }
}
