#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    
    int counter = 0;

    for(int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for(int j = i; j < n; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // swapping
        if(i != minIndex) {
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
            counter++;
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

    selectionSort(arr, n);
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}