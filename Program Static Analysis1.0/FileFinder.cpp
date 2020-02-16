#include"FileFinder.h"
#include"CosineSimilarity.h"
// ���ļ��л�ȡ�����ļ��ľ���·����path���ļ��о���·����files�Ǵ洢�ļ����������ļ��ľ���·��������
void getFiles(string path, vector<string>& files);
//�Ӿ���·������ļ���
void getFilenames(vector<string>& files, string filenames[NUMBER_MAX]);

FileFinder::FileFinder(string filepath1, string filepath2)
{
	getFiles(filepath1, allFiles1);
	size1 = allFiles1.size();
	getFiles(filepath2, allFiles2);
	size2 = allFiles2.size();

	//��files1����ȡ���ļ���������string����filenames1[NUMBER_MAX]
	getFilenames(allFiles1, filenames1);

	//��files2����ȡ���ļ���������string����filenames2[NUMBER_MAX]
	getFilenames(allFiles2, filenames2);

}

vector<string>& FileFinder::getAllFiles1()
{
	return allFiles1;
}

vector<string>& FileFinder::getAllFiles2()
{
	return allFiles2;
}


void FileFinder::getCommonFilenames(vector<string>& common1, vector<string>& common2)
{
	int t1 = 0;//t1��¼��������ͬ���ļ���������0��ʼ

	for (int j = 0; j < size1; j++)
	{
		for (int m = 0; m < size2; m++)
		{
			if (filenames1[j] == filenames2[m] || ( compare(filenames1[j], filenames2[m] )>= 0.94))
			{
				common1.push_back(allFiles1[j]);
				common2.push_back(allFiles2[m]);
				sign1[t1] = j;
				sign2[t1] = m;
				t1++;
			}
		}
	}
	commonFiles1 = common1;
	commonFiles2 = common2;
	commonSize = t1;
}

vector<string>& FileFinder::getOtherFiles1()
{
	int k = 0;//��ͬ������������
	int i;
	vector<string>common1, common2;
	getCommonFilenames(common1, common2);

	for (i = 0; i < size1; i++)
	{
		if (k == commonSize)
			break;
		if (i == sign1[k])
		{
			k++;
			continue;
		}
		otherFiles1.push_back(allFiles1[i]);
	}
	for (int j = i; j < size1; j++)
		otherFiles1.push_back(allFiles1[j]);
	return otherFiles1;
}

vector<string>& FileFinder::getOtherFiles2()
{
	int k = 0;//��ͬ������������
	int i;
	vector<string>common1, common2;
	getCommonFilenames(common1, common2);

	for (i = 0; i < size2; i++)
	{
		if (k == commonSize)
			break;
		if (i == sign2[k])
		{
			k++;
			continue;
		}
		otherFiles2.push_back(allFiles2[i]);
	}
	for (int j = i; j < size2; j++)
		otherFiles2.push_back(allFiles2[j]);
	return otherFiles2;
}

int FileFinder::getNumberOfCommonFiles()
{
	vector<string>common1, common2;
	getCommonFilenames(common1, common2);
	return commonSize;
}

void getFiles(string path, vector<string>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

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

int FileFinder::getCommonSize()
{ 
	return commonSize; 
};