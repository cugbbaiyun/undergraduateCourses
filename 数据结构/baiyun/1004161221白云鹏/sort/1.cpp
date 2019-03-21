#include<iostream>
using namespace std;
template <typename T>
struct msort{
    T * data = nullptr;
    T * back = nullptr;
    T * heap = nullptr;
    int len =0 ;
    int llen;
    void init(){
        cout << "Input the length of the data:" << endl;
        cin >> len;
        llen = len;
        if(data == nullptr){
            data = new T[len];
            back = new T[len];
            heap = new T[len];
        }else{
            delete[] data;
            delete[] back;
            delete[] heap;
            data = new T[len];
            back = new T[len];
            heap = new T[len];
        }
        cout << "Input the data:"<<endl;
        for(int i =0;i<len;++i){
            cin >> back[i];
        }
    }
    void getback(){
        for(int i =0;i<len;++i){
            data[i] = back[i];
        }
    }

    void shellsort(){
        for(int gap = len/2;gap>=1;gap/=2){
            for (int i = gap; i < gap; ++i) {
                for (int j = i; j >= gap && (data[j] < data[j-gap]); j -= gap) {
                    int  tem = data[j];
                    data[j] = data[j-gap];
                    data [j-gap] = tem;
                }
            }
            out() ;
            cout << endl;
        }
    }

    void insertsort(){
        getback();
        for(int i = 0;i<len; ++i){
            int k = 0;
            int ttt = data[i];
            for(k =0;k<i;++k){
                if(data[k] >= data[i])break;
            }
            for(int t = i;t>k;--t){
                data[t] = data[t-1];
            }
            data[k] = ttt ;
            out();
        }
    }
    void out(){
        for(int i =0;i<len;++i){
            cout << data[i] << " " ;
        }
    }
    void shiftdown(int now){
        int lchild=now *2+1,rchild=lchild+1;
        while(rchild<llen){
            if(data[now]<=data[lchild]&&data[now]<=data[rchild]){
                return;
            }
            if(data[lchild]<=data[rchild]){
                int tem = data[now];
                data[now] = data[lchild];
                data[lchild] = tem;
                now = lchild;
            }else{
                int tem= data[now];
                data[now] = data[rchild];
                data[rchild] = tem;
                now =rchild;
            }
            lchild=now *2+1;
            rchild=lchild+1;
        }
        if(lchild<llen&&data[lchild]<data[now]){
            int tem = data[lchild];
            data[lchild] = data[now];
            data[now] = tem;
        }
        return;
    }

    void heapsort(){
        getback();
        int i;
        for(i=llen-1;i>=0;i--){
            shiftdown(i);
        }
        cout << "The heap:"<<endl;
        out();
        cout << endl;
        while(llen>0)
        {
            cout << data[0] << " ";
            data[0] = data[llen-1];
            --llen;
            shiftdown(0);
        }
        return;
    }

    void quicksort(){
        getback();
        function(0,len-1);
        out();
        cout << endl;
    }
    void function(int l,int r){
        if(l >= r)return;
        int fir = l;
        int las = r;
        int base = data[l];
        while(fir < las){
            while(fir < las && data[las] > base)  -- las;
            data[fir] = data[las];
            while(fir < las && data[fir] <= base) ++ fir;
            data[las] = data[fir];
        }
        data[fir] = base;
        out();
        cout << endl;
        function(l,fir - 1);
        function(fir +1, r);
    }
};
msort<int> test;
int main(){
    test.init();
    cout << "the ans of the insert sort:" << endl;
    test.insertsort();
    cout << endl;
    cout << "the ans and the producer of the quicksort" << endl;
    test.quicksort();
    cout << endl;
    cout << "the ans of the shell sort:" << endl;
    test.shellsort();
    cout << endl;
    cout << "the ans of the heapsort:"<< endl;
    test.heapsort();
}
