/*
    You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

    Find out how many ways to assign symbols to make sum of integers equal to target S.

*/

// THIS PROBLEM IS EXACTLY SAME AS "Count Subsets with given difference" just the difference is called TargetSum here!! :)

#include <bits/stdc++.h>
using namespace std;

int signs(int arr[], int targetSum, int size) {

    int sum = 0;
    for(int i = 0; i < size; i++)
        sum += arr[i];
    
    int subsetsSum = (sum + targetSum) / 2;

    int DP[size + 1][subsetsSum + 1];

    for(int i = 0; i < size + 1; i++)
        DP[i][0] = 1;
    for(int j = 1; j < subsetsSum + 1; j++)
        DP[0][j] = 0;
    
    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < subsetsSum + 1; j++)
            if(arr[i - 1] <= j)
                DP[i][j] = DP[i - 1][j - arr[i - 1]] + DP[i - 1][j];
            else 
                DP[i][j] = DP[i - 1][j];
    }

    return DP[size][subsetsSum];

}

int main() {

    int arr[] = {1, 1, 1, 1, 1};
    int sum = 3;
    int size = sizeof(arr)/sizeof(int);

    cout << "Number of Ways we can Assign Signs : " << signs(arr, sum, size) << endl;

    return 0;

}