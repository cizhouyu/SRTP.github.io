#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <io.h>
#include <string>
#include <process.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sys/types.h>
#include<deque>
#include<algorithm>
using namespace std;
#pragma warning(disable:4996)
string& replace_String(string& str, const string& Find, const string& Replace)
{
	while (1) {
		size_t pos(0);
		if ((pos = str.find(Find)) != string::npos)
			str.replace(pos, Find.length(), Replace);
		else break;
	}
	return str;
}
void remove_Comment(char *buffer, size_t size)
{
	char *p, *end, c; //p-动态移动的字符指针，end-指向文件末尾的字符指针，c-存储没一个p指向的字符
	char *sq_start, *dq_start; //sq_start-单引号开始位置（single），dq_start-双引号开始（double）
	char *lc_start, *bc_start; //lc_start-//的开始位置，bc_start-/*的开始位置
	size_t len; //记录某符号结束和开始的位置之差
	p = buffer;
	end = p + size;
	sq_start = dq_start = NULL;
	lc_start = bc_start = NULL;

	while (p < end) /*当指针没有到达文件末尾*/
	{
		c = *p; //用字符变量c存储指针指向的字符

		switch (c) //根据c的值做相应处理
		{
		case '\'': /*处理单引号*/
		{
			if (dq_start || lc_start || bc_start) //当遇到过双引号、//或/*的时候，则不需要再判断'//'的情况了。
			{
				p++;
				continue; //继续下一个，对while而言的
			}
			if (sq_start == NULL) /****如果未遇到单引号****/
			{
				sq_start = p++; //start指向单引号的开始位置，p指向下一个

			}
			else /*如果遇到过单引号，sq_start指向单引号开始位置*/
			{
				len = (p++) - sq_start;

				if (len == 2 && *(sq_start + 1) == '\\')

				{

					/*若遇到 “ '\'' ”这种情况则两个单引号并未匹配，遇到的“'”是“\' ”中的，而不是与sq_start所指向单引号匹配*/
					continue;
				}

				sq_start = NULL; //否则将sq_start置位为NULL

			}
			break;
		}

		case '\"': /*处理双引号*/
		{
			if (sq_start || lc_start || bc_start) //当遇到过单引号、//或/*的时候，则不需要处理
			{
				p++;
				continue;
			}
			if (dq_start == NULL) /*如果没有遇到过双引号*/
			{
				dq_start = p++; //标记遇到了双引号
			}
			else if (*((p++) - 1) == '\\')
			{
				continue;
			}
			dq_start = NULL; //如果双引号中不是//，标记为NULL
		}

		case '/': //斜杠
		{
			if (sq_start || dq_start || lc_start || bc_start) //如果是单引号、双引号、斜杠、/*的后面
			{
				p++;
				continue;
			}
			c = *(p + 1); //否则c取p指向字符的下一个字符
			if (c == '/') //遇到了双斜杠
			{
				lc_start = p; //标记双斜杠的开始
				p += 2; //p指向双斜杠后面的字符
			}
			else if (c == '*') //遇到了/*
			{
				bc_start = p; //标记/*的开始
				p += 2; //p指向/*后面的字符
			}
			else
			{

				p++;
			}
		}

		case '*': //星号，同斜杠，但少了如果遇到/*的情况，因为遇到这种情况后，要判断是不是遇到结束的地方*/了
		{
			if (sq_start || dq_start || lc_start) //如果是单引号、双引号、斜杠、/*的后面
			{
				p++;
				continue;
			}

			if (*(p + 1) != '/') //如果星号后面紧跟的不是斜杠，那么忽略过。
			{
				p++;
				continue;
			}

			p += 2; //否则p指向斜杠后面那个字符。注意下面的清空语句，p指向的那个字符并不会被清除。
			memset(bc_start, ' ', p - bc_start); //清空/* …… */中间的内容包括注释符号本身。
			bc_start = NULL;
			break;
		}

		case '\n': /*换行符，主要处理遇到双斜杠时，需要清除双斜杠到\n的前面的字符*/
		{
			if (lc_start == NULL) //如果还没有遇到双斜杠，那么忽略
			{
				p++;
				continue;

			}

			c = *(p - 1);
			memset(lc_start, ' ', (c == '\r' ? ((p++) - 1) : p++) - lc_start);
			lc_start = NULL;
			break;
		}

		default:
			p++;
			break;
		}
		if (lc_start)
		{
			memset(lc_start, ' ', p - lc_start);
		}
	}
}
bool deleteComment(string file)
{
	int fd, n;
	char buf[500000];
	char * filename = const_cast<char *>(file.c_str());
	fd = open(filename, O_RDONLY); 
	if (fd == -1)
	{
		cout << "文件不存在！";
		return -1;
	}
	n = read(fd, buf, sizeof(buf));
	if (n == -1 || n == 0)
	{
		close(fd);
		cout << "文件读取失败！";
		return -1;
	}
	remove_Comment(buf, n);
	*(buf + n) = '\0';
	string str = buf;
	replace_String(str, "\r\n\r\n", "\r\n");
	replace_String(str, "\n\n", "\n");
	replace_String(str, "  ", " ");
	replace_String(str, " \n", "");
	replace_String(str, " \r\n", "");//去除多余空格、空行
	ofstream fs(filename);
	fs << str;
	close(fd);
	return true;
}
int main()
{
	string r;
	cout << "请输入完整路径";
	cin >> r;
	deleteComment(r);
	cout << "succeeded";
	system("pause");
}