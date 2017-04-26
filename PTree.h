/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: PTree.h
 *  简要描述:.
 *
 *  创建日期: 2017年04月26日
 *  作者: pw-ethan
 *  说明:.
 *
 *  修改日期:.
 *  作者:.
 *  说明:.
 ******************************************************************/
#ifndef PROVER_TREE_H
#define PROVER_TREE_H


#include <vector>

class ProverTree
{
public:
	typedef int ciphertext_t; // type definition

public:
	ProverTree() = default;
	~ProverTree();
	bool updatePTree(const std::vector<ciphertext_t> &weights);
	bool appendValue(const ciphertext_t &val);
	bool query(int index, std::vector<ciphertext_t> &auth) const;

// prevent copying
private:
	ProverTree(const ProverTree&);
	ProverTree& operator=(const ProverTree&);

private:
	int depth = 0;
	int size = 0;
	int capacity = 0;
	std::vector<std::vector<ciphertext_t>> ptree_w;
	std::vector<std::vector<ciphertext_t>> ptree_v;
};

#endif

