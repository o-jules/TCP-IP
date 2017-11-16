#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
  struct sockaddr_in addr1, addr2;
  char *str_ptr;
  char str_arr[20];

  addr1.sin_addr.s_addr = htonl(0x01020304);
  addr2.sin_addr.s_addr = htonl(0x01010101);

  str_ptr = inet_ntoa(addr1.sin_addr);
 
  strcpy(str_arr, str_ptr);
  printf("Dotted-Decimal notation 1: %s \n", str_ptr);

  inet_ntoa(addr2.sin_addr); // str_ptr will be rewritten.
  printf("Dotted-Decimal notation 2: %s \n", str_ptr);
  printf("Dotted-Decimal notation 3: %s \n", str_arr);
  
  return 0;
}
