#include <iostream>
#include <string>

using namespace std;

void findStringDifference(string a,string b)
{
    int lena=a.size(),lenb=b.size();
    string **f=new string *[lena+1];
    for (int i=0;i<=lena;i++)
        f[i]=new string[lenb+1];
    a="y"+a;
    b="y"+b;
    for (int i=0;i<=lena;i++)
        f[i][0]="";
    for (int j=0;j<=lenb;j++)
        f[0][j]="";
    for (int i=1;i<=lena;i++)
        for (int j=1;j<=lenb;j++)
            if (a[i]==b[j])
                f[i][j]=f[i-1][j-1]+a[i];
            else
            {
                if (f[i][j-1].size()>f[i-1][j].size())
                    f[i][j]=f[i][j-1];
                else
                    f[i][j]=f[i-1][j];
            }
    string ans=f[lena][lenb];
    cout<<"��������У�"<<f[lena][lenb]<<endl;
    cout<<"�仯���£�"<<endl;
    cout<<"ԭ����"<<endl;
    int j=0;
    for (int i=1;i<=lena;i++)
        if (j>=ans.size() || a[i]!=ans[j])
            cout<<"λ��"<<i-1<<"   "<<"ɾȥ"<<a[i]<<endl;
        else
            j++;
    cout<<"�´���"<<endl;
    j=0;
    for (int i=1;i<=lenb;i++)
        if (j>=ans.size() || b[i]!=ans[j])
            cout<<"λ��"<<i-1<<"   "<<"����"<<b[i]<<endl;
        else
            j++;
}
