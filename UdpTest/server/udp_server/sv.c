#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int
main()
{
 int sock;
 struct sockaddr_in addr;
 struct sockaddr_in from;
 int sockaddr_in_size = sizeof(struct sockaddr_in);
 int size;

 char buf[2048];
 char str[16];

 sock = socket(AF_INET, SOCK_DGRAM, 0);

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

 bind(sock, (struct sockaddr *)&addr, sizeof(addr));

 printf("waiting for recv..\n");
 while(1){
  memset(buf, 0, sizeof(buf));

  /*受信*/
  size = recvfrom(sock, buf, 2048-1, 0, 
                    (struct sockaddr *)&from, &sockaddr_in_size);
  buf[2048-1] = 0;

  inet_ntop(AF_INET, &from.sin_addr, str, sizeof(str));
  printf("%s\n",buf);
  printf("recv data from : %s:%d\n", str, ntohs(from.sin_port));

  /*返信*/
  strcpy(buf , "echo");
  sendto(sock, buf, size, 0, (struct sockaddr *)&from, sockaddr_in_size);
  printf("%s\n",buf);
  printf("send data to :%s:%d\n", str, ntohs(from.sin_port));
 }
 close(sock);

 return 0;
}
