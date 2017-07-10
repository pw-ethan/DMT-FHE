/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: hrdope.h
 *  简要描述:.
 *
 *  创建日期: 2017年07月10日
 *  作者: pw-ethan
 *  说明:.
 *
 *  修改日期:.
 *  作者:.
 *  说明:.
 ******************************************************************/
#ifndef HRDOPE_H
#define HRDOPE_H

#include <functional>
#include <string>

struct HCode {
	HCode(const std::string &k, int v) : key(k), xi(v) {}
	const std::string &key;
	int xi;
};

namespace std{
	template <>
	class hash<HCode> {
	public:
		size_t operator()(const HCode& hc) const {
			size_t h1 = std::hash<std::string>()(hc.key);
			size_t h2 = std::hash<int>()(hc.xi);
			return h1 ^ (h2 << 1);
		}
	};
}

#endif

