#include <iostream>
using namespace std;

int n;
void print(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
    cout << endl;
}

void merge(int a[], int s, int t) {
    int mid = (s + t) / 2;
    int *temp = new int[t - s + 1];
    int i = s, j = mid + 1, k = 0;
    while (i <= mid && j <= t) {
        if (a[i] < a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
        
    }
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= t) {
        temp[k++] = a[j++];
    }
    //cout << s << ' ' << t << ' ' << mid <<endl;
    //print(temp, t - s + 1);
    for (int i = s, j = 0; i <= t; ++i, ++j) {
        a[i] = temp[j];
    }
    delete []temp;
}

void mergesort(int a[], int s, int t) {
    if (s == t) {
        return;
    }
    int mid = (s + t) / 2;
    mergesort(a, s, mid);
    mergesort(a, mid + 1, t);
    merge(a, s, t);
    print(a, n);
}

int main(void) {
    cin >> n;
    int *a = new int[n + 10];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    mergesort(a, 0, n - 1);
    delete[] a;
}