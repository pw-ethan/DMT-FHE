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

#include <iostream>
#include <string>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


const int OK = 0;
const int NG = -1;

const int MAX = 4096;

const std::string LOCAL("127.0.0.1");
const int PORT = 11111;

typedef int sockfd_t;

class Socket
{
    public:
        Socket(sockfd_t fd = NG); // also a default constructors
        ~Socket(); // non-virtual destructor
        bool create(int domain = PF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_IP);
        bool bind(int port, const std::string host = LOCAL, int domain = AF_INET);
        bool listen(int connum = 1) const;
        bool accept(Socket &tos) const;
        bool connect(int port, const std::string host = LOCAL, int domain = AF_INET) const;
        bool recvMsg(std::string &recv_buf) const;
        bool sendMsg(const std::string &send_buf) const;
    private:
        sockfd_t m_Sockfd;
        struct sockaddr_in m_addr;

        bool IsOK(int fd) const;
};


#endif

