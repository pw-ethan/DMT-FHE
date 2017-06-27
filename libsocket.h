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
#include <memory>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


const int OK = 0;
const int NG = -1;

const int MAX = 4096;

const std::string LOCAL_ADDRESS("127.0.0.1");
const int DEFAULT_PORT = 22224;
const int DEFAULT_BACK = 1;

typedef int sockfd_t;

class Socket
{
    public:
        Socket(sockfd_t fd = NG); // also a default constructors
        ~Socket(); // non-virtual destructor
        int init_server(
            int port = DEFAULT_PORT, 
            const std::string host = LOCAL_ADDRESS,
            int domain = PF_INET,
            int type = SOCK_STREAM,
            int protocol = IPPROTO_IP);
        bool listen(int connum = DEFAULT_BACK) const;
        bool accept(Socket &tos) const;
        std::unique_ptr<Socket> accept() const;

        int init_client(
            int domain = PF_INET,
            int type = SOCK_STREAM,
            int protocol = IPPROTO_IP);
        bool connect(
            int port = DEFAULT_PORT,
            const std::string host = LOCAL_ADDRESS,
            int domain = AF_INET) const;

        bool recv_msg(std::string &recv_buf) const;
        bool send_msg(const std::string &send_buf) const;

    private:
        sockfd_t m_Sockfd;
        struct sockaddr_in m_addr;

        bool IsOK(int fd) const;
};


#endif