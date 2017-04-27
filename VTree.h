/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: VTree.h
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
#ifndef VERIFIER_TREE_H
#define VERIFIER_TREE_H

#include <vector>
#include <deque>

class VerifierTree
{
public:
	typedef int plaintext_t;

private:
	static const plaintext_t ZERO = 0;

public:
	VerifierTree() = default;
	~VerifierTree();
	bool updateVTree(const std::vector<plaintext_t> &weights);
	bool appendValue(const plaintext_t &val);
	bool verify(int index, const plaintext_t &data, const std::vector<plaintext_t> &auth) const;

private:
	std::vector<plaintext_t> evidence;
	int depth = 0;
	int size = 0;
	int capacity = 0;
	std::deque<std::vector<plaintext_t>> vtree;

// prevent copying
private:
	VerifierTree(const VerifierTree&);
	VerifierTree& operator=(const VerifierTree&);



public:
	bool IsFull() const; // judge whether the tree is full
	int getDepth() const;
	void print() const;

};

inline bool VerifierTree::IsFull() const
{
	return capacity == size;
}

inline int VerifierTree::getDepth() const
{
	return depth;
}


#endif
