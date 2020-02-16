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
	char *p, *end, c; //p-��̬�ƶ����ַ�ָ�룬end-ָ���ļ�ĩβ���ַ�ָ�룬c-�洢ûһ��pָ����ַ�
	char *sq_start, *dq_start; //sq_start-�����ſ�ʼλ�ã�single����dq_start-˫���ſ�ʼ��double��
	char *lc_start, *bc_start; //lc_start-//�Ŀ�ʼλ�ã�bc_start-/*�Ŀ�ʼλ��
	size_t len; //��¼ĳ���Ž����Ϳ�ʼ��λ��֮��
	p = buffer;
	end = p + size;
	sq_start = dq_start = NULL;
	lc_start = bc_start = NULL;

	while (p < end) /*��ָ��û�е����ļ�ĩβ*/
	{
		c = *p; //���ַ�����c�洢ָ��ָ����ַ�

		switch (c) //����c��ֵ����Ӧ����
		{
		case '\'': /*��������*/
		{
			if (dq_start || lc_start || bc_start) //��������˫���š�//��/*��ʱ������Ҫ���ж�'//'������ˡ�
			{
				p++;
				continue; //������һ������while���Ե�
			}
			if (sq_start == NULL) /****���δ����������****/
			{
				sq_start = p++; //startָ�����ŵĿ�ʼλ�ã�pָ����һ��

			}
			else /*��������������ţ�sq_startָ�����ſ�ʼλ��*/
			{
				len = (p++) - sq_start;

				if (len == 2 && *(sq_start + 1) == '\\')

				{

					/*������ �� '\'' ��������������������Ų�δƥ�䣬�����ġ�'���ǡ�\' ���еģ���������sq_start��ָ������ƥ��*/
					continue;
				}

				sq_start = NULL; //����sq_start��λΪNULL

			}
			break;
		}

		case '\"': /*����˫����*/
		{
			if (sq_start || lc_start || bc_start) //�������������š�//��/*��ʱ������Ҫ����
			{
				p++;
				continue;
			}
			if (dq_start == NULL) /*���û��������˫����*/
			{
				dq_start = p++; //���������˫����
			}
			else if (*((p++) - 1) == '\\')
			{
				continue;
			}
			dq_start = NULL; //���˫�����в���//�����ΪNULL
		}

		case '/': //б��
		{
			if (sq_start || dq_start || lc_start || bc_start) //����ǵ����š�˫���š�б�ܡ�/*�ĺ���
			{
				p++;
				continue;
			}
			c = *(p + 1); //����cȡpָ���ַ�����һ���ַ�
			if (c == '/') //������˫б��
			{
				lc_start = p; //���˫б�ܵĿ�ʼ
				p += 2; //pָ��˫б�ܺ�����ַ�
			}
			else if (c == '*') //������/*
			{
				bc_start = p; //���/*�Ŀ�ʼ
				p += 2; //pָ��/*������ַ�
			}
			else
			{

				p++;
			}
		}

		case '*': //�Ǻţ�ͬб�ܣ��������������/*���������Ϊ�������������Ҫ�ж��ǲ������������ĵط�*/��
		{
			if (sq_start || dq_start || lc_start) //����ǵ����š�˫���š�б�ܡ�/*�ĺ���
			{
				p++;
				continue;
			}

			if (*(p + 1) != '/') //����Ǻź�������Ĳ���б�ܣ���ô���Թ���
			{
				p++;
				continue;
			}

			p += 2; //����pָ��б�ܺ����Ǹ��ַ���ע������������䣬pָ����Ǹ��ַ������ᱻ�����
			memset(bc_start, ' ', p - bc_start); //���/* ���� */�м�����ݰ���ע�ͷ��ű���
			bc_start = NULL;
			break;
		}

		case '\n': /*���з�����Ҫ��������˫б��ʱ����Ҫ���˫б�ܵ�\n��ǰ����ַ�*/
		{
			if (lc_start == NULL) //�����û������˫б�ܣ���ô����
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
		cout << "�ļ������ڣ�";
		return -1;
	}
	n = read(fd, buf, sizeof(buf));
	if (n == -1 || n == 0)
	{
		close(fd);
		cout << "�ļ���ȡʧ�ܣ�";
		return -1;
	}
	remove_Comment(buf, n);
	*(buf + n) = '\0';
	string str = buf;
	replace_String(str, "\r\n\r\n", "\r\n");
	replace_String(str, "\n\n", "\n");
	replace_String(str, "  ", " ");
	replace_String(str, " \n", "");
	replace_String(str, " \r\n", "");//ȥ������ո񡢿���
	ofstream fs(filename);
	fs << str;
	close(fd);
	return true;
}
int main()
{
	string r;
	cout << "����������·��";
	cin >> r;
	deleteComment(r);
	cout << "succeeded";
	system("pause");
}