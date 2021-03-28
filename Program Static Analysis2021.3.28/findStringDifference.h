//读入两个string,输出区别
//由文件名读到string（Cos里面有函数）

#pragma once
#include <iostream>
#include <string>

using namespace std;


void findStringDifference(string a, string b)//findStringDifference2.0
{
    int lena = a.size(), lenb = b.size();
    string** f = new string * [lena + 1];
    for (int i = 0; i <= lena; i++)
        f[i] = new string[lenb + 1];
    a = "y" + a;
    b = "y" + b;
    for (int i = 0; i <= lena; i++)
        f[i][0] = "";
    for (int j = 0; j <= lenb; j++)
        f[0][j] = "";
    for (int i = 1; i <= lena; i++)
        for (int j = 1; j <= lenb; j++)
            if (a[i] == b[j])
                f[i][j] = f[i - 1][j - 1] + a[i];
            else
            {
                if (f[i][j - 1].size() > f[i - 1][j].size())
                    f[i][j] = f[i][j - 1];
                else
                    f[i][j] = f[i - 1][j];
            }
    a.erase(0, 1);
    b.erase(0, 1);
    string ans = f[lena][lenb];
    cout << "最长公共序列：" << ans << endl;

    cout << "变化如下：" << endl;
    cout << "原串：" << endl;
    int* head = new int[a.size() + 2];//head[i]记录a中第i行的开头字符的位置
    int cnt = -1;
    int* x = new int[ans.size()];
    int* y = new int[ans.size()];
    //x,y记录ans中每个字符对应a中的行列
    int j = 0, xx = 1, yy = -1;
    head[1] = 0;
    for (int i = 0; i < lena; i++)
    {
        yy++;
        if (a[i] == '\n')
        {
            xx++; yy = -1;
            head[xx] = i + 1;
        }
        if (j < ans.size() && a[i] == ans[j])
        {
            if (ans[j] != '\n')
            {
                cnt++;
                x[cnt] = xx; y[cnt] = yy;
            }
            j++;
        }
    }
    head[xx + 1] = a.size() + 1;
    j = 0;
    for (int i = 1; i <= xx; i++)
    {
        cout << "第" << i << "行：\n";
        if (x[j] != i)
            cout << "删除整行" << endl;
        else
        {
            bool flag = false;
            int k = j;
            while (k < cnt && x[k + 1] == i) k++;
            if (y[j] > 0)
            {
                cout << "位置0：删除" << a.substr(head[i], y[j]) << endl;
                flag = true;
            }
            for (int p = j + 1; p <= k; p++)
                if (y[p] > y[p - 1] + 1)
                {
                    cout << "位置" << y[p - 1] + 1 << "：删除" << a.substr(head[i] + y[p - 1] + 1, y[p] - y[p - 1] - 1) << endl;
                    flag = true;
                }
            if (head[i + 1] - head[i] - 2 > y[k])
            {
                cout << "位置" << y[k] << "：删除" << a.substr(head[i] + y[k] + 1, head[i + 1] - 2 - (head[i] + y[k] + 1) + 1) << endl;
                flag = true;
            }
            if (!flag) cout << "没有改动\n";
            j = k + 1;
        }
    }

    cout << endl << "新串：" << endl;
    int* h = new int[b.size() + 2];//head[i]记录b中第i行的开头字符的位置
    cnt = -1; j = 0; xx = 1; yy = -1; h[1] = 0;
    for (int i = 0; i < lenb; i++)
    {
        yy++;
        if (b[i] == '\n')
        {
            xx++; yy = -1;
            h[xx] = i + 1;
        }
        if (j < ans.size() && b[i] == ans[j])
        {
            if (ans[j] != '\n')
            {
                cnt++;
                x[cnt] = xx; y[cnt] = yy;
            }
            j++;
        }
    }
    h[xx + 1] = b.size() + 1;
    j = 0;
    for (int i = 1; i <= xx; i++)
    {
        cout << "第" << i << "行：\n";
        if (x[j] != i)
            cout << "新增整行：" << b.substr(h[i], h[i + 1] - h[i] - 1) << endl;
        else
        {
            bool flag = false;
            int k = j;
            while (k < cnt && x[k + 1] == i) k++;
            if (y[j] > 0)
            {
                cout << "位置0：新增" << b.substr(h[i], y[j]) << endl;
                flag = true;
            }
            for (int p = j + 1; p <= k; p++)
                if (y[p] > y[p - 1] + 1)
                {
                    cout << "位置" << y[p - 1] + 1 << "：新增" << b.substr(h[i] + y[p - 1] + 1, y[p] - y[p - 1] - 1) << endl;
                    flag = true;
                }
            if (h[i + 1] - h[i] - 2 > y[k])
            {
                cout << "位置" << y[k] << "：新增" << b.substr(h[i] + y[k] + 1, h[i + 1] - 2 - (h[i] + y[k] + 1) + 1) << endl;
                flag = true;
            }
            if (!flag) cout << "没有改动\n";
            j = k + 1;
        }
    }
}


/*void findStringDifference(string a, string b)//findStringDifference1.0
{
    int lena = a.size(), lenb = b.size();
    string** f = new string * [lena + 1];
    for (int i = 0; i <= lena; i++)
        f[i] = new string[lenb + 1];
    a = "y" + a;
    b = "y" + b;
    for (int i = 0; i <= lena; i++)
        f[i][0] = "";
    for (int j = 0; j <= lenb; j++)
        f[0][j] = "";
    for (int i = 1; i <= lena; i++)
        for (int j = 1; j <= lenb; j++)
            if (a[i] == b[j])
                f[i][j] = f[i - 1][j - 1] + a[i];
            else
            {
                if (f[i][j - 1].size() > f[i - 1][j].size())
                    f[i][j] = f[i][j - 1];
                else
                    f[i][j] = f[i - 1][j];
            }
    string ans = f[lena][lenb];
    cout << "最长公共序列：" << f[lena][lenb] << endl;
    cout << "变化如下：" << endl;
    cout << "原串：" << endl;
    int j = 0;
    for (int i = 1; i <= lena; i++)
        if (j >= ans.size() || a[i] != ans[j])
            cout << "位置" << i - 1 << "   " << "删去" << a[i] << endl;
        else
            j++;
    cout << "新串：" << endl;
    j = 0;
    for (int i = 1; i <= lenb; i++)
        if (j >= ans.size() || b[i] != ans[j])
            cout << "位置" << i - 1 << "   " << "增加" << b[i] << endl;
        else
            j++;
}*/
