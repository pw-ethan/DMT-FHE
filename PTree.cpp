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
	logMsg("update PTree", LOG::Info);
	return false;
}

bool ProverTree::appendValue(const ciphertext_t &val)
{
	logMsg("ptree append value", LOG::Info);
	return false;
}

bool ProverTree::query(int index, std::vector<ciphertext_t> &auth) const
{
	logMsg("query", LOG::Info);
	return false;
}


void ProverTree::print() const
{
	std::cout << "capacity : " << capacity 
		<< "\n    size : " << size 
		<< "\n   depth : " << depth << std::endl;
	
	std::cout << "tree structure :" << std::endl;
	/*for(auto itd = vtree.begin(); itd != vtree.end(); ++itd){
		for(auto itv = itd->begin(); itv != itd->end(); ++itv){
			std::cout << *itv << "\t";
		}
		std::cout << std::endl;
	}*/
	std::cout << std::endl;
}