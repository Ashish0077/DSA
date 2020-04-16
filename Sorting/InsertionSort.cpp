#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {

    for(int i = 1; i <= n - 1; i++) {
        int e = arr[i];
        // place the element at right position in sorted part
        int j = i - 1;
        while(arr[j] > e && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = e;
    }
}

int main() {

    int n;
    cin >> n;

    int arr[1000];
    for(int i = 0; i < n; i++)
        arr[i] = n - i;

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    insertionSort(arr, n);
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}