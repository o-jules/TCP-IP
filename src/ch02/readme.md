# 套接字类型与协议设置

```cpp
int socket(int domain, int type, int protocol);
```

- domain：套接字中使用的协议族（Protocol Family）信息

  协议族（Protocol Family），可以分成下面几类：

  * PF_INET，IPv4 互联网协议族
  * PF_INET6，IPv6 互联网协议族
  * PF_LOCAL，本地通信的 UNIX 协议族
  * PF_PACKET，底层套接字的协议族
  * PF_IPX，IPX Novell 协议族

- type：套接字数据传输类型信息
  
  套接字类型是指套接字的数据传输方式。一下是两种常见的数据传输方式：

  * SOCK_STREAM，面向连接的套接字
    可靠的，按顺序传递的，基于字节的

  * SOCK_DGRAM，面向消息的套接字
    不可靠的，不按顺序传递的，以数据的高速传输为目的的

- protocol：计算机间通信中使用的协议信息
  当同一协议族中存在多个数据传输方式相同的协议时，需要指定；其他情况下，可以使用0。
