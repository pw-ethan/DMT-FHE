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

void encrypt_weights(const vector<VerifierTree::plaintext_t> &wghts, vector<ProverTree::ciphertext_t> &e_wghts)
{
	e_wghts.clear();
	for(auto wght: wghts){
		e_wghts.push_back(wght);
	}
}

void decrypt_auth(const vector<ProverTree::ciphertext_t> &e_auth, vector<VerifierTree::plaintext_t> &auth)
{
	auth.clear();
	for(auto item : e_auth){
		auth.push_back(item);
	}
}

void print_vector(const vector<ProverTree::ciphertext_t> &v)
{
	for(auto i : v){
		cout << i << " ";
	}
	cout << endl;
}


int main()
{
	VerifierTree vtree;
	ProverTree ptree;

	vector<VerifierTree::plaintext_t> wghts;
	vector<ProverTree::ciphertext_t> e_wghts;
	for (int i = 0; i < 8; ++i)
	{
		if(vtree.IsFull()){
			get_weights(power_two(vtree.getDepth()), wghts);
			vtree.updateVTree(wghts);

			encrypt_weights(wghts, e_wghts);
			ptree.updatePTree(e_wghts);
		}
		vtree.appendValue(1);
		ptree.appendValue(1);
	}

	VerifierTree::plaintext_t data;
	vector<ProverTree::ciphertext_t> e_auth;
	ptree.query(2, data, e_auth);

	vector<VerifierTree::plaintext_t> auth;
	decrypt_auth(e_auth, auth);
	if(vtree.verify(2, data, auth)){
		cout << "verify succeed" << endl;
	}
	
	return 0;
}

