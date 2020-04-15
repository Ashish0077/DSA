#include<bits/stdc++.h>
using namespace std;

bool subsetSumRecursive(int arr[], int sum, int size) {

    // base case A 
    // when required sum is 0 we can always construct a {} null set hence always true
    if (sum == 0)
        return true;
    
    // base case B
    // if the size of array is 0 we can not construct any set hence always false
    if(size == 0)
        return false;

    if(arr[size - 1] <= sum)
        return subsetSumRecursive(arr, sum - arr[size - 1], size - 1) || subsetSumRecursive(arr, sum, size - 1);
    else 
        return subsetSumRecursive(arr, sum, size - 1);
}

int DP[1000][1000];
bool subsetSumTopDownDP(int arr[], int sum, int size) {
    
    // base case A 
    // when required sum is 0 we can always construct a {} null set hence always true
    if (sum == 0)
        return true;
    
    // base case B
    // if the size of array is 0 we can not construct any set hence always false
    if(size == 0)
        return false;

    if(DP[size][sum] != -1)
        return DP[size][sum];

    if(arr[size - 1] <= sum)
        DP[size][sum] =  subsetSumRecursive(arr, sum - arr[size - 1], size - 1) || subsetSumRecursive(arr, sum, size - 1);
    else 
        DP[size][sum] =  subsetSumRecursive(arr, sum, size - 1);
    
    return DP[size][sum];
}

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

int main() {

    memset(DP, -1, sizeof(DP));

    int arr[] = {3, 34, 4, 12, 5, 2};
    int size = sizeof(arr)/sizeof(int);
    int sum = 9;
    
    cout << "Is there a Subset with sum = " << sum << " ?\n";
    cout << "Recursive Approach : "<< (subsetSumRecursive(arr, sum, size) ? "True" : "False")<< endl;
    cout << "Top Down DP Approach : "<< (subsetSumTopDownDP(arr, sum, size) ? "True" : "False")<< endl;
    cout << "Bottom Up DP Approach : "<< (subsetSumBottomUpDP(arr, sum, size) ? "True" : "False")<< endl;
    return 0;
}