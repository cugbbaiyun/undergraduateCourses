#include<iostream>
#include<string>
using namespace std;
struct hashlist{
    int mod;
    int len;
    int *list;
    int data;
    void init(){
        cout << "Input the mod:" << endl;
        cin >> mod;
        int len;
        cout << "Input the length of the data:" << endl;
        cin >> len;
        list = new int[mod];
        cout << "Input the data:"<< endl;
        for(int i =0;i<mod;++i){
            list[i] = -1;
        }
        for(int i =0;i<len;++i){
            cin >> data;
            insert(data);
            out();
        }
    }
    void tosearch(){
        cout << "Input the element to seach:" << endl;
        int t;
        cin >>t;
        search(t);
        out();
    }
    int search(int t ){
        int key = t % mod;
        int ok =0 ;
        while(list[key]!=t){
            cout << key<< " ";
            ++key;
            ++ok;
            key%=mod;
            if(ok==len){
                cout << "Search falied" << endl;
                return -1 ;
            }
        }
        return key;
    }

    void del(){
        int t;
        cout << "Input the delete element:"<<endl;
        cin >> t;
        list[search(t)] = -1;
        out();
    }

    void insert(int & t){
        list[gethash(t)] = t;
    }
    void add(){
        int t;
        cout <<"Input the element to add:"<<endl;
        cin >> t;
        insert(t);
        out();
    }
    int gethash(int &t ){
        int key = t % mod;
        while(list[key] !=-1){
            ++key;
            key %= mod;
        }
        return key;
    }
    void out(){
        for(int i =0;i<mod;++i){
            cout << list[i] <<" ";
        }
        cout <<endl;
    }
};
int main(){
    hashlist test;
    test.init();
    test.search();
    test.del();
    test.add();
}
