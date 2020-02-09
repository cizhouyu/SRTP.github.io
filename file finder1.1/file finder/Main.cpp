//目标是提取出两个文件夹中相同文件名的文件，并且记下他们的路径
//现在设定的文件最大数量：50

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

void getFiles( string path, vector<string>& files );
int file_finder(char * filepath1,char * filepath2 , string route1[NUMBER_MAX],string route2[NUMBER_MAX]);

//将两个文件夹内名字相同的文件，它们的本地绝对路径分别存入route1[]和route2[]
int main()
{
	//输入第一份文件夹的绝对路径
	char * filePath1 = "D:\\a";//在这里输入第一份文件夹的本地绝对路径
	char * filePath2 = "D:\\b";//在这里输入第二份文件夹的本地绝对路径
	string Path1[NUMBER_MAX] = {};//用于存放位于一的相同文件路径
	string Path2[NUMBER_MAX] = {};//用于存放位于二的相同文件路径
	int numbers=0;
	numbers=file_finder( filePath1 ,filePath2 , Path1 ,Path2 );
	cout << "共有" << numbers << "个文件名相同的文件" << endl;
	system("pause");
	return 1;
}
// 从文件夹获取所有文件的绝对路径，path是文件夹绝对路径，files是存储文件夹所有子文件的绝对路径的容器
void getFiles( string path, vector<string>& files )
{
	//文件句柄
	long   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}

//从绝对路径获得文件名
void getFilenames(vector<string>& files, string filenames[NUMBER_MAX])
{
	int size = files.size();
	for (int j = 0; j < size; j++)
	{
		int iBeginIndex = files[j].find_last_of("\\") + 1;
		int iEndIndex = files[j].length();
		filenames[j] = files[j].substr(iBeginIndex, iEndIndex - iBeginIndex);
		//cout << filenames[j] << endl;
	}
}

//比较两个文件夹里的文件名，获得共同的文件名
int getCommonFilenames(string filenames1[],string filenames2[],string path1[],string path2[],vector<string>&files1,vector<string>&files2 )
{
	int size1 = files1.size();
	int size2 = files2.size();
	int t1 = 0;//t1记录了名字相同的文件数量，从0开始
	for (int j = 0; j < size1; j++)
	{
		for (int m = 0; m < size2; m++)
		{
			if (filenames1[j] == filenames2[m]) {
				path1[t1] = files1[j];
				path2[t1] = files2[m];
				t1++;
			}
		}
	}

	//输出相同文件名及其fullpath
	for (int k = 0; k < t1; k++)
	{
		cout << "第" << k+1 << "对:" << endl;
		cout << path1[k] << endl;
		cout << path2[k] << endl;
	}

	return t1;
}
//传入两个本地绝对路径，和两个保存路径的数组；返回相同文件的个数
int file_finder(char * filepath1,char * filepath2 , string path1[NUMBER_MAX],string path2[NUMBER_MAX])
{
	vector<string> files1;
	//获取该路径下的所有文件
	getFiles(filepath1, files1 );
	int size1 = files1.size();
	cout<<"第一份文件夹内部文件:"<<endl;//输出第一份文件夹内的所有文件
	for (int i = 0;i < size1;i++)
	{
		cout<<files1[i]<<endl;
	}

	vector<string> files2;
	//获取该路径下的所有文件
	getFiles(filepath2, files2 );
	int size2 = files2.size();
	cout<<"第二份文件夹内部文件:"<<endl;//输出第二份文件夹内的所有文件
	for (int i = 0;i < size2;i++)
	{
		cout<<files2[i]<<endl;
	}

	//从files1中提取出文件名，存入string数组filenames1[NUMBER_MAX]
	string filenames1[NUMBER_MAX]={};
	getFilenames(files1, filenames1);

	//从files2中提取出文件名，存入string数组filenames2[NUMBER_MAX]
	string filenames2[NUMBER_MAX] = {};
	getFilenames(files2, filenames2);

	//比较两份文件夹内的文件名，输出名字相同文件的名字及其路径
	return getCommonFilenames(filenames1, filenames2, path1, path2, files1, files2);
}