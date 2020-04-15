#include <bits/stdc++.h>
using namespace std;

int countSubsetsOfSum(int arr[], int sum, int size) {

    int DP[size + 1][sum + 1];

    for(int i = 0; i < size + 1; i++)
        DP[i][0] = 1;

    for(int j = 1; j < sum + 1; j++)
        DP[0][j] = 0;
    
    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < sum + 1; j++) {
            if(arr[i - 1] <= j)
                DP[i][j] = DP[i - 1][j - arr[i - 1]] + DP[i - 1][j];
            else 
                DP[i][j] = DP[i - 1][j];
        }
    }
    return DP[size][sum];
}

int main() {

    int arr[] = {2, 3, 5, 6, 8, 10};
    int size = sizeof(arr)/sizeof(int);
    int sum = 10;
    int count = countSubsetsOfSum(arr, sum, size);

    cout << "Count : " << count << endl;

}