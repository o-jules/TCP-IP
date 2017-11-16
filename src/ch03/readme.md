# 地址族与数据序列

## 分配给套接字的IP地址与端口号

IP： Internet Protocol 的简写，是为了收发网络数据而分配给计算机的值。
端口号： 为了区分程序中创建的套接字而分配给套接字的序号。

### 网络地址

IP地址两类：

IPv4: 4字节地址族；
IPv6: 16字节地址族。

### 网络地址分类与主机地址边界

只需要通过IP地址的第一个字节即可判断网络地址占用的字节数，因为我们根据IP地址的边界区分网络地址，如下所示：

A类地址的首字节范围：0 ~ 127
B类地址的首字节范围：128 ~ 191
C类地址的首字节范围：192 ~ 223

### 用于区分套接字的端口号

端口号为了在同一操作系统中区分不同的套接字而设置的，因此无法将相同的端口号分配给不同的套接字。
虽然端口号不能重复，但TCP套接字和UDP套接字不会共用端口号，所以允许重复。

端口号由16位构成，范围是 0 ~ 65535。

## 地址信息的表示

### 表示IPv4地址的结构体

```c
struct sockaddr_in
{
  sa_family_t     sin_family; // 地址族（address family）
  uint16_t        sin_port;   // 16位的TCP/UDP端口号
  struct int_addr sin_addr;   // 32位的IP地址
  char            sin_zero[8];// 不使用
};

struct in_addr {
  in_addr_t s_addr; // 一般是32位的IPv4地址
};
```

POSIX定义的类型：

`sa_family_t`：地址族（address family），头文件：`sys/socket.h`
`socklen_t`：长度，头文件：`sys/socket.h`
`in_addr_t`：IP 地址，一般声明为 `uint32_t`，头文件：`netinet/in.h`
`in_port_t`：端口号，一般声明为 `uint16_t`，头文件：`netinet/in.h`

### 结构体 `sockaddr_in` 的成员分析

1. `sin_family`

每种协议族适用的地址族均不同。

|    地址族（Address Family）    |           含义               |
|------------------------------|------------------------------|
|           AF_INET            |  IPv4 网络协议中使用的地址族    |
|           AF_INET6           |  IPv6 网络协议中使用的地址族    |
|           AF_LOCAL           |  本地通信中采用的UNIX协议地址族  |

2. `sin_port`

保存了16位的端口号，以**网络字节序**保存。

3. `sin_addr`

保存32位的IP地址信息，以**网络字节序**保存。

4. `sin_zero`

无特殊含义。只是为了使结构体 `sockaddr_in` 的大小 与 结构体 `sockaddr` 保持一致而插入的成员。
必需填充为0，否则无法得到想要的结果。

### `sockaddr` 的结构

```c
struct sockaddr {
  sa_family_t sin_family; // 地址族（Address Family）
  char sa_data[14]; // 地址信息
}
```

由于结构提 `sockaddr` 并非只为IPv4设计，所以要求在 sa_family 中指定地址族信息；为了与 `sockaddr` 保持一致，`sockaddr_in` 中也有地址族信息。

## 网络字节序与地址变换

### 字节序与网络字节序

CPU 向内存保存数据的方式有 2 种，这意味着 CPU 解析数据的方式也分为 2 种。

- 大端序（Big Endian）高位字节存放到低位地址（放在前）
- 小端序（Little Endian）高位字节存放到高位地址（放在后）

目前主流的Intel系列CPU以小端序方式保存数据。
关于大小端，详情参见[大小端](/appendix/endian/readme.md);

由于不同计算机之间采用的字节序不同，数据传输后解析可能出现问题。因此，在通过网络传输数据时约定统一方式，这种约定称为**网络字节序**，并统一为大端序。

即，在进行网络数据传输时，需要将数据数组统一转化成大端格式。

### 字节序转换

帮助转换字节序的函数有：

```c
unsigned short htons(unsigned short);
unsigned short ntohs(unsigned short);
unsigned long ntohs(unsigned long);
unsigned long ntohs(unsigned long);
```

其中，h 代表 host，n 代表 network；s 代表short，l 代表long（Linux中long类型占用 4 个字节）。

### 数据转换的必要性

并不是所有的数据都需要手动转换，很多时候都是自动的过程。一般除去向 sockaddr_in 结构体变量填充数据外，其他情况无需考虑字节序问题。

## 网络地址的初始化与分配

### 将字符串信息转换为网络字节序的整数型

`sockaddr_in` 中保存地址信息的成员为32为整数型。因此，为了分配 IP 地址，需要将其表示为 32 位整数型数据。

该功能可以通过一下函数实现：

```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char *string);
```

还有一个函数也能实现：

```c
#include <arpa/inet.h>

int inet_aton(const char *string, struct in_addr *addr);
// string 需要转换的IP地址信息的字符串
// addr 将保存转换结果的 in_addr 结构体变量的地址值
```

`inet_aton` 与 `inet_addr` 函数在功能上完全相同，只不过利用了in_addr结构体，其使用频率更高。

相反的转换函数，即将数值地址转换成字符串：

```c
#include <arpa/inet.h>

char * inet_ntoa(struct in_addr addr);
```

### 客户端地址信息初始化

上述网络地址信息初始化过程主要针对服务器而非客户端。
服务器端的准备工作通过bind函数来完成，而客户端则通过connect函数来完成。因此，函数调用前需要准备的地址值类型也不同。
服务器端声明 `sockaddr_in` 结构体变量，将其初始化为赋予服务器端IP和套接字的端口，然后调用`bind`函数；而客户端则声明 `sockaddr_in` 结构体变量，并初始化为要与之连接的的服务器端套接字的IP和端口号，然后调用`connect`函数。
