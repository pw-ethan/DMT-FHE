/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: VTree.cpp
 *  简要描述: 
 *
 *  创建日期: 2017年04月26日
 *  作者: pw-ethan
 *  说明: 
 *
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/

#include "VTree.h"
#include "commons.h"

VerifierTree::~VerifierTree()
{
	logMsg("dtor", LOG::Info);
}

bool VerifierTree::updateVTree(const std::vector<plaintext_t> &weights)
{
	logMsg("update VTree", LOG::Info);
	if(weights.empty() || weights.size() - power_two(depth) != 0){
		logMsg("VTree::updateVTree() -- parameter error", LOG::Error);
		return false;
	}

	if(0 == capacity){
		capacity = 1;
	}
	else{
		capacity *= 2;
	}
	depth += 1;
	
	std::vector<plaintext_t>::size_type index = 0;
	std::vector<plaintext_t> newlayer;
	newlayer.push_back(weights[index++]);
	vtree.push_back(newlayer);

	for(std::vector<std::vector<plaintext_t>>::size_type i = 0; i < vtree.size() - 1; ++i){
		std::vector<plaintext_t>::size_type sz = vtree[vtree.size() - i - 2].size();
		for(std::vector<plaintext_t>::size_type j = 0; j < sz; ++j){
			vtree[vtree.size() - i - 2].push_back(weights[index++]);
		}
	}

	return false;
}

bool VerifierTree::appendValue(const plaintext_t &val)
{
	logMsg("append value", LOG::Info);

	return false;
}

bool VerifierTree::verify(int index, const std::vector<plaintext_t> &auth) const
{
	logMsg("verify", LOG::Info);

	return false;
}

void VerifierTree::print() const
{
	for(std::vector<std::vector<plaintext_t>>::size_type i = 0; i < vtree.size(); ++i){
		for(std::vector<plaintext_t>::size_type j = 0; j < vtree[i].size(); ++j){
			std::cout << vtree[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

inline int VerifierTree::power_two(int n) const
{
	return 1 << n;
}

inline bool VerifierTree::IsFull() const
{
	return capacity == size;
}