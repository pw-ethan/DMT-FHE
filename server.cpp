/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: server.cpp
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

#include <iostream>

#include "VTree.h"
#include "PTree.h"
#include "commons.h"

using namespace std;

void get_weights(int n, vector<VerifierTree::plaintext_t> &weights)
{
	weights.clear();
	for(int i = 0; i < n; ++i){
		weights.push_back(i+1);
	}
}

void encrypt_weights(vector<VerifierTree::plaintext_t> &wghts, vector<ProverTree::ciphertext_t> &e_wghts)
{
	e_wghts.clear();
	for(auto wght: wghts){
		e_wghts.push_back(wght);
	}
}


int main()
{
	VerifierTree vtree;

	vector<VerifierTree::plaintext_t> wghts;
	for (int i = 0; i < 8; ++i)
	{
		if(vtree.IsFull()){
			get_weights(power_two(vtree.getDepth()), wghts);
			vtree.updateVTree(wghts);
		}
		vtree.appendValue(1);
	}

	ProverTree ptree;
	
	return 0;
}

