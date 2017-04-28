/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: PTree.cpp
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

#include "PTree.h"
#include "commons.h"

const ProverTree::ciphertext_t ProverTree::ZERO;

ProverTree::~ProverTree()
{
	logMsg("ProverTree dtor", LOG::Info);
}

	
bool ProverTree::updatePTree(const std::vector<ciphertext_t> &weights)
{
	logMsg("update ptree", LOG::Info);

	if(weights.empty() || weights.size() - power_two(depth) != 0){
		logMsg("ProverTree::updatePTree() -- parameter error", LOG::Error);
		return false;
	}

	// extend value tree
	if(ptree_v.empty()){
		ptree_v.push_back(std::vector<ciphertext_t>(1, ZERO));
	}else{
		std::vector<ciphertext_t> newlayer;
		newlayer.push_back(ptree_v.front().front() * ptree_w.front().front());
		ptree_v.push_front(newlayer);

		for(std::deque<std::vector<ciphertext_t>>::size_type i = 1; i < ptree_v.size(); ++i){
			std::vector<ciphertext_t>::size_type sz = ptree_v[i].size();
			for(std::vector<ciphertext_t>::size_type j = 0; j < sz; ++j){
				ptree_v[i].push_back(ZERO);
			}
		}
	}

	
	// extend weight tree
	std::vector<ciphertext_t>::size_type index = 0;
	std::vector<ciphertext_t> newlayer;
	newlayer.push_back(weights[index++]);
	ptree_w.push_front(newlayer);

	for(std::deque<std::vector<ciphertext_t>>::size_type i = 1; i < ptree_w.size(); ++i){
		std::vector<ciphertext_t>::size_type sz = ptree_w[i].size();
		for(std::vector<ciphertext_t>::size_type j = 0; j < sz; ++j){
			ptree_w[i].push_back(weights[index++]);
		}
	}


	if(0 == capacity){
		capacity = 1;
	}
	else{
		capacity *= 2;
	}
	depth += 1;

	print();
	return true;
}

bool ProverTree::appendValue(const ciphertext_t &val)
{
	logMsg("ptree append value", LOG::Info);

	int offset = size;
	ciphertext_t valueAdd2Evidence = val;
	auto itw = ptree_w.rbegin();
	auto itv = ptree_v.rbegin();
	for(;itv != ptree_v.rend(); ++itw, ++itv){
		(*itv)[offset] += valueAdd2Evidence;
		valueAdd2Evidence *= (*itw)[offset];
		offset /= 2;
	}
	size += 1;

	print();
	return false;
}

bool ProverTree::query(int index, std::vector<ciphertext_t> &auth) const
{
	logMsg("query", LOG::Info);
	if(index >= size){
		logMsg("ProverTree::query() -- parameter error", LOG::Error);
		return false;
	}
	auth.clear();
	int offset = index;
	for(auto it = ptree_v.rbegin(); it != ptree_v.rend() - 1; ++it){
		if(offset & 0x01){
			auth.push_back((*it)[offset - 1]);
		}else{
			auth.push_back((*it)[offset + 1]);
		}
		offset /= 2;
	}
	return true;
}


void ProverTree::print() const
{
	std::cout << "capacity : " << capacity 
		<< "\n    size : " << size 
		<< "\n   depth : " << depth << std::endl;
	
	std::cout << "weight tree structure :" << std::endl;
	for(auto itd = ptree_w.begin(); itd != ptree_w.end(); ++itd){
		for(auto itv = itd->begin(); itv != itd->end(); ++itv){
			std::cout << *itv << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "value tree structure :" << std::endl;
	for(auto itd = ptree_v.begin(); itd != ptree_v.end(); ++itd){
		for(auto itv = itd->begin(); itv != itd->end(); ++itv){
			std::cout << *itv << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}