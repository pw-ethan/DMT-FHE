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
#include <deque>

class ProverTree
{
public:
	typedef int ciphertext_t; // type definition

private:
	static const ciphertext_t ZERO = 0;

public:
	ProverTree() = default;
	~ProverTree();
	bool updatePTree(const std::vector<ciphertext_t> &weights);
	bool appendValue(const ciphertext_t &val);
	bool query(int index, std::vector<ciphertext_t> &auth) const;


private:
	int depth = 0;
	int size = 0;
	int capacity = 0;
	std::deque<std::vector<ciphertext_t>> ptree_w;
	std::deque<std::vector<ciphertext_t>> ptree_v;

// prevent copying
private:
	ProverTree(const ProverTree&);
	ProverTree& operator=(const ProverTree&);


public:
	bool IsFull() const; // judge whether the tree is full
	int getDepth() const;
	void print() const;

};

inline bool ProverTree::IsFull() const
{
	return capacity == size;
}

inline int ProverTree::getDepth() const
{
	return depth;
}


#endif

