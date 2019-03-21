#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	ifstream in("numbers.txt");
	system("touch correct.txt");
	int number1,number2;
	ofstream out("correct.txt");
	while(in>>number1>>number2)
	{
		vector<int> tem;
		int ppp;
		ppp=number1+number2;
		if(ppp<=100)tem.push_back(ppp);
		ppp=number1*number2;
		if(ppp<=100)tem.push_back(ppp);
		ppp=number1-number2;
		if(ppp<=100)tem.push_back(ppp);
		ppp=number2-number1;
		if(ppp<=100)tem.push_back(ppp);
		int max1=-99999;
		for(auto  c: tem)
		{
			if(c>max1)max1=c;
		}
		out<<max1<<endl;
	}
}
