#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
#include<set>
#include<cstdio>
#include<iomanip>
#include<map>
using namespace std;
const vector<int>::size_type max_student_num = 2;
int welcome()
{
	set<int> modestd = { 0,1,2,3,4,5,6,7 };
	cout << "          =========================================" << endl;
	cout << "          =          欢迎使用成绩管理系统         =" << endl;
	cout << "          =       1=录入学生     2=显示信息       =" << endl;
	cout << "          =       3=排序总评     4=查找学生       =" << endl;
	cout << "          =       5=插入学生     6=删除学生       =" << endl;
	cout << "          =       7=统计人数     0=退出           =" << endl;
	cout << "          =========================================" << endl;
	cout << "请选择：";
	int mode;
	cin >> mode;
	while (modestd.find(mode) == modestd.end())
	{
		cout << "输入非法，请重新输入！" << endl;
		welcome();
		cin >> mode;
	}
	return mode;
}
struct student
{
	student() = default;
	double usualscore;
	string name;
	int num;
	double finalscore;
	double sum;
};
vector<student> aaa;
map<int, student> ppp;
set<int> lll;
int mode1()
{
	if (aaa.size() >= max_student_num)
	{
		cout << "人数上限已达到" << max_student_num << "人上限，无法再输入！" << endl;
		return 0;
	}
	student tem;
	int tem2;
	cout << "请输入学号（1-40）之间：";
	cin >> tem2;
	while (tem2>40||tem2<0||(lll.find(tem2)!=lll.end()))
	{
		if (tem2 > 40 || tem2 < 0)
		{
			cout << "输入学号非法！请重新输入！" << endl;
			cout << "请输入学号（1-40）之间：";
		}
		else
			cout << "学号不允许重复，该学号已经存在！" << endl<<"请输入学号（1-40）之间:";
		cin >> tem2;
	}
	tem.num = tem2;
	cout << "请输入姓名：";
	cin >> tem.name;
	cout << "请输入平时成绩（0~100)：";
	cin >> tem2;
	while (tem2 > 100 || tem2 < 0)
	{
		cout << "输入错误，成绩应该在0到100之间！" << endl;
		cout << "请输入平时成绩（0~100)：";
		cin >> tem2;
	}
	tem.usualscore = tem2;
	cout << "请输入期末考试成绩（0~100)：";
	cin >> tem2;
	while (tem2 > 100 || tem2 < 0)
	{
		cout << "输入错误，成绩应该在0到100之间！" << endl;
		cout << "请输入期末考试成绩（0~100)：";
		cin >> tem2;
	}
	tem.finalscore = tem2;
	tem.sum = tem.finalscore/2 + tem.usualscore/2;
	aaa.push_back(tem);
	ppp[tem.num] = tem;
	lll.insert(tem.num);
	cout << "继续输入学生数据请按y或Y：";
	char tem3;
	cin >> tem3;
	if (tem3 == 'y' || tem3 == 'Y')
	{
		mode1();
	}
	return 0;
}
int mode2()
{
	if (!aaa.size()){cout << "没有学生信息！" << endl;return 0;}
	cout << "      学号           姓名           平时           期末           总评" << endl;
	for (auto c : aaa)
	{
		printf("%10d", c.num);
		cout << setw(15) << c.name;
		printf("%15.1f", c.usualscore);
		printf("%15.1f", c.finalscore);
		printf("%15.1f", c.sum);
		cout << endl;
	}
	return 0;
}
int mode3()
{
	sort(aaa.begin(), aaa.end(), [=](student a, student b) {return a.sum > b.sum;});
	if (!aaa.size()) { cout << "没有学生信息！" << endl;return 0; }
	cout << "      学号           姓名           平时           期末           总评" << endl;
	for (auto c : aaa)
	{
		printf("%10d", c.num);
		cout << setw(15)<< c.name;
		printf("%15.1f", c.usualscore);
		printf("%15.1f", c.finalscore);
		printf("%15.1f", c.sum);
		cout << endl;
	}
	return 0;
}
int mode4()
{
	cout << "请输入您要查找的学号：";
	int tem1;cin >> tem1;
	if (lll.find(tem1)!=lll.end())
	{
		cout << "      学号           姓名           平时           期末           总评" << endl;
		printf("%10d", ppp[tem1].num);
		cout << setw(15) << ppp[tem1].name;
		printf("%15.1f", ppp[tem1].usualscore);
		printf("%15.1f", ppp[tem1].finalscore);
		printf("%15.1f", ppp[tem1].sum);
		cout << endl;
	}
	else cout << "没有该学号学生信息！"<<endl;
	return 0;
}
int mode7()
{
	cout << "    100~90   89~80   79~70   69~60    <60" << endl;
	int a[5] = { 0,0,0,0,0 };
	for (auto c : aaa)
	{
		if (c.sum >= 90)++a[0];
		else if (c.sum >= 80) ++a[1];
		else if (c.sum >= 70)++a[2];
		else if (c.sum >= 60)++a[3];
		else ++a[4];
	}
	for (auto c : a)
		cout << setw(8) << c;
	cout << endl;
	return 0;
}
int mode6()
{
	cout << "请输入要删除学生的学号：";
	int n;
	cin >> n;
	if(lll.find(n)==lll.end())
	{
		cout << "没有该学号学生！" << endl;
		return 0;
	}
	else
	{
		lll.erase(n);
		for (auto c = aaa.begin();c != aaa.end();)
		{
			if (c->num == n) { aaa.erase(c);break; }
		}
		cout << n << "号学生信息删除成功！" << endl;
	}
	return 0;
}
int main()
{
	vector<student>	aaa;
	int mode = welcome();
	char choice;
	while (mode != 0)
	{
		if (mode == 1)
		{
			cout << "您选择了1=录入学生" << endl;
			mode1();
		}
		else if (mode == 2) {
			cout << "您选择了2=显示信息" << endl;
			mode2();
		}
		else if (mode == 5)
		{
			cout << "您选择了5=插入学生" << endl;
			mode1();
		}
		else if (mode == 3)
		{
			cout << "您选择了3=排序总评" << endl;
			mode3();
		}
		else if (mode == 4)
		{
			cout << "您选择了4=查找学生" << endl;
			mode4();
			cout << "继续查找请按y或Y：";
			cin >> choice;
			while (choice == 'y' || choice == 'Y')
			{
				mode4();
				cout << "继续查找请按y或Y：";
				cin >> choice;
			}
		}
		else if (mode == 7)
			mode7();
		else if (mode == 6)
		{
			mode6();
			char choice2;
			cout << " 继续删除其他学生请按y或Y：";
			cin >> choice2;
			while (choice2 == 'y' || choice2 == 'Y')
			{
				mode6();
				cout << " 继续删除其他学生请按y或Y：";
				cin >> choice2;
			}
		}
		mode = welcome();
		}
	return 0;
	}