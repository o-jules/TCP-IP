# 基于 TCP 的服务器端/客户端

## 理解 TCP 和 UDP

根据数据传输方式的不同，基于网络协议的套接字一般分为 TCP套接字 和 UDP 套接字。因为 TCP 是面向连接的，因此又称为 基于流（stream）的套接字。

TCP 是 Transmission Control Protocol （传输控制协议）的简写，意为“对数据传输过程的控制”。

### TCP/IP 协议栈

TCP/IP协议栈（Stack层）如图所示：

    应用层
  /        \
TCP层      UDP层
  \        /
     IP层
      |
    链路层

（数据通信中使用的协议栈分为 7 层，这里的 4 层对于理解TCP/IP协议就足够了）

