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

int countSubsetsOfDiff(int arr[], int diff, int size) {

    int sum = 0;
    for(int i = 0; i < size; i++)
        sum += arr[i];

    int subsetSum = (sum + diff) / 2;

    int count = countSubsetsOfSum(arr, subsetSum, size);

    return count;
}

int main() {

    int arr[] = {1, 1, 2, 3};
    int diff = 1;
    int size = sizeof(arr)/sizeof(int);

    cout << "Number of subsets with Given Diff : " << countSubsetsOfDiff(arr, diff, size) << endl;

    return 0;
}