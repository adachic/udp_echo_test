#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void tcpconnect(struct sockaddr_in from, char *ipstr)
{
 struct sockaddr_in server;
 int sock;
 char buf[32];
 int n;

 /* �\�P�b�g�̍쐬 */
 sock = socket(AF_INET, SOCK_STREAM, 0);

 /* �ڑ���w��p�\���̂̏��� */
 server.sin_family = AF_INET;
 server.sin_port = htons(from.sin_port);

 /* 127.0.0.1��localhost */
 inet_pton(AF_INET, ipstr, &server.sin_addr.s_addr);

 fprintf(stderr, "willconnect\n");
 fprintf(stderr, "recv data from : %d\n",  ntohs(from.sin_port));
 /* �T�[�o�ɐڑ� */
 // int ret =connect(sock, (struct sockaddr *)&server, sizeof(server));
 //
 from.sin_port = htons(12345);
 int ret = connect(sock, (struct sockaddr *)&from, sizeof(from));
 fprintf(stderr, "ret:%d\n",ret);

 /* �T�[�o����f�[�^����M */
 memset(buf, 0, sizeof(buf));
 fprintf(stderr, "read\n");
 n = read(sock, buf, sizeof(buf));

 fprintf(stderr, "%d, %s\n", n, buf);

 /* socket�̏I�� */
 close(sock);

 return 0;
}

int
main()
{
 int sock, sock2;
 struct sockaddr_in addr;
 struct sockaddr_in from;
 struct sockaddr_in to;
 int sockaddr_in_size = sizeof(struct sockaddr_in);
 int size;

 char buf[2048];
 char str[16];

 sock = socket(AF_INET, SOCK_DGRAM, 0);

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

bind(sock, (struct sockaddr *)&addr , sizeof(addr)); 
sock2 = socket(AF_INET, SOCK_DGRAM, 0);

 while(1){
  memset(buf, 0, sizeof(buf));
  fprintf(stderr, "waiting for recv..\n");

  size = recvfrom(sock, buf, 2048-1, 0, 
                    (struct sockaddr *)&from, &sockaddr_in_size);
  time_t now = time(NULL);
  struct tm *time = localtime(&now);
  fprintf(stderr, "%02d/%02d %02d:%02d:%02d\n", time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
  buf[2048-1] = 0;

  inet_ntop(AF_INET, &from.sin_addr, str, sizeof(str));
  fprintf(stderr, "%s\n",buf);
  fprintf(stderr, "recv data from : %s:%d\n", str, ntohs(from.sin_port));

  memcpy(&to, buf, sizeof(struct sockaddr_in));
  sprintf(buf, "%02d/%02d %02d:%02d:%02d", time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
  sendto(sock2, buf, size, 0, (struct sockaddr *)&to, sockaddr_in_size);
  fprintf(stderr, "%s\n",buf);
  inet_ntop(AF_INET, &to.sin_addr, str, sizeof(str));
  fprintf(stderr, "send data to :%s:%d\n", str, ntohs(to.sin_port));
 }
 close(sock);

 return 0;
}
