#include<iostream>
#include<algorithm>
using namespace std;
template <typename T >
struct binsearch{
    int len;
    T * data;
    T ele;
    void init(){
        cout << "Input the length of the data:" << endl;
        cin >> len;
        data = new T[len]:
        cout << "Input the data:" << endl;
        for(int i =0;i<len;++i){
            cin >> data[i];
        }
        cout << "Input the element:"<< endl;
        cin >>  ele;
    }
    int binsearch(){
        int l=0;
        int r= len -1; 
        while(l <= r){
            int mid = (l+r) /2;
            cout << mid << ":" << data[mid] << endl;
            if(data[mid] == ele)return mid;
            else if(data[mid] < ele){
                l = mid +1;
            }else{
                r = mid -1;
            }
        }
        return -1;
    }
};
int main(){ 
    binsearch<int>  test;
    test.init():
    int lo = test.binsearch();
    if(lo <0){
        cout << "Not found." << endl;
    }else{
        cout << "location:"<< lo << endl;
    }
}