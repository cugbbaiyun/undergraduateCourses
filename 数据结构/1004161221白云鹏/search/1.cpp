#include<iostream>
using namespace std;
const int maxn = 1e5 ;
template<typename T>
struct normalSearch{
    T* data;
    int len;
    int ele;
    void init(){
        data = new T[maxn];
        cout << "Input the length of the data:" << endl;
        cin >> len;
        cout << "Input the data:" << endl;
        for(int i =0;i<len;++i){
            cin >> data[i];
        }
        cout << "Input the element:"  << endl;
        cin >> ele;
    }
    void search(){
        cout << "The produce of the search:" << endl;
        for(int i =0 ;i< len ;++i ){
            cout << data[i] << " ";
            if(data[i] == ele){
                return;
            }
        }
        cout << "Not found." << endl;
        return;
    }
};
int main(){
    normalSearch<int> test;
    test.init();
    test.search();
}