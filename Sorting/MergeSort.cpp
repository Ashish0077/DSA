#include <iostream>
using namespace std;

void merge(int arr[], int start, int end) {
    int midPoint = (start + end) / 2;
    int i = start;
    int j = midPoint + 1;
    
    int k = 0; // this keeps track of temp array
    int temp[end - start + 1];

    while(i <= midPoint && j <= end) {
        if(arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= midPoint)
        temp[k++] = arr[i++];
    
    while(j <= end)
        temp[k++] = arr[j++];

    // copying temp array back to original array
    for(int i = start, j = 0;i <= end && j < end - start + 1; i++, j++)
        arr[i] = temp[j];
}

void mergeSort(int arr[], int start,int end) {

    // base case
    if(start >= end)
        return;

    int midPoint = (start + end) / 2;
    mergeSort(arr, start, midPoint);
    mergeSort(arr, midPoint + 1, end);

    merge(arr, start, end);

}

int main() {

    int n;
    cin >> n;

    int arr[1000];
    for(int i = 0; i < n; i++)
        arr[i] = n - i;

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    mergeSort(arr, 0, n - 1);
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}