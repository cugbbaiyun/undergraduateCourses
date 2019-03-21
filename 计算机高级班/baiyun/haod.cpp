#include <iostream>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include <fstream>

// 密码部分 

int chcode() 
{
    char pw[50],ch;
    char *syspw = "123456"; // 原始密码
    int i,m = 0;
    printf("请输入密码:");
    while(m < 3)
	 {
        i = 0;
        while((ch = _getch()) != '\r') {
            if(ch == '\b' && i > 0) {
                printf("\b \b");
                --i;
            }
            else if(ch != '\b') {
                pw[i++] = ch;
                printf("*");
            }
        }
        pw[i] = '\0';
        printf("\n");
        if(strcmp(pw,syspw) != 0) {
            printf("密码错误，请重新输入!\n");
            m++;
        }
        else {
            printf("密码正确！\n");
            return 1;
        }
    }
    printf("连续3次输入错误，退出!\n");
    system("pause");
    return 0;
}

using namespace std;
class Student
{
	public:
		void menu();                                   //菜单
		Student* Input(Student stu[],int &num);        //录入学生 
		void Output(Student stu[],int &num);           //显示信息 
		void Order(Student stu[],int &num);            //排序总评 
		void Search(Student stu[],int &num);           //查找学生
		Student* Insert(Student stu[],int &num);       //插入学生 
		void Delete(Student stu[],int &num);           //删除学生 
		void Statis(Student stu[],int &num);           //统计人数 
		void inputId();                                //输入学号 
		void inputName();                              //输入姓名 
		void inputRegularGrade();                      //输入平时成绩 
		void inputFinalExam();                         //输入期末考试成绩 
		int getId();                                   //获得学号 
	
	
		double CalTotalMark();                         //计算总评成绩 
	private:
		int id;                                        //学号 
		char name[20];                                 //姓名 
		double regularGrade;                           //平时成绩 
		double finalExam;                              //期末考试成绩
};

using namespace std;



void Student::inputId()
{
	do
	{
		cout<<"请输入学号（1-40）";
		cin>>id;
		if(id<1||id>40)
		{
			cout<<"输入错误！学号应该在1-40之间";
			cin>>id; 
		}
		else
		break;
		
	}
	while(1);
}

void Student::inputName()
{
	cout<<"请输入姓名：";
	cin>>name;
}

void Student::inputRegularGrade()
{
	do
	{
		cout<<"请输入平时成绩（0-100）：";
		cin>>regularGrade;
		if(regularGrade<0||regularGrade>100)
		{
			cout<<"输入有误！成绩应该在0-100之间";
			cin>>regularGrade;
		}
		else
		break;
	}
	while(1); 
}

void Student::inputFinalExam()
{
	do
	{
		cout<<"请输入期末成绩（0-100）：";
		cin>>finalExam;
		if(finalExam<0||finalExam>100)
		{
			cout<<"输入有误！成绩应该在0-100之间";
			cin>>finalExam;
		}
		else
		break;
	}
	while(1);
}

int Student::getId()
{
	return id;
}

double Student::CalTotalMark()
{
		return regularGrade*0.5+finalExam*0.5;
}

void Student::menu()                   //菜单 
{
          cout<<"========================================="<<endl;
          cout<<"=          欢迎使用成绩管理系统         ="<<endl;
          cout<<"=       1=录入学生     2=显示信息       ="<<endl;
          cout<<"=       3=排序总评     4=查找学生       ="<<endl;
          cout<<"=       5=插入学生     6=删除学生       ="<<endl;
          cout<<"=       7=统计人数     0=退出           ="<<endl;
          cout<<"========================================="<<endl;
}

Student* Student::Input(Student stu[],int &num)                        //录入学生
{
	
	int x=0;
	int i=0;
	char c;
	do{
	
       	while(1)                                                     //判断学号 是否重复 
		{
			stu[num].inputId();
			for(i=0;i<num;i++)
				if(stu[num].getId()==stu[i].getId())
					break;
			
			if(i>=num)
				break;
				
			else
				cout<<"学号不允许重复，该学号已经存在！"<<endl; 
				
		}
		stu[num].inputName();
		stu[num].inputRegularGrade();
		stu[num].inputFinalExam();
		num++;
		cout<<"继续输入学生数据请按y或Y：";
		cin>>c;
	
}
while(c=='y'||c=='Y');
return stu;
}

void Student::Output(Student stu[],int &num)        //显示信息 
{
	int i=0;
	cout<<setw(10)<<"学号"<<setw(10)<<"姓名"<<setw(10)<<"平时"<<setw(10)<<"期末"<<endl; 
	for(i=0;i<num;i++)
		cout<<setw(10)<<id<<setw(10)<<name<<setw(10)<<regularGrade<<setw(10)<<finalExam<<endl;
	    cout<<endl;
}

void Student::Order(Student stu[],int &num)       //排序总评
{
	Student t;
	int i, j;
	for(i=0;i<num;i++)
		for(j=i+1;j<num;j++)
			if(stu[i].CalTotalMark()<stu[j].CalTotalMark())
			{
				t = stu[i];
				stu[i] = stu[j]; 
				stu[j] = t;
			}
	Output(stu,num);
}

void Student::Search(Student stu[],int &num)        //查找学生 
{
	char c;
	int i=0, idd;
	
	do
	{
		cout<<"请输入您要查找的学号：";
		cin>>idd;
		for(i=0;i<num;i++)
			if(idd==stu[i].getId())
			{
					cout<<setw(10)<<"学号"<<setw(10)<<"姓名"<<setw(10)<<"平时成绩"<<setw(10)<<"期末成绩"; 
				cout<<setw(10)<<id<<setw(10)<<name<<setw(10)<<regularGrade<<setw(10)<<finalExam<<endl;
			
				break;
			}
		if(i>=num)
			cout<<"没有该学号学生信息！"<<endl;
		cout<<"继续查找请按y或Y：";
		cin>>c;
	}
	while(c=='y'||c=='Y');
		
}

Student* Student::Insert(Student stu[],int &num)     //插入学生
{
    Student t;
	char c;
	int i=0, j;
	
	do
	{
		
		cout<<"您将增加学生信息"<<endl;
		stu[num].inputId();
		for(i=0;i<num;i++)
			if(stu[i].getId()==stu[num].getId())
			{
				cout<<"该学号已存在！"<<endl;
				break;
			}	
		if(i>=num)
		{
			stu[num].inputName();
			stu[num].inputRegularGrade();
			stu[num].inputFinalExam();
			for(i=0;i<num+1;i++)
			{
				
				for(j=i+1;j<num+1;j++)
					if(stu[j].getId()<stu[i].getId())
					{
						t = stu[i];
						stu[i] = stu[j]; 
						stu[j] = t;
					}
			}
			num++;
		}
			
		cout<<"继续添加请按y或Y：";
		cin>>c;
	}
	while(c=='y'||c=='Y');

	return stu;
}

void Student::Delete(Student stu[],int &num)                             //删除学生
{
	char c;
	int i=0, j, idd;
	do
	{
		cout<<"请输入要删除学生的学号：";
		cin>>idd;
		for(i=0;i<num;i++)
			if(idd==stu[i].getId())
			{
				for(j=i;j<num;j++)
					stu[j] = stu[j+1];
				
				break;
			}
		if(i>=num)
			cout<<"没有该学号学生！"<<endl;
		num--;	
		cout<<"继续删除请按y或Y：";
		cin>>c;
	}
	while(c=='y'||c=='Y');

}

void Student::Statis(Student stu[],int &num)                 //统计人数 
{
	int a=0, b=0, c=0, d=0, e=0;
	for(int i=0;i<num;i++)
		if(stu[i].CalTotalMark()<60)
			a++;
		else if(stu[i].CalTotalMark()<70)
			b++;
		else if(stu[i].CalTotalMark()<80)
			c++;
		else if(stu[i].CalTotalMark()<90)
			d++;
		else
			e++;
	cout<<" "<<"100~90"<<" "<<"89~80"<<" "<<"79~70"<<" "<<"69~60"<<" "<<"<60"<<endl;
	cout<<" "<<e<<" "<<d<<" "<<c<<" "<<b<<" "<<a;
}

int main()
{
      if(chcode())
            printf("登录成功!\n");
      else
      {
            printf("登录失败!\n");
            return 0;
      }
    Student s1, *stu;
    int currentN=0;
    int s;
    int n=0;
   
		
		ifstream filein("student dat",ios::binary);
		if(filein)
		{
			filein.read((char*)&currentN,sizeof(currentN)) ;
			for(int i=0;i<currentN;i++)
			filein.read((char*)&(stu[i]),sizeof(stu[i])); 
		}
		filein.close();
		
		while(s)
		{
			s1.menu();
			cout<<"请选择：";
			cin>>s;
		    if(s==1)
		    {
		    	s1.Input(stu,n);
			}
			if(s==2)
			{
			     s1.Output(stu,n);
			}
			if(s==3)
			{
				s1.Order(stu,n);
			}
			if(s==4)
			{
				s1.Search(stu,n);
			}
			if(s==5)
			{
				s1.Insert(stu,n) ;
			}
			if(s==6)
			{
				s1.Delete(stu,n);
			}
			if(s==7)
			{
				s1.Statis(stu,n);
			}
			if(s==0)
			{
				ofstream fileout("student dat",ios::binary);
              if(!fileout)
           {
         	cout<<"文件不能被打开";
        	return 0;
	          }
	            fileout.write((char*)&currentN,sizeof(currentN));
	                for(int i=0;i<currentN;i++)
	                  fileout.write((char*)&(stu[i]),sizeof(stu[i]));
	                	fileout.close();
	                    	return 0; 
			}
			ofstream fileout("student dat",ios::binary);
	            fileout.write((char*)&currentN,sizeof(currentN));
	            for(int i=0;i<currentN;i++)
	            fileout.write((char*)&(stu[i]),sizeof(stu[i]));
		        fileout.close();
	
		}
  }
