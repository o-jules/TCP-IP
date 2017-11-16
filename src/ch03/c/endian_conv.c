#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
  unsigned short host_port = 0x1234;
  unsigned short net_port;
  unsigned long host_addr = 0x12345678;
  unsigned long net_addr;

  // 在小端序 CPU 上会有不同的结果；
  // 大端序上相同
  net_port = htons(host_port);
  net_addr = htonl(host_addr);

  printf("Host ordered port: %#x \n", host_port);
  printf("Net ordered port: %#x \n", net_port);
  printf("Host ordered address: %#lx \n", host_addr);
  printf("Net ordered address: %#lx \n", net_addr);

  return 0;
}