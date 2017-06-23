#ifndef TASK_PROCESS_H
#define TASK_PROCESS_H

#include <memory>
#include <string>

#include "libsocket.h"
#include "task.h"


class CTaskProcess
{
	std::unique_ptr<Socket> m_pSock;
public:
    CTaskProcess(std::unique_ptr<Socket> pSock) 
    : m_pSock(std::move(pSock)) { }
    
    void operator() () {
        std::string buf;
		while(1) {
			m_pSock->recv_msg(buf);
			if (buf == "exit") {
				break;
			}
			m_pSock->send_msg(buf);
		}
    }
};

#endif // TASK_PROCESS_H