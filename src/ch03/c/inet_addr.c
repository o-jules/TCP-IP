#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
  char *addr1 = "1.2.3.4";
  char *addr2 = "1.2.3.256";
  unsigned long conv_addr;
  
  conv_addr = inet_addr(addr1);
  // 在小端系统上是： 0x040302010
  if (conv_addr == INADDR_NONE) {
    printf("Error occured!\n");
  } else {
    printf("Network ordered integer addr: %#lx \n", conv_addr);
  }

  conv_addr = inet_addr(addr2);
  if (conv_addr == INADDR_NONE) {
    printf("Error occured!\n");
  } else {
    printf("Network ordered integer addr: %#lx \n", conv_addr);
  }

  return 0;
}