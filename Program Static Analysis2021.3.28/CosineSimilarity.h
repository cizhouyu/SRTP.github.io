#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include<cstring>
#include <string>
#include <map>
#include<fstream>
#include<io.h>
#include<sstream>
#include<vector>
#include<cstdlib>
#include <sys/types.h>
#include<deque>
#include<algorithm>
#include <fcntl.h>

#define NUMBER_MAX 50

using namespace std;
#pragma warning(disable:4996)
#pragma warning(disable:4430)
bool word_segment_(const std::string& substr);


float compare(const std::string& ref1, const std::string& ref2);


//���ļ����뵽string��
string readFileIntoString(string filename);
//�þ���·�����ļ����뵽string��
string readFileThroughPath(string path);