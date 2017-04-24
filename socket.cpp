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

#include "socket.h"

Socket::Socket(sockfd_t fd)
{
    m_Sockfd = fd;
}

Socket::~Socket()
{
    if(IsOK(m_Sockfd)){
        close(m_Sockfd);
    }
}

bool Socket::create(int domain, int type, int protocol)
{
    bool ret = false;

    m_Sockfd = socket(domain, type, protocol);
    if(IsOK(m_Sockfd)){
        ret = true;
    }

    return ret;
}

bool Socket::bind(int port, string host)
{

}

bool Socket::listen(int connum) const
{
    
}

bool Socket::accept(Socket &mesg)
{
    
}

bool Socket::connect(int port, string host)
{

}

bool Socket::recvMsg(Socket &mesg, string &recv_buf)
{
    
}

bool Socket::sendMsg(Socket &mesg, string &send_buf)
{
    
}


bool Socket::IsOK(sockfd_t fd)
{
    return fd != NG;
}
