/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: rdope_crypto_utility.cpp
 *  简要描述: 
 *
 *  创建日期: 2017年07月10日
 *  作者: pw-ethan
 *  说明: 
 *
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/

#include "rdope_crypto_utility.h"

#include <random>
#include <functional>
#include <set>

#include "hrdope.h"

#include <iostream>

void rdOPE::init() {
	std::set<int> numbers;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, m_nKeyRange);
	auto dice = std::bind(dis, gen);

	// randomly choose rcn possibly distinct numbers
	while (numbers.size() < m_nReadingsRange * m_nTableSize /* * m_nSensors */) {
		numbers.insert(dice());
	}
	// for(auto it = numbers.begin(); it != numbers.end(); ++it) {
	// 	std::cout << *it << std::endl;
	// }

	// partition into r groups
	// randomly sample c numbers from group i without replacement
	auto it = numbers.begin();
	while(it != numbers.end()) {
		std::vector<int> tmp;
		for (unsigned i = 0; i < m_nTableSize; ++i) {
			tmp.push_back(*it++);
		}
		m_vKeyTable.push_back(tmp);
	}
	for (auto it = m_vKeyTable.begin(); it != m_vKeyTable.end(); ++it) {
		for (auto i : *it) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}

// assume plaintext [1,r]
int rdOPE::encrypt(int plaintext, const std::string& key) {
	HCode code(key, plaintext);
	std::hash<HCode> h;
	return m_vKeyTable[plaintext - 1][h(code) % m_nTableSize];
}
