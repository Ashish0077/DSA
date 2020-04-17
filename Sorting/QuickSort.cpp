#include <iostream>
using namespace std;

#define maxLimit 100006
#define int long long

int partition(int arr[], int start, int end) {

    int pivot = arr[end];
    int i = start - 1;

    for(int j = start; j <= end - 1; j++) {
        if(arr[j] < pivot) {
            i++;
            // swapping
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // place the pivot element at correct possition (arr[end] is equals to pivot)
    arr[end] = arr[i + 1];
    arr[i + 1] = pivot;

    return i + 1;
}

void quickSort(int arr[], int start,int end) {

    // base case
    if (start >= end)
        return;
    
    int p = partition(arr, start, end);

    // left part
    quickSort(arr, start, p - 1);
    // right part
    quickSort(arr, p + 1, end);
    

}

int32_t main() {

    int n;
    cin >> n;

    int arr[maxLimit];
    for(int i = 0; i < n; i++)
        arr[i] = n - i;

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    quickSort(arr, 0, n - 1);
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}