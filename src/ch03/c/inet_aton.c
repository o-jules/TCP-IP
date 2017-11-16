#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
  char *addr1 = "1.2.3.4";
  char *addr2 = "1.2.3.256";
  struct sockaddr_in addr_inet;

  if (!inet_aton(addr1, &addr_inet.sin_addr)) {
    error_handling("Conversion error");
  } else {
    printf("Network ordered integer address: %#x. \n", addr_inet.sin_addr.s_addr);
  }

  if (!inet_aton(addr2, &addr_inet.sin_addr)) {
    error_handling("Conversion error");
  } else {
    printf("Network ordered integer address: %#x. \n", addr_inet.sin_addr.s_addr);
  }

  return 0;
}

void error_handling(char *message) {
  printf("Error: %s.\n", message);
  exit(0);
}