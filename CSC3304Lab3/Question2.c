#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char** argv) {
  printf("argc: %d\n", argc);

  printf("arguments:\n");
  for(int i = 0; i < argc; i++) {
    printf("%d: %s", i, argv[i]);
  }
  printf("\n");

  if(argc != 3) {
    printf("[*]USAGE: %s <ipaddr> <port> \n", argv[0]);
    return -1;
  }

  char* ip = argv[1];
  int port = atoi(argv[2]);

  printf("Listening on %s:%d\n", ip, port);

  int sock, addrlen, opt;
  struct sockaddr_in server;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  
  if(inet_pton(AF_INET, ip, &server.sin_addr) <= 0) {
    printf("[!]Connection to server failed\n");
    return -1;
  }

  if(connect(sock, (struct sockaddr*)&server, sizeof(server))) {
    printf("[!]Connection to server failed\n");
    return -1;
  }

  int readCount;
  
  do {
    char buf[32];
    readCount = recv(sock, buf, 32, 0);
    buf[readCount] = '\0';
    printf("%s", buf);
  } while(readCount == 32);

  close(sock);

  return 0;
}
