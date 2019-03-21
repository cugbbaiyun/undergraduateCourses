#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;
using int2 = vector<int>::size_type;
struct node
{
	int n;
	node* left=0;
	node* right =0;
};
void treecreat(node *head, vector<int> a)
{
	int2  count1=a.size();
	head->n = a[0];
	for (int2 count2 = 1;count2 < count1;++count2)
	{
		node *current = head;
		while (1)
		{
			if (a[count2] > current->n&&current->right)
			{
				current = current->right;
            }
			else if (a[count2] < current->n&&current->left)
				current = current->left;
			else break;
		}
		auto *p = new node;
		p->n = a[count2];
		if (p->n > current->n)current->right= p;
		else current->left= p;
	}
}
void foreprint(node *p)
{
	if (p == 0)return;
	cout << p->n << " ";
    foreprint(p->left);
    foreprint(p->right);
}
void afterprint(node *p)
{
    if(p==0)return;
    afterprint(p->left);
    afterprint(p->right);
    cout<<p->n<<" ";
}
void inprint(node *p)
{
    if(p==0)return;
    inprint(p->left);
    cout<<p->n<<" ";
    inprint(p->right);
}
void clear1(node *p)
{
    if(p->left)clear1(p->left);
    if(p->right)clear1(p->right);
    delete(p);
}
void levelprint(node *root)
{
    int head=0,tail=0;
    if(!root)return;
    decltype(root) dequeue[1025]={root};
    ++tail;
    while(head!=tail)
    {
        cout<<dequeue[head]->n<<" " ;
        if(dequeue[head]->left)dequeue[tail++]=dequeue[head]->left;
        if(dequeue[head]->right)dequeue[tail++]=dequeue[head]->right;
        ++head;
    }
}
int main()
{
    cout<<"二叉排序树是用链表做的"<<endl;
    srand(time(0));
    vector<int> aaa;
    int tem;
    for(int2 count2=1;count2<=30;++count2)
    {
        tem=rand()%1000+1;
        aaa.push_back(tem);
    }
    int count1=1;
    cout<<"原数组为："<<endl;
    for(auto c:aaa)
    {cout<<c<<" ";
    ++count1;if(count1==11){cout<<endl;count1=1;}}
    auto head=new node;
    treecreat(head,aaa);
    cout<<"前序遍历："<<endl;
    foreprint(head);
    cout<<endl;
    cout<<"中序遍历："<<endl;
    inprint(head);
    cout<<endl;
    cout<<"后序遍历："<<endl;
    afterprint(head);
    cout<<endl;
    cout<<"层次遍历："<<endl;
    levelprint(head);
    cout<<endl;
    aaa.clear();
    system("pause");
    return 0;
}
