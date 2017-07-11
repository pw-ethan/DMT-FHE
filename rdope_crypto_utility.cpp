/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved. 
 *
 *  文件名称: rdope_crypto_utility.cpp
 *  简要描述: 
 *
 *  创建日期: 2017年07月10日
 *  作者: pw-ethan
 *  说明: 
 *
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/

#include "rdope_crypto_utility.h"

#include <random>
#include <functional>
#include <set>
#include <fstream>
#include <sstream>
#include <json/json.h>

#include "hrdope.h"

#include <iostream>

void rdOPE::initKeyTable() {
	std::set<int> sNumbers;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, m_nKeyRange);
	auto dice = std::bind(dis, gen);

	// randomly choose rcn possibly distinct numbers
	while (sNumbers.size() < m_nReadingsRange * m_nCellSize  * m_nNumbersOfSensors) {
		sNumbers.insert(dice());
	}
	// for(auto it = sNumbers.begin(); it != sNumbers.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;

	// partition into r groups
	// randomly sample c numbers from group i without replacement
	std::vector<int> vNumbers(sNumbers.begin(), sNumbers.end());
	std::uniform_int_distribution<> dis_sample(0, m_nNumbersOfSensors * m_nCellSize - 1);
	auto dice_sample = std::bind(dis_sample, gen);
	
	auto itSR = m_mSensorsReadings.begin();
	while (itSR != m_mSensorsReadings.end()) {
		unsigned index = 0;
		std::vector<std::vector<int>> OnekeyTable;
		while (index != vNumbers.size()) {
			std::set<int> sSamples;
			while (sSamples.size() < m_nCellSize) {
				sSamples.insert(vNumbers[index + dice_sample()]);
			}
			std::vector<int> tmp(sSamples.begin(), sSamples.end());
			OnekeyTable.push_back(tmp);
			index += m_nNumbersOfSensors * m_nCellSize;
		}
		m_mKeyTables[itSR->first] = OnekeyTable;
		++itSR;
	}

	auto itKT = m_mKeyTables.begin();
	while (itKT != m_mKeyTables.end()) {
		std::cout << itKT->first << std::endl;
		unsigned szi = (itKT->second).size();
		for (unsigned i = 0; i < szi; ++i) {
			unsigned szj = (itKT->second)[i].size();
			for (unsigned j = 0; j < szj; ++j) {
				std::cout << (itKT->second)[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		++itKT;
	}
}

int rdOPE::encrypt(int plaintext,const std::string& sensor, const std::string& hkey) {
	HCode code(hkey, plaintext);
	std::hash<HCode> h;
	unsigned j = plaintext - m_mSensorsReadings[sensor]->m_nMinReading;
	unsigned v = h(code) % m_nCellSize;
	return m_mKeyTables[sensor][j][v];
}

void rdOPE::initSensorsReadings() {
	std::cout << "initSensorsReadings..." << std::endl;
	std::ifstream fin(CONFIG_FILE_PATH);
	std::string buffer;
	std::ostringstream sout;
	while(getline(fin, buffer)){
		sout << buffer;
	}
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(sout.str(), root)){
		// n --
		m_nNumbersOfSensors = root["NumberOfSensors"].asInt();
		// r --
		m_nReadingsRange = root["ReadingsRange"].asInt();
		// b -- (r * c * n) * extend
		m_nKeyRange = RANGE_EXTEND * m_nReadingsRange * m_nCellSize * m_nNumbersOfSensors;

		Json::Value sensors = root["Sensors"];
		if (m_nNumbersOfSensors == sensors.size()) {
			for (unsigned i = 0; i < sensors.size(); ++i) {
				m_mSensorsReadings[sensors[i]["NameOfSensor"].asString()] = std::make_shared<SensorReadingInfo>(
					sensors[i]["MinReading"].asInt(),
					sensors[i]["MinReading"].asInt() + m_nReadingsRange);
			}
		}
	}

	// std::cout << m_mSensorsReadings["HeartRate"]->m_nMinReading << std::endl;
	// std::cout << m_mSensorsReadings["Temperature"]->m_nMaxReading << std::endl;
}

void rdOPE::initCipherTable(const std::string& hkey) {
	auto itSR = m_mSensorsReadings.begin();
	while (itSR != m_mSensorsReadings.end()) {
		std::unordered_map<int, int> OneCipherTable;
		int min = itSR->second->m_nMinReading;
		int max = itSR->second->m_nMaxReading;
		int plaintext = min;
		while (plaintext < max) {
			HCode code(hkey, plaintext);
			std::hash<HCode> h;
			unsigned j = plaintext - min;
			unsigned v = h(code) % m_nCellSize;
			OneCipherTable[m_mKeyTables[itSR->first][j][v]] = plaintext;
			++plaintext;
		}
		m_mCipherTables[itSR->first + hkey] = OneCipherTable;
		++itSR;
	}
}

int rdOPE::decrypt(int ciphertext, const std::string& sensor, const std::string& hkey) {
	return m_mCipherTables[sensor + hkey][ciphertext];
}
