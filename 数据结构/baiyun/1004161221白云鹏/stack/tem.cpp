#include<iostream>
#include<vector>
using namespace std;
struct node
{
	node() = default;
	int val = 1;
	node *higher = NULL;
	node *lower = NULL;
};
int main()
{
	int n;
	cin >> n;
	node lowest;
	node *current = &lowest;
	for (int count1 = 1;count1 <= n;++count1)
	{
		int left = 0;
		for (current = &lowest;current->higher!=NULL;current=current->higher)
		{
			current->val *=count1;
			current->val += left;
			left =current-> val / 10;
			current->val %= 10;
		}
		current->val *= count1;
		current->val += left;
		left = current->val / 10;
		current->val %= 10;
		while (left != 0)
		{
			int tem = left % 10;
			auto *aaa = new node;
			aaa->val = tem;
			current->higher = aaa;
			current = aaa;
			left /= 10;
		}
	}
	vector<int> result;
	for (current = &lowest;current != NULL;current = current->higher)
		result.push_back(current->val);
	for (auto c = result.rbegin();c != result.rend();++c)
		cout << *c;
}