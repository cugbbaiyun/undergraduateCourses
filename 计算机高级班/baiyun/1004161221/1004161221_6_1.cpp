#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;
int main()
{
	system("touch result.txt");
	system("touch numbers.txt");
	srand(time(NULL));
	ofstream iii("numbers.txt");
	for(int count1=1;count1<=500;++count1)
	{
		iii<<rand()%100+1<<" "<<rand()%100+1<<endl;
	}
	cout<<"Please run on linux platfroms because the commands belong to Linux"<<endl;
	cout<<"It was tested successfuly on Ubuntu 16.04 LTS"<<endl;
	int mode;
	cout<<"Choose the mode 1 for bianry file and 2 for txt/cpp/..."<<endl;
	cin>>mode;
	if(mode==2)
	{
	cout<<"Input the tested file name:"<<endl;
	string filename;
	cin>>filename;
	system("touch waitedname.cpp");//A new cpp source file
	ofstream out("waitedname.cpp");
	ifstream in(filename);
	string tem;
	while(getline(in,tem))
	{
		out<<tem<<endl;//Edit the file
	}
	auto c=system("g++ -std=c++11 waitedname.cpp");//Compile the source file
	if(c!=0){cout<<"Compile Error"<<endl;return 0;}
	else//If compile successfuly
	{
	system("./a.out");
	system("g++ -std=c++11 std.cpp"); //Compile the given source file
	system("./a.out");
	}
	}
	else 
	{
		cout<<"Please rename the binary file to \"b.out\""<<endl;
		system("./b.out");
		system("g++ -std=c++11 std.cpp");
		system("./a.out");	
	}
	vector<int> correctanswer;//Store the true answers
	vector<int> results;// Strore the answers
	int ppp;
	ifstream in2("result.txt");
	while(in2>>ppp)
	{
		results.push_back(ppp);
	}
	ifstream in3("correct.txt");
	while(in3>>ppp)
	{
		correctanswer.push_back(ppp);
	}
	if(correctanswer==results)
		cout<<"Accepted"<<endl;
	else cout<<"Wrong answer"<<endl;
	return 0;
}
