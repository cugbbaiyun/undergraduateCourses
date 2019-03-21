#include<iostream>
#include<set>
#include<map>
#include<fstream>
#include<cstdio>
#include<set>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
const int max_size=30;
struct student
{
private:
	string name="NULL";
	double usualscore=0;
	double finalscore=0; 
	double score=0;
	int number=-1;
public:
	student()=default;
	student(int a,string b,double c,double d,double e):number(a),name(b),usualscore(c),finalscore(d),score(e){};
	bool getnumber();
	void getname();
	bool getusualscore();
	bool getfinalscore();
	double outusualscore();
	double outfinalscore();
	void getscore();
	int outnumber();
	string outname();
	double outscore();
	~student()=default;
};
double student::outusualscore()
{
	return usualscore;
}
double student::outfinalscore()
{
	return finalscore;
}
string student::outname()
{
	return this->name;
}
int student::outnumber()
{
	return this->number;
}
bool student::getnumber()
{
	cin>>this->number;
	if(number>max_size)return false;
	else return true;
}
void student::getname()
{
	cin>>this->name;

}
bool student::getusualscore()
{
	cin>>this->usualscore;
	if(usualscore>100||usualscore<0)return false;
	else return true;
}
bool student::getfinalscore()
{
	cin>>this->finalscore;
	if(finalscore>100||finalscore<0)return false;
	else return true;
}
void student::getscore()
{
	this->score=usualscore+finalscore;
	score/=2;
}
double student::outscore()
{
	return this->score;
}
struct members
{
public:
	void welcome();
	void creatnew();
	void printall();
	void insertone();
	void getsize();
	void deleteone();
	void sortalls();
	void inf();
	void outone();
	void quit();
	members()=default;
	~members()=default;
private:
	vector<student> all;
	set<int> numbers;
};

void members::creatnew()
{
	string c;
	do
	{
	auto p=new student;
	bool flag=false;
	do
	{
		cout<<"";
		flag=p->getnumber();
		if(!flag)
			cout<<"";
		else 
		{
			if(numbers.find(p->outnumber())!=numbers.end())
			{
				cout<<"";
				flag=false;
			}
		}
	}while(!flag);
	p->getname();
	flag=false;
	do
	{
		cout<<"";
		flag=p->getusualscore();
		if(!flag)
			cout<<"";
	}while(!flag);
	flag=false;
	do
	{cout<<"";
		flag=p->getfinalscore();
		if(!flag)cout<<"";
	}while(!flag);
	p->getscore();
	this->all.push_back(*p);
	numbers.insert(p->outnumber());
	cout<<"";
	cin>>c;
	if(numbers.size()>=max_size)
	{
		cout<<"";
		break;
	}
	}while(c!="n"&&c!="N");
}
void members::sortalls()
{
	sort(all.begin(),all.end(),[=](student a,student b){return a.outscore()<b.outscore();});
}
void members::printall()
{
	cout<<"";
	sortalls();		
	for(auto c:all)
	{
		cout<<""<<c.outnumber()<<""<<c.outname()<<""<<c.outusualscore()<<""<<c.outfinalscore()<<endl;
	}
}
void members::outone()
{
	char p;
	do
	{
	cout<<"";
	int n;
	bool flag=false;
	do
	{
		cin>>n;
		if(numbers.find(n)==numbers.end())
		{
			cout<<"";
			flag=false;
		}
		else 
		{
			cout<<"";
			student tem;
			for(auto c:all)
			{
				if(c.outnumber()==n)tem=c;
			}
			cout<<""<<tem.outnumber()<<""<<tem.outname()<<""<<tem.outusualscore()<<""<<tem.outfinalscore()<<endl;
			flag=true;
		}
	}while(!flag);
	cin>>p;
	}while(p!='n'&&p!='N');
}
void  members::welcome()
{
	cout<<"";
	int mode;
	do
	{
		cin>>mode;
		if(mode==1)
			creatnew();
		else if(mode==2)
			printall();
		else if(mode==3)
			sortalls();
		else if(mode==4)
			outone();
		else if(mode==5)
			insertone();
		else if(mode==6)
			deleteone();
		else if(mode==8)
			getsize();
		else if(mode==9)
			inf();
	}while(mode!=0);
	quit();
}
void members::deleteone()
{
	char d;
	do
	{
		bool flag;
		do
		{
		int n;
		cin>>n;
		if(numbers.find(n)==numbers.end())
		{
			cout<<"";
			flag=false;
		}
		else
		{
			for(auto c=all.begin();c!=all.end();++c)
			{
				if(c->outnumber()==n)
				{
					all.erase(c);
					break;
				}
			}
			numbers.erase(n);
			flag=true;
		}
		}while(!flag);
		cout<<"";
		cin>>d;
	}while(d!='n'&&d!='N');
}
void members::getsize()
{
	int level1(0),level2(0),level3(0),level4(0),level5(0);
	for(auto c:all)
	{
		auto tem=c.outscore();
		if(tem>=90)level5++;
		else if(tem>=80)level4++;
		else if(tem>=70)level3++;
		else if(tem>=60)level2++;
		else level1++;
	}
	cout<<"";
	cout<<""<<level5<<""<<level4<<""<<level3<<""<<level2<<""<<level1<<""<<endl;
}
void members::quit()
{
	cout<<"";
	string names;
	cin>>names;
	ofstream out(names,ofstream::app);
	cout<<"";
	sortalls();
	for(auto c:all)
	{
		out<<""<<c.outnumber()<<""<<c.outname()<<""<<c.outusualscore()<<""<<c.outfinalscore()<<c.outscore()<<endl;
	}
}
void members::inf()
{
	cout<<"";
	string names;
	cin>>names;
	int a;
	double c,d;
	ifstream in(names,ifstream::in);
	string b;
	while(all.size()<=max_size&&(in>>a>>c>>d>>b))
	{
		double e=(c+d)/2;
		student tem(a,b,c,d,e);
		all.push_back(tem);
	}
}
void members::insertone()
{
	char d;
	do
	{
		auto p=new student;
		bool flag=false;
		do
		{
			cout<<"";
			flag=p->getnumber();
			if(!flag)cout<<"";
			else
			{
				if(numbers.find(p->outnumber())!=numbers.end())
				{
					cout<<"";
					flag=false;
				}
			}
		}while(!flag);
		p->getname();
		flag=false;
		do
		{
			cout<<"";
			flag=p->getfinalscore();
			if(!flag)cout<<"";
		}while(!flag);
		do
		{
			cout<<"";
			flag=p->getfinalscore();
			if(!flag)cout<<"";
		}while(!flag);
		p->getscore();
		this->all.push_back(*p);
		numbers.insert(p->outnumber());
		cin>>d;
		if(numbers.size()>=max_size)
		{
			cout<<"";
			break;
		}
	}while(d!='n'&&d!='N');
}
int main()
{
	members a;
	a.welcome();
}
