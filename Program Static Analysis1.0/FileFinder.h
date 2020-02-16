#pragma once
#include<iostream>
#include<io.h>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<string>
//�����趨���ļ����������50
#define NUMBER_MAX 50
using namespace std;
//ÿһ������ֱ�ӿ���ʹ��
//vectorҪpush_back������[]����ͬ�Ӽ�Ϊ��û����ʾע��
class FileFinder
{
public:
	FileFinder(string filepath1, string filepath2);//���������ļ��о���·��
	vector<string>& getAllFiles1();//ԭ���汾�ļ����е�ȫ��·������Ӧfilepath1
	vector<string>& getAllFiles2();//�����汾�ļ����е�ȫ��·������Ӧfilepath2
	void getCommonFilenames(vector<string>& common1, vector<string>& common2);//��ͬ�ļ�����·���ֱ����common1��common2
	vector<string>& getOtherFiles1();//ԭ���汾�ļ��г���ͬ�ļ��������ļ�
	vector<string>& getOtherFiles2();//�����汾�ļ��г���ͬ�ļ��������ļ�
	int getNumberOfCommonFiles();//�����ļ�����ͬ�Ķ���
	string filenames1[NUMBER_MAX];//�����һ���ļ��������е��ļ���
	string filenames2[NUMBER_MAX];//����ڶ����ļ��������е��ļ���
	int getCommonSize();//���ƥ����ļ���Ŀ

private:
	vector<string> allFiles1, allFiles2, commonFiles1, commonFiles2, otherFiles1, otherFiles2;
	int size1, size2, commonSize;
	int sign1[NUMBER_MAX], sign2[NUMBER_MAX];//��ͬ�ļ����ļ�1���ļ�2�е�λ�ñ��
};