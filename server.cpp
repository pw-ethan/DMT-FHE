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
#include <fstream>
#include <sstream>
#include <string>
#include <json/json.h>

#include "VTree.h"
#include "PTree.h"
#include "commons.h"
#include "libsocket.h"
#include "thread_pool.h"
#include "task.h"
#include "task_process.h"

using namespace std;

const int SERVER_PORT = 22222;

void get_weights(int n, vector<VerifierTree::plaintext_t> &weights)
{
	weights.clear();
	for(int i = 0; i < n; ++i){
		weights.push_back(i + 1);
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

string filename = "/home/pw-ethan/workspace/io.dat";

string recv()
{
	ifstream fin(filename);
	string buffer;
	ostringstream sout;
	while(getline(fin, buffer)){
		sout << buffer;
	}
	return sout.str();
}

void process(string request)
{
	cout << request << endl;
	Json::Reader reader;
	Json::Value root;
	if(reader.parse(request, root)){
		cout << root["username"].asString() << endl;
	}
}


int main()
{
	CThreadPool pool;

	shared_ptr<Socket> pServer(new Socket);
	if(pServer->init_server()) {
		cerr << "init server error" << endl;
		exit(1);
	}
	if (!pServer->listen()) {
		cerr << "listen error" << endl;
		exit(1);
	}

	while (1) {
		unique_ptr<Socket> pc = pServer->accept();
		if(!pc) {
			cerr << "accept error" << endl;
			exit(1);
		}
		CTaskProcess task(move(pc));
		pool.submit(move(task));
	}
	
	// CThreadPool pool;

	// vector<future<int>> futures(20);
	// int result = 0;
	// for(int i = 1; i <= 20; ++i){
	// 	CTask tmp(i);
	// 	futures[i-1] = pool.submit(tmp);
	// }

	// for(unsigned i = 0; i < 20; ++i) {
	// 	result += futures[i].get();
	// }

	// cout << result << endl;

	// string request = recv();
	// process(request);

	// Socket server, client;
 //    server.create();
 //    server.bind(SERVER_PORT);
 //    server.listen();

 //    server.accept(client);

 //    string buf;
 //    //while(1){
 //        client.recvMsg(buf);
 //        cout << "receive message : " << buf << endl;
 //        // if(buf == "exit"){
 //        //     break;
 //        // }
 //        client.sendMsg(buf);
    //}

	// VerifierTree vtree;
	// ProverTree ptree;

	// vector<VerifierTree::plaintext_t> wghts;
	// vector<ProverTree::ciphertext_t> e_wghts;
	// for (int i = 0; i < 8; ++i)
	// {
	// 	if(vtree.IsFull()){
	// 		get_weights(power_two(vtree.getDepth()), wghts);
	// 		vtree.updateVTree(wghts);

	// 		encrypt_weights(wghts, e_wghts);
	// 		ptree.updatePTree(e_wghts);
	// 	}
	// 	vtree.appendValue(1);
	// 	ptree.appendValue(1);
	// }

	// VerifierTree::plaintext_t data;
	// vector<ProverTree::ciphertext_t> e_auth;
	// ptree.query(2, data, e_auth);

	// vector<VerifierTree::plaintext_t> auth;
	// decrypt_auth(e_auth, auth);
	// if(vtree.verify(2, data, auth)){
	// 	cout << "verify succeed" << endl;
	// }
	
	return 0;
}

