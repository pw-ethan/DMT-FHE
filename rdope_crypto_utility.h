/*******************************************************************
 *  Copyright (C) 2016 PeanutWine Ethan - 1501680@stu.neu.edu.cn
 *  All rights reserved..
 *
 *  文件名称: rdope_crypto_utility.h
 *  简要描述:.
 *
 *  创建日期: 2017年07月10日
 *  作者: pw-ethan
 *  说明:.
 *
 *  修改日期:.
 *  作者:.
 *  说明:.
 ******************************************************************/
#ifndef RDOPE_CRYPTO_UTILITY_H
#define RDOPE_CRYPTO_UTILITY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

const unsigned RANGE_EXTEND = 2;
const std::string CONFIG_FILE_PATH = "/home/pw-ethan/workspace/config.dat";

class rdOPE {
public:
	struct SensorReadingInfo {
		int m_nMinReading;
		int m_nMaxReading;
		SensorReadingInfo(int min, int max) :
			m_nMinReading(min),
			m_nMaxReading(max){ }
	};

	rdOPE(unsigned c = 2) : 
		m_nCellSize(c) { 
			initSensorsReadings();
	}

	~rdOPE() = default;
	rdOPE(const rdOPE&) = delete;
	rdOPE& operator=(const rdOPE&) = delete;

	void initKeyTable();
	void initCipherTable(const std::string& hkey);

	int encrypt(int plaintext,const std::string& sensor, const std::string& hkey);
	int decrypt(int ciphertext, const std::string& sensor, const std::string& hkey);

private:
	void initSensorsReadings();

private:
	unsigned m_nReadingsRange; // r
	unsigned m_nCellSize; // c
	unsigned m_nNumbersOfSensors; // n
	unsigned m_nKeyRange; // b

	std::unordered_map<std::string, std::vector<std::vector<int>>> m_mKeyTables;

	std::unordered_map<std::string, std::unordered_map<int, int>> m_mCipherTables;

	std::unordered_map<std::string, std::shared_ptr<SensorReadingInfo>> m_mSensorsReadings;
};

#endif