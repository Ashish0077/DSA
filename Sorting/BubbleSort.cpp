#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {

    // this loop keeps the track of iteration
    for(int it = 1; it <= n - 1; it++) {
        for(int j = 0; j <= n - it - 1; j++) {
            // swapping
            if(arr[j] >= arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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

    bubbleSort(arr, n);
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}