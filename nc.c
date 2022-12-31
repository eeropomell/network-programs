#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

/*
  netcat

  so far it just either listens or sends data
*/

int
main(int argc, char** argv)
{
  struct sockaddr_in sin;
  char recvb[200];
  int s;

  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&sin, 0, sizeof sin);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(4000);
  inet_aton("192.168.1.2", &sin.sin_addr);

  if (argv[1]) {
    sendto(s, "lol", 3, 0, (struct sockaddr*)&sin, sizeof sin);
  } else {
    bind(s, (struct sockaddr*)&sin, sizeof sin);
    recv(s, recvb, 3, 0);
    printf("Received: %s", recvb);
  }
}
