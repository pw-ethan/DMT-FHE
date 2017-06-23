/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: main.cpp
 *  简要描述: 
 *
 *  创建日期: 2017年04月25日
 *  作者: pw-ethan
 *  说明: 
 *
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/

#include <iostream>

#include "libsocket.h"

//#define SERVER
#define CLIENT
using namespace std;

const int SERVER_PORT = 22222;

int main()
{

#ifdef SERVER
    Socket server, client;
    server.create();
    server.bind(SERVER_PORT);
    server.listen();

    server.accept(client);

    string buf;
    while(1){
        client.recvMsg(buf);
        cout << "receive message : " << buf << endl;
        if(buf == "exit"){
            break;
        }
        client.sendMsg(buf);
    }
#endif

#ifdef CLIENT
    Socket client;
    client.init_client();
    client.connect();

    string buf;
    while(getline(cin, buf)){
        client.send_msg(buf);
        cout << "send message : " << buf << endl;

        if(buf == "exit"){
            break;
        }

        client.recv_msg(buf);
        cout << "receive message : " << buf << endl;
    }

#endif
    return 0;
}

