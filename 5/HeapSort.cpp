#include <chrono>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

#define MAXN 50000

struct SortResult {
    int comparisons;
    int swaps;
};

SortResult Heapify(int a[], int l, int r) {
    SortResult result = {0, 0};
    int t = a[l];
    for (int i = l * 2; i <= r; l = i, i *= 2) {
        if (i + 1 <= r) {
            result.comparisons++;
            if (a[i] < a[i + 1]) {
                ++i;
            }
        }
        result.comparisons++;
        if (a[i] <= t) {
            break;
        }
        result.swaps++;
        a[l] = a[i];
    }
    result.swaps++;
    a[l] = t;
    return result;
}

SortResult HeapSort(int a[], int n) {
    SortResult result = {0, 0};
    for (int i = n / 2; i >= 1; --i) {
        SortResult res = Heapify(a, i, n);
        result.comparisons += res.comparisons;
        result.swaps += res.swaps;
    }
    for (int i = n; i >= 1; --i) {
        result.swaps++;
        int t = a[i];
        a[i] = a[1];
        a[1] = t;
        Heapify(a, 1, i - 1);
    }
    return result;
}

int *loadArray(int &n) {
    ifstream s;
    // s.open("intfile_small.dat");
    s.open("intfile.dat");
    int *a = new int[MAXN];
    if (!a) exit(EXIT_FAILURE);
    n = 1;
    while (true) {
        if (n >= MAXN) {
            cout << "Too many data\n";
            exit(EXIT_FAILURE);
        }
        s >> a[n];
        ++n;
        if (s.eof()) break;
    }
    n--;
    return a;
}

void printArray(int a[], int n) {
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

int main() {
    int n;
    int *original = loadArray(n);
    int *a = new int[MAXN];
    if (!a) exit(EXIT_FAILURE);
    cout << "Number of elements: " << n << "\n";

    memcpy(a + 1, original + 1, (size_t)n * sizeof(int));
    chrono::time_point start = chrono::high_resolution_clock::now();
    SortResult cnt = HeapSort(a, n);
    chrono::time_point stop = chrono::high_resolution_clock::now();
    if (n < 20) {
        printArray(a, n);
    }
    cout << "Heap sort: Number of comparison: " << cnt.comparisons
         << ", Number of swapping: " << cnt.swaps
         << ", Execution time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms\n";
    delete[] a;
    delete[] original;
}