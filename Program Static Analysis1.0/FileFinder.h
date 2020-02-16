#pragma once
#include<iostream>
#include<io.h>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<string>
//现在设定的文件最大数量：50
#define NUMBER_MAX 50
using namespace std;
//每一个函数直接可以使用
//vector要push_back，不能[]，共同子集为空没有显示注意
class FileFinder
{
public:
	FileFinder(string filepath1, string filepath2);//传入两个文件夹绝对路径
	vector<string>& getAllFiles1();//原来版本文件夹中的全部路径，对应filepath1
	vector<string>& getAllFiles2();//后来版本文件夹中的全部路径，对应filepath2
	void getCommonFilenames(vector<string>& common1, vector<string>& common2);//共同文件绝对路径分别存在common1和common2
	vector<string>& getOtherFiles1();//原来版本文件夹除共同文件的其他文件
	vector<string>& getOtherFiles2();//后来版本文件夹除共同文件的其他文件
	int getNumberOfCommonFiles();//返回文件名共同的对数
	string filenames1[NUMBER_MAX];//保存第一份文件夹内所有的文件名
	string filenames2[NUMBER_MAX];//保存第二份文件夹内所有的文件名
	int getCommonSize();//获得匹配的文件数目

private:
	vector<string> allFiles1, allFiles2, commonFiles1, commonFiles2, otherFiles1, otherFiles2;
	int size1, size2, commonSize;
	int sign1[NUMBER_MAX], sign2[NUMBER_MAX];//共同文件在文件1和文件2中的位置标记
};