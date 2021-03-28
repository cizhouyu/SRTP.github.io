#include"CosineSimilarity.h"

bool word_segment_(const std::string& substr)
{
	return true;
}


float compare(const std::string& ref1, const std::string& ref2)
{
	std::map<std::string, std::pair<size_t, size_t>> container;

	for (size_t i = 0, start = 0; i < ref1.length(); ++i)
	{
		std::string substr = ref1.substr(start, i - start + 1);
		if (word_segment_(substr))
		{
			++container[substr].first;
			start = i + 1;
		}
	}

	for (size_t i = 0, start = 0; i < ref2.length(); ++i)
	{
		std::string substr = ref2.substr(start, i - start + 1);
		if (word_segment_(substr))
		{
			++container[substr].second;
			start = i + 1;
		}
	}

	unsigned long product = 0;
	unsigned long modulo1 = 0;
	unsigned long modulo2 = 0;

	for (std::map<std::string, std::pair<size_t, size_t>>::const_iterator it = container.begin(); it != container.end(); ++it)
	{
		const std::pair<size_t, size_t>& cnt = it->second;
		product += cnt.first * cnt.second;
		modulo1 += cnt.first * cnt.first;
		modulo2 += cnt.second * cnt.second;
	}

	return product / (std::sqrt(static_cast<float>(modulo1))* std::sqrt(static_cast<float>(modulo2)));
}


//从文件读入到string里
string readFileIntoString(string filename)
{
	ifstream ifile(filename);
	//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}

string readFileThroughPath(string path)
{
	string filepath = path ;
	fstream fin;
	fin.open(filepath.c_str(), ios::in);

	ostringstream buf2;
	char ch;
	while (buf2 && fin.get(ch))
	{
		buf2.put(ch);
		//cout << ch;//测试输出
	}
	//返回与流对象buf关联的字符串
	return buf2.str();

}