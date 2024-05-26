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

SortResult BubbleSort(int a[], int n) {
    SortResult result = {0, 0};
    int i = n;
    while (i > 1) {
        int last = 1;
        for (int j = 1; j < i; ++j) {
            result.comparisons++;
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                result.swaps++;
                last = j;
            }
        }
        i = last;
    }
    return result;
}

SortResult SimpleSelectionSort(int a[], int n) {
    SortResult result = {0, 0};
    for (int i = 1; i < n; ++i) {
        int imin = -1, amin = INT_MAX;
        for (int j = i; j <= n; ++j) {
            result.comparisons++;
            if (a[j] < amin) {
                imin = j;
                amin = a[j];
            }
        }
        if (i != imin) {
            int t = a[i];
            a[i] = a[imin];
            a[imin] = t;
            result.swaps++;
        }
    }
    return result;
}

SortResult InsertionSort(int a[], int n) {
    SortResult result = {0, 0};
    for (int i = 2; i <= n; ++i) {
        result.comparisons++;
        if (a[i] < a[i - 1]) {
            a[0] = a[i];
            a[i] = a[i - 1];
            result.swaps++;
            int j;
            for (j = i - 2; a[0] < a[j]; --j) {
                a[j + 1] = a[j];
                result.comparisons++;
                result.swaps++;
            }
            result.comparisons++;
            a[j + 1] = a[0];
        }
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
    SortResult cnt = BubbleSort(a, n);
    chrono::time_point stop = chrono::high_resolution_clock::now();
    if (n < 20) {
        printArray(a, n);
    }
    cout << "Bubble sort: Number of comparison: " << cnt.comparisons
         << ", Number of swapping: " << cnt.swaps
         << ", Execution time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms\n";

    memcpy(a + 1, original + 1, (size_t)n * sizeof(int));
    start = chrono::high_resolution_clock::now();
    cnt = InsertionSort(a, n);
    stop = chrono::high_resolution_clock::now();
    if (n < 20) {
        printArray(a, n);
    }
    cout << "Insertion sort: Number of comparison: " << cnt.comparisons
         << ", Number of swapping: " << cnt.swaps
         << ", Execution time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms\n";

    memcpy(a + 1, original + 1, (size_t)n * sizeof(int));
    start = chrono::high_resolution_clock::now();
    cnt = SimpleSelectionSort(a, n);
    stop = chrono::high_resolution_clock::now();
    if (n < 20) {
        printArray(a, n);
    }
    cout << "Simple selection sort: Number of comparison: " << cnt.comparisons
         << ", Number of swapping: " << cnt.swaps
         << ", Execution time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms\n";
    delete[] a;
    delete[] original;
}