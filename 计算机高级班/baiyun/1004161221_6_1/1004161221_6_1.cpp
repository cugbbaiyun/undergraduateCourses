#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
void stupro(vector<int> num1s,vector<int> num2s,vector<int> &wresults)
{
	auto c=num1s.size();
	auto current=c;
	for(current=0;current<c;++current)
	{
		vector<int> tem;
		tem.push_back(num1s[current]+num2s[current]);	
		tem.push_back(num1s[current]*num2s[current]);	
		tem.push_back(num1s[current]-num2s[current]);	
		tem.push_back(num2s[current]-num1s[current]);	
		int max=-100000;
		for(auto c:tem)
		{
			if(c>max)max=c;
		}
		wresults.push_back(max);
	}
}
int main()
{
	vector<int> num1s,num2s;
	int tem;
	vector<int> cresults;
	vector<int> wresults;	
	ifstream in("in.txt",ifstream::in);
	int n;
	int top=0;
	ifstream in2("answers.txt",ifstream::in);
	while(in>>n)
	{
		++top;
		wresults.clear();
		cresults.clear();
		num1s.clear();
		num2s.clear();
		for(int count1=1;count1<=n;++count1)
		{
			int num1,num2;
			in>>num1>>num2;
			num1s.push_back(num1);
			num2s.push_back(num2);
			in2>>tem;
			cresults.push_back(tem);
		}
		stupro(num1s,num2s,wresults);	
		if(wresults!=cresults)
		{
			in.close();in2.close();
			cout<<"Wrong answer on test "<<top;
			return 0;
		}
	}
	in.close();
	in2.close();
	cout<<"Accepted"<<endl;
}
