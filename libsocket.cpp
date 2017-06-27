/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: socket.cpp
 *  简要描述: 
 *
 *  创建日期: 2017年04月24日
 *  作者: pw-ethan
 *  说明: 
 *
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/

#include "libsocket.h"

Socket::Socket(sockfd_t fd)
{
    m_Sockfd = fd;
}

Socket::~Socket()
{
    if(IsOK(m_Sockfd)){
        close(m_Sockfd);
        std::cout << "close fd" << std::endl;
    }
}

int Socket::init_server(
    int port, 
    const std::string host, 
    int domain, 
    int type, 
    int protocol) {

    if ((m_Sockfd = socket(domain, type, protocol)) == NG) {
        return -1; // create socket error
    }

    bzero(&m_addr,sizeof(m_addr));
    m_addr.sin_family = domain;
    m_addr.sin_addr.s_addr = inet_addr(host.c_str());
    m_addr.sin_port = htons(port);

    if (bind(m_Sockfd, (struct sockaddr*)&m_addr, sizeof(m_addr)) == NG) {
        return -2; // bind error
    }

    return 0;
}

bool Socket::listen(int connum) const
{
    bool ret = false;
    int flag = NG;

    if(IsOK(m_Sockfd)){
        flag = ::listen(m_Sockfd, connum);
        if(IsOK(flag)){
            ret = true;
        }
    }

    return ret;
}

bool Socket::accept(Socket &tos) const
{
    bool ret = false;
    int len = sizeof(tos.m_addr);

    if(IsOK(m_Sockfd)){
        tos.m_Sockfd = ::accept(m_Sockfd, (struct sockaddr*)&(tos.m_addr), (socklen_t *)&len);

        if(IsOK(tos.m_Sockfd)){
            ret = true;
        }
        else {
            ret = false;
        }
    }

    return ret;
}

std::unique_ptr<Socket> Socket::accept() const {
    std::unique_ptr<Socket> ret(new Socket);
    int len = sizeof(ret->m_addr);
    if(IsOK(m_Sockfd)) {
        ret->m_Sockfd = ::accept(m_Sockfd, (struct sockaddr*)&(ret->m_addr), (socklen_t*)&len);
        if(IsOK(ret->m_Sockfd)) {
            return ret;
        }
    }
    return nullptr;
}


int Socket::init_client(
    int domain,
    int type,
    int protocol) {

    if ((m_Sockfd = socket(domain, type, protocol)) == NG) {
        return -4; // create socket error
    }

    return 0;
}

bool Socket::connect(int port, const std::string host, int domain) const {
    bool ret = false;
    int flag = NG;

    if(IsOK(m_Sockfd)){
        struct sockaddr_in server_addr;
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family = domain;
        server_addr.sin_addr.s_addr = inet_addr(host.c_str());
        server_addr.sin_port = htons(port);

        flag = ::connect(m_Sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if(IsOK(flag)){
            ret = true;
        }
    }
    return ret;
}

bool Socket::recv_msg(std::string &recv_buf) const
{
    bool ret = false;
    int num = 0;
    char buf[MAX];
    recv_buf.clear();
    memset(buf, 0, MAX);

    if(IsOK(m_Sockfd)){
        num = recv(m_Sockfd, buf, MAX - 1, 0);
        if (num != 0) {
            ret = true;
            recv_buf = buf;
        }
    }

    return ret;
}

bool Socket::send_msg(const std::string &send_buf) const
{
    bool ret = false;
    int flag = NG;

    if(IsOK(m_Sockfd)){
        flag = send(m_Sockfd, send_buf.c_str(), send_buf.length(), 0);
        if(IsOK(flag)){
            ret = true;
        }
    }

    return ret;
}


bool Socket::IsOK(int fd) const
{
    return fd != NG;
}
