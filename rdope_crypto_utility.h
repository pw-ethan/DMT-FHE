/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: rdope_crypto_utility.h
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
#ifndef RDOPE_CRYPTO_UTILITY_H
#define RDOPE_CRYPTO_UTILITY_H

#include <vector>
#include <string>

const int RANGE_EXTEND = 2;

class rdOPE {
public:
	rdOPE(unsigned r, /*unsigned n = 1,*/ unsigned c = 2) :
		/* m_nSensors(n), */
		m_nReadingsRange(r), 
		m_nKeyRange(RANGE_EXTEND * r * c /* * n */), 
		m_nTableSize(c) { }
	~rdOPE() = default;
	rdOPE(const rdOPE&) = delete;
	rdOPE& operator=(const rdOPE&) = delete;

	void init();

	int encrypt(int plaintext, const std::string& key);


private:
	// unsigned m_nSensors;
	unsigned m_nReadingsRange;
	unsigned m_nKeyRange;
	unsigned m_nTableSize;
	std::vector<std::vector<int>> m_vKeyTable;
};


#endif

