#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int
main()
{
  int s, r;
  struct sockaddr_in sin;
  memset(&sin, 0, sizeof sin);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(14000);
  inet_aton("192.168.1.1", &sin.sin_addr);

  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  r = sendto(s, "lol", 100, 0, (struct sockaddr*)&sin, sizeof sin);
}
