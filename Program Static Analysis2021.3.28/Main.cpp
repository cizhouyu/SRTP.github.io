//˵����
//1,��ƥ���ļ�����main����26��27������������ļ�����·��
//2,Ԥ������FileFinder.cpp�е�getCommonFileNames���������˹��ˣ�ֻ������׺Ϊstring tmp���ļ�
//3��deleteComment���ԭ���еĴ���ֱ�ӸĶ����ǵñ���ԭ�ļ�������
//4.����Ԥ����ʹ���������ƶ�Ѱ��ƥ���ļ������л����ı��ȽϵĲ��������
/*
��������:1.��50���ļ���ȡ�ļ���getfilenameʱ����������Ϊ�ļ����ࣻ
������FileFinders��getfiles�������ļ���׺ɸѡ����Ҫ���ļ���������files�д�ŵ��ļ���Ŀ��
2.��ӡ�ļ���������
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
	//���Դ�·����ȡ�ļ�����
	cout << "the content in home1.txt is : " << endl;
	string testpath = "D:\\testfiles1\\home1.txt";//�ļ����ݡ�abcdefgefg��
	cout<<readFileThroughPath(testpath);
	*/

	//system("chcp 65001");//�������ƶ�
	//�����һ���ļ��еľ���·��
	//string filePath1 = "D:\\testfiles1";//�����������һ���ļ��еı��ؾ���·��
	//string filePath2 = "D:\\testfiles2";//����������ڶ����ļ��еı��ؾ���·��
	string filePath1 = "D:\\test\\calculator - master";//�����������һ���ļ��еı��ؾ���·��
	string filePath2 = "D:\\test\\calculator-revert-758-Fix757";//����������ڶ����ļ��еı��ؾ���·��

	vector<string> Path1;//���ڴ���ļ���һ����Ҫ·��
	vector<string> Path2;//���ڴ���ļ��ж�����Ҫ·��
	int numbers = 0;
	FileFinder fileFinder(filePath1, filePath2);
	
	/*
	//ȫ��·������
	Path1 = fileFinder.getAllFiles1();
	Path2 = fileFinder.getAllFiles2();
	*/
	
	
	//��ͬ�ļ�����
	fileFinder.getCommonFilenames(Path1, Path2);
	

	/*
	//δƥ��������ļ�����
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
		//Ԥ����ȥ��ע��
		deleteComment(Path1[m]);
		deleteComment(Path2[m]);
		//��ȡ�ļ�����
		string a = readFileThroughPath(Path1[m]);
		string b = readFileThroughPath(Path2[m]);//Ҫ���������·��������string���͵����ݡ�
		cout << "the content of a and b are : \n"<<"content of a:\n"<<a <<"\n"<<"content of b:\n"<< b<<endl;
		cout << "the "<< m+1 << "th group " << endl;
		cout << "the differences between "<< fileFinder.filenames1[m] << " and " << fileFinder.filenames2[m]<<" is:"<<endl ;
		//Ѱ�Ҳ���
		findStringDifference(a, b);
		cout << endl;
	}

	system("pause");
	return 0;
}