//FileFinder 内加入Cos ，还需要测试cos是否正确作用
//准备将FileFinder接上Diff
//准备将预处理放在到diff的路上
#include"FileFinder.h"
#include"findStringDifference.h"
#include"CosineSimilarity.h"

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
	string filePath1 = "D:\\testfiles1";//在这里输入第一份文件夹的本地绝对路径
	string filePath2 = "D:\\testfiles2";//在这里输入第二份文件夹的本地绝对路径
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
		string a = readFileThroughPath(Path1[m]);
		string b = readFileThroughPath(Path2[m]);//要求输入绝对路径，返回string类型的内容。
		cout << "the content of a and b are : "<<a << b<<endl;
		cout << "the "<< m+1 << "th group " << endl;
		cout << "the differences between "<< fileFinder.filenames1[m] << " and " << fileFinder.filenames2[m]<<" is:"<<endl ;
		findStringDifference(a, b);
		cout << endl;
	}

	system("pause");
	return 0;
}