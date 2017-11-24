/**
 * run test, for example:
 * 
 * ```bash
 * ./server.out 5143
 * ```
 * the number of port should not be too small.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define CODE_FAILURE -1
#define CODE_SUCCESS 0

void error_handling(char *message);

int main(int argc, char *argv[]) {
  int serv_sock, clnt_sock;

  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_sz;
  int str_len;

  char message[BUF_SIZE];

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == CODE_FAILURE) {
    error_handling("socket() error");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  int bind_status = bind(
    serv_sock,
    (struct sockaddr *) &serv_addr,
    sizeof(serv_addr)
  );
  if (bind_status == CODE_FAILURE) {
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == CODE_FAILURE) {
    error_handling("listen() error");
  }

  clnt_addr_sz = sizeof(clnt_addr);
  // infinite loop of server
  for (int i = 0; i < 5; i++) {
    clnt_sock = accept(
      serv_sock,
      (struct sockaddr *) &clnt_addr,
      &clnt_addr_sz
    );

    if (clnt_sock == CODE_FAILURE) {
      error_handling("accept() error");
    } else {
      printf("Connect client %d.\n", i);
    }
    while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
      write(clnt_sock, message, str_len);
    }

    close(clnt_sock); 
  }

  // close(clnt_sock);
  close(serv_sock);

  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
