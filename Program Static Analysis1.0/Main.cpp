//FileFinder �ڼ���Cos ������Ҫ����cos�Ƿ���ȷ����
//׼����FileFinder����Diff
//׼����Ԥ������ڵ�diff��·��
#include"FileFinder.h"
#include"findStringDifference.h"
#include"CosineSimilarity.h"

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
	string filePath1 = "D:\\testfiles1";//�����������һ���ļ��еı��ؾ���·��
	string filePath2 = "D:\\testfiles2";//����������ڶ����ļ��еı��ؾ���·��
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
		string a = readFileThroughPath(Path1[m]);
		string b = readFileThroughPath(Path2[m]);//Ҫ���������·��������string���͵����ݡ�
		cout << "the content of a and b are : "<<a << b<<endl;
		cout << "the "<< m+1 << "th group " << endl;
		cout << "the differences between "<< fileFinder.filenames1[m] << " and " << fileFinder.filenames2[m]<<" is:"<<endl ;
		findStringDifference(a, b);
		cout << endl;
	}

	system("pause");
	return 0;
}