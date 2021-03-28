//说明：
//1,找匹配文件，在main函数26和27行输入两软件文件绝对路径
//2,预处理，在FileFinder.cpp中的getCommonFileNames函数中做了过滤，只保留后缀为string tmp的文件
//3，deleteComment会把原件中的代码直接改动，记得保存原文件附件。
//4.含有预处理、使用余弦相似度寻找匹配文件、进行基于文本比较的差异分析。
/*
存在问题:1.第50个文件抽取文件名getfilename时报错，可能因为文件过多；
考虑在FileFinders的getfiles中先用文件后缀筛选出需要的文件名，减少files中存放的文件数目。
2.打印文件名有乱码
*/
#include"FileFinder.h"
#include"findStringDifference.h"
#include"CosineSimilarity.h"
#include"deleteComment.h"

extern void getFiles(string path, vector<string>& files);
extern void getFilenames(vector<string>& files, string filenames[NUMBER_MAX]);


int main()
{
	/*
	//测试从路径读取文件内容
	cout << "the content in home1.txt is : " << endl;
	string testpath = "D:\\testfiles1\\home1.txt";//文件内容“abcdefgefg”
	cout<<readFileThroughPath(testpath);
	*/

	//system("chcp 65001");//余弦相似度
	//输入第一份文件夹的绝对路径
	//string filePath1 = "D:\\testfiles1";//在这里输入第一份文件夹的本地绝对路径
	//string filePath2 = "D:\\testfiles2";//在这里输入第二份文件夹的本地绝对路径
	string filePath1 = "D:\\test\\calculator - master";//在这里输入第一份文件夹的本地绝对路径
	string filePath2 = "D:\\test\\calculator-revert-758-Fix757";//在这里输入第二份文件夹的本地绝对路径

	vector<string> Path1;//用于存放文件夹一的需要路径
	vector<string> Path2;//用于存放文件夹二的需要路径
	int numbers = 0;
	FileFinder fileFinder(filePath1, filePath2);
	
	/*
	//全部路径测试
	Path1 = fileFinder.getAllFiles1();
	Path2 = fileFinder.getAllFiles2();
	*/
	
	
	//共同文件测试
	fileFinder.getCommonFilenames(Path1, Path2);
	

	/*
	//未匹配的其他文件测试
	Path1 = fileFinder.getOtherFiles1();
	Path2 = fileFinder.getOtherFiles2();
	*/

	int size1 = Path1.size();
	for (int i = 0; i < size1; i++)
		cout << Path1[i] << endl;
	int size2 = Path2.size();
	for (int j = 0; j < size2; j++)
		cout << Path2[j] << endl;

	for (int m=0;m<fileFinder.getCommonSize();m++){
		//预处理去掉注释
		deleteComment(Path1[m]);
		deleteComment(Path2[m]);
		//读取文件内容
		string a = readFileThroughPath(Path1[m]);
		string b = readFileThroughPath(Path2[m]);//要求输入绝对路径，返回string类型的内容。
		cout << "the content of a and b are : \n"<<"content of a:\n"<<a <<"\n"<<"content of b:\n"<< b<<endl;
		cout << "the "<< m+1 << "th group " << endl;
		cout << "the differences between "<< fileFinder.filenames1[m] << " and " << fileFinder.filenames2[m]<<" is:"<<endl ;
		//寻找差异
		findStringDifference(a, b);
		cout << endl;
	}

	system("pause");
	return 0;
}