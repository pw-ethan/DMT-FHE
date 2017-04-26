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

using namespace std;

int main()
{
	vector<VerifierTree::plaintext_t> v0 = {0};
	vector<VerifierTree::plaintext_t> v1 = {0, 1};
	vector<VerifierTree::plaintext_t> v2 = {0, 1, 2, 3};
	vector<VerifierTree::plaintext_t> v3 = {0, 1, 2, 3, 4, 5, 6, 7};

	VerifierTree vtree;
	vtree.updateVTree(v0);
	vtree.print();
	vtree.updateVTree(v1);
	vtree.print();
	vtree.updateVTree(v2);
	vtree.print();
	vtree.updateVTree(v3);
	vtree.print();
	return 0;
}

