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


void tcpconnect(struct sockaddr_in from, char *ipstr)
{
 struct sockaddr_in server;
 int sock;
 char buf[32];
 int n;

 /* ソケットの作成 */
 sock = socket(AF_INET, SOCK_STREAM, 0);

 /* 接続先指定用構造体の準備 */
 server.sin_family = AF_INET;
 server.sin_port = htons(from.sin_port);

 /* 127.0.0.1はlocalhost */
 inet_pton(AF_INET, ipstr, &server.sin_addr.s_addr);

 printf("willconnect\n");
 printf("recv data from : %d\n",  ntohs(from.sin_port));
 /* サーバに接続 */
 // int ret =connect(sock, (struct sockaddr *)&server, sizeof(server));
 //
 from.sin_port = htons(12345);
 int ret = connect(sock, (struct sockaddr *)&from, sizeof(from));
 printf("ret:%d\n",ret);

 /* サーバからデータを受信 */
 memset(buf, 0, sizeof(buf));
 printf("read\n");
 n = read(sock, buf, sizeof(buf));

 printf("%d, %s\n", n, buf);

 /* socketの終了 */
 close(sock);

 return 0;
}

int
main()
{
 int sock,sock2;
 struct sockaddr_in this;
 struct sockaddr_in from;
 struct sockaddr_in to;
 int sockaddr_in_size = sizeof(struct sockaddr_in);
 int size;

 char buf[2048];
 char str[16];

 sock = socket(AF_INET, SOCK_DGRAM, 0);
 this.sin_family = AF_INET;
 this.sin_port = htons(12345);
 this.sin_addr.s_addr = INADDR_ANY;

 sock2 = socket(AF_INET, SOCK_DGRAM, 0);
 to.sin_family = AF_INET;
 to.sin_port = htons(12345);
 to.sin_addr.s_addr = inet_addr("49.212.136.43");

 bind(sock, (struct sockaddr *)&this, sizeof(this));

 while(1){
  memset(buf, 0, sizeof(buf));
  printf("waiting for recv..\n");

  /* recv */
  size = recvfrom(sock, buf, 2048-1, 0, 
                    (struct sockaddr *)&from, &sockaddr_in_size);
  buf[2048-1] = 0;

  inet_ntop(AF_INET, &from.sin_addr, str, sizeof(str));
  printf("%s\n",buf);
  printf("recv data from : %s:%d\n", str, ntohs(from.sin_port));

//  tcpconnect(from,str);

  /* to*/
  memcpy(buf , &from, sizeof(struct sockaddr_in));
  sendto(sock2, buf, sizeof(struct sockaddr_in), 0, (struct sockaddr *)&to, sockaddr_in_size);
  printf("%s\n",buf);
  inet_ntop(AF_INET, &to.sin_addr, str, sizeof(str));
  printf("relay data to :%s:%d\n", str, ntohs(to.sin_port));
 }
 close(sock);

 return 0;
}
