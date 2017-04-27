/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: commons.h
 *  简要描述:.
 *
 *  创建日期: 2017年04月26日
 *  作者: pw-ethan
 *  说明:.
 *
 *  修改日期:.
 *  作者:.
 *  说明:.
 ******************************************************************/
#ifndef COMMONS_H
#define COMMONS_H

#include <iostream>
#include <string>

namespace LOG{
	enum {Info, Error};
};

inline void logMsg(const std::string msg, int type)
{
#ifdef DEBUG
	switch(type){
		case LOG::Info:
			std::cout << "[Info] ";
			break;
		case LOG::Error:
			std::cerr << "[Error] ";
			break;
	}
	std::cout << msg << std::endl;
#endif
}

inline int power_two(int n)
{
	return 1 << n;
}


#endif

