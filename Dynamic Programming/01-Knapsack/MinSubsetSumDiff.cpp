#include <bits/stdc++.h>
using namespace std;

vector<int> subsetSum(int arr[], int sum, int size) {
    
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

    vector<int> possibleSums;
    for(int i = 0; i < sum/2 + 1; i++) {
        if(DP[size][i])
            possibleSums.emplace_back(i);
    }

    return possibleSums;
}

int minSubsetSumDiff(int arr[], int size) {

    int sum = 0;
    for(int i = 0; i < size; i++)
        sum += arr[i];

    auto possibleSums = subsetSum(arr, sum, size);

    int min = INT_MAX;
    for(auto it: possibleSums) {
        int temp = sum - (2 * it);
        if (min > temp)
            min = temp;
    }

    return min;
}

int main() {

    int arr[] = {1, 6, 11, 5};
    int size = sizeof(arr)/sizeof(int);

    cout << "Min Difference : " << minSubsetSumDiff(arr, size) << "\n";

    return 0;
}