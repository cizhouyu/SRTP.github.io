#include <bits/stdc++.h>
#include<io.h>
#include<stdio.h>

using namespace std;

string a[100010];

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

string workfile(string s,int &cnt)
{
    int sum=0;
    string ans="";
    for (int i=0;s[i]!='\0';i++)
    {
        ans+=s[i];
        if (s[i]=='{')
            {
                sum++;
                if (sum==1)
                {
                    int j=i;
                    bool flag=true;
                    while (s[j]!='(')
                    {
                        j--;
                        if (s[j]=='c' && s.substr(j,6)=="class " && j>0 && (s[j-1]==' ' || s[j-1]=='\n'))
                        {
                            flag=false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        int k=j;
                        while (s[k]!='\n') k--;
                        cnt++;
                        a[cnt]=s.substr(k+1,j-1-k);
                        int t=cnt;
                        string st="";
                        while (t>0)
                        {
                            char c=(t%10)+'0';
                            st=c+st;
                            t/=10;
                        }
                    ans=ans+"\n\tfstream out(\"Track.txt\",ios::app);\n\tout<<"+st+"<<endl;";
                    }
                }
            }
        if (s[i]=='}') sum--;
    }
    return ans;
}

void work(string path)
{
    vector<string> f;
    getFiles(path,f);
    int cnt=0;
    for (int i=0;i<f.size();i++)
    {
        char c[100];
        strcpy(c,f[i].c_str());
        fstream in(c,ios::in);
        string s="#include <fstream>\n",st;
        while (getline(in,st))
            s=s+st+"\n";
        fstream out(c,ios::out);
        out<<workfile(s,cnt);
    }
    fstream out("Name.txt",ios::out);
    out<<"����"<<cnt<<"��������\n";
    for (int i=1;i<=cnt;i++)
        out<<i<<" "<<a[i]<<endl;
}

int main()
{
    string path;
    cin>>path;
    work(path);
    return 0;
}
