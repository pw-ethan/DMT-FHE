/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: socket.h
 *  简要描述:.
 *
 *  创建日期: 2017年04月24日
 *  作者: pw-ethan
 *  说明:.
 *
 *  修改日期:.
 *  作者:.
 *  说明:.
 ******************************************************************/
#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define OK  (0)
#define NG  (-1)

#define MAX (4096)

#define LOCAL ("127.0.0.1")
#define PORT  (11111)

typedef int sockfd_t;

class Socket
{
    public:
        Socket(sockfd_t fd = NG);
        ~Socket();
        bool creat(int domain = PF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_IP);
        bool bind(int port, string host = LOCAL);
        bool listen(int connum = 1) const;
        bool accept(Socket &mesg) const;
        bool connect(int port, string host = LOCAL);
        bool recvMsg(Socket &mesg, string &recv_buf);
        bool sendMsg(Socket &mesg, string &send_buf);
    private:
        sockfd_t m_Sockfd;
        struct sockaddr_in m_addr;

        bool IsOK(sockfd_t fd) const;
};


#endif

