#include <bits/stdc++.h>
using namespace std;

bool subsetSumBottomUpDP(int arr[], int sum, int size) {

    bool DP[size + 1][sum + 1];

    for(int i = 0; i < size + 1; i++)
        DP[i][0] = true;

    for(int j = 1; j < sum + 1; j++)
        DP[0][j] = false;
    
    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < sum + 1; j++) {
            if(arr[i - 1] <= j)
                DP[i][j] = DP[i - 1][j - arr[i - 1]] || DP[i - 1][j];
            else 
                DP[i][j] = DP[i - 1][j];
        }
    }

    return DP[size][sum];
}

bool equalSumPartition(int arr[], int size) {

    int sum = 0;
    for(int i = 0; i < size; i++)
        sum += arr[i];

    // if the sum is odd then it is not possible to make equal sum partition
    if (sum % 2 != 0)
        return false;
    
    // if the sum is even then if we find only 1 parition with sum/2 other partition will obviously be available in the array as the sum is even
    return subsetSumBottomUpDP(arr, sum/2, size);
}


int main() {

    int arrA[] = {1, 5, 11, 5};
    int sizeA = sizeof(arrA)/sizeof(int);
    int arrB[] = {1, 5, 3};
    int sizeB = sizeof(arrB)/sizeof(int);

    cout << "A : ";
    for(auto it: arrA)
        cout << "|" << it;
    cout << "| => " << ( (equalSumPartition(arrA, sizeA)) ? "true" : "false" ) << endl;
    cout << "B : ";
    for(auto it: arrB)
        cout << "|" << it;
    cout << "| => " << ( (equalSumPartition(arrB, sizeB)) ? "true" : "false" ) << endl;

    return 0;
}