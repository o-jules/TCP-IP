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