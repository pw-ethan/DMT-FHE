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

const VerifierTree::plaintext_t VerifierTree::ZERO;

VerifierTree::~VerifierTree()
{
	logMsg("VerifierTree dtor", LOG::Info);
}

bool VerifierTree::updateVTree(const std::vector<plaintext_t> &weights)
{
	logMsg("update vtree", LOG::Info);
	if(weights.empty() || weights.size() - power_two(depth) != 0){
		logMsg("VerifierTrees::updateVTree() -- parameter error", LOG::Error);
		return false;
	}
	
	std::vector<plaintext_t>::size_type index = 0;
	std::vector<plaintext_t> newlayer;
	newlayer.push_back(weights[index++]);
	vtree.push_front(newlayer);

	for(std::deque<std::vector<plaintext_t>>::size_type i = 1; i < vtree.size(); ++i){
		std::vector<plaintext_t>::size_type sz = vtree[i].size();
		for(std::vector<plaintext_t>::size_type j = 0; j < sz; ++j){
			vtree[i].push_back(weights[index++]);
		}
	}

	if(evidence.empty()){
		evidence.push_back(ZERO);
	}else{
		evidence.push_back(evidence.back() * weights[0]);
	}

	if(0 == capacity){
		capacity = 1;
	}
	else{
		capacity *= 2;
	}
	depth += 1;

	//print();
	return true;
}

bool VerifierTree::appendValue(const plaintext_t &val)
{
	logMsg("vtree append value", LOG::Info);
	int offset = size;
	plaintext_t valueAdd2Evidence = val;
	for(auto itd = vtree.rbegin(); itd != vtree.rend() - 1; itd++){
		valueAdd2Evidence *= (*itd)[offset];
		offset /= 2;
	}
	evidence.back() += valueAdd2Evidence;
	size += 1;

	//print();
	return true;
}

bool VerifierTree::verify(int index, const plaintext_t &data, const std::vector<plaintext_t> &auth) const
{
	logMsg("verify", LOG::Info);

	return false;
}

void VerifierTree::print() const
{
	std::cout << "capacity : " << capacity 
		<< "\n    size : " << size 
		<< "\n   depth : " << depth << std::endl;

	std::cout << "evidence : ";
	for(auto it = evidence.begin(); it != evidence.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	std::cout << "tree structure :" << std::endl;
	for(auto itd = vtree.begin(); itd != vtree.end(); ++itd){
		for(auto itv = itd->begin(); itv != itd->end(); ++itv){
			std::cout << *itv << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}