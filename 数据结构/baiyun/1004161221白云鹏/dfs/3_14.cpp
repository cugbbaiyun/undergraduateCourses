#include <iostream>
#include <utility>
using namespace std;
int *arr;
int len;
int getsum(int sum, int now) {
    if (now == len) {
        return sum;
    }
    sum += arr[now];
    return getsum(sum, now + 1);
}
int getave(int sum, int n) {
    if (n == len) {
        return sum / n;
    }
    sum += arr[n];
    return getave(sum, n + 1);
}
int getmax(int max, int n) {
    if (n == len) {
        return max;
    }
    if (arr[n] > max) max = arr[n];
    return getmax(max, n + 1);
}

int main() {
    cout << "Input the length of the array:";
    cin >> len;
    if (len == 0) return 0;
    cout << "Input the element of the array,separated by space or enter:";
    arr = new int[len + 7];
    for (int i = 0; i < len; ++i) {
        cin >> arr[i];
    }
    cout << "the sum of the array is:" << getsum(0, 0) << endl;
    cout << "the average of the array is:" << getave(0, 0) << endl;
    cout << "the max of the array is:" << getmax(-99999, 0) << endl;
}