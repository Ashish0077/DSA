#include<bits/stdc++.h>
using namespace std;

/*
    Initial Approach to solve knapsack problem
    A recursive Solution
    Time Complexity : O(2^size)
    Space Complexity : O(size)
*/
int knapsackRecursive(int wt[], int val[], int capacity, int size) {

    // base case
    if(size == 0 || capacity == 0)
        return 0;
    
    // when weight of the item is less or equal to the capacity of the knapsack
    if(wt[size - 1] <= capacity)
        return max(val[size -1] + knapsackRecursive(wt, val, capacity - wt[size - 1], size - 1), knapsackRecursive(wt, val, capacity, size - 1)); // choosing the btr option max(item included, item not included)
    else // when weight of the item is more than capcity of the knapsack
        return knapsackRecursive(wt, val, capacity, size - 1); // skiping that current item
}

/*
    Memoizing the recursive solution to eleminate dublicate
    recursive calls
*/
int DP[1000][1000]; // global DP varibale this is used for memoization
int knapsackTopDownDP(int wt[], int val[], int capacity, int size) {

    // base case
    if(capacity == 0 || size == 0)
        return 0;

    // if the result is already computed, no recursive call will be made
    if(DP[size][capacity] != -1)
        return DP[size][capacity];
    
    if(wt[size - 1] <= capacity) {
        // memoization storing the result in DP matrix
        DP[size][capacity] = max(val[size - 1] + knapsackTopDownDP(wt, val, capacity - wt[size - 1], size - 1), knapsackTopDownDP(wt, val, capacity, size - 1)); // same as recursive solution choosing the btr option
    } else {
        // memoization stroing the result in DP matrix
        DP[size][capacity] = knapsackTopDownDP(wt, val, capacity, size - 1);
    }

    return DP[size][capacity];
}

/*
    converting the memoized recursive solution (TopDown DP)
    to Bottom Up DP (Iterative approach)
*/
int knapsackBottomUpDP(int wt[], int val[], int capacity, int size) {
    
    /*
        initial DP Matrix
        rows represent size and column represents capacity of the knapsack
        we are taking + 1 extra becase 1st column and 1st row will be filled with base conditions which will be used to build the solution further up
    */
    int DP[size + 1][capacity + 1];

    // initialization (base cases) this is used to build further solutions
    for(int i = 0; i < size + 1; i++)
        DP[i][0] = 0;
    for(int j = 1; j < capacity + 1; j++)
        DP[0][j] = 0;

    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < capacity + 1; j++) {
            if(wt[i - 1] <= j) {
                DP[i][j] = max(val[i - 1] + DP[i - 1][j - wt[i - 1]], DP[i - 1][j]);// choosing the btr option same as above solutions
            } else {
                DP[i][j] = DP[i - 1][j]; // skipping the item
            }
        }
    }

    return DP[size][capacity];
}

int main() {

    memset(DP, -1, sizeof(DP));

    int wt[] = {10, 20, 30};
    int val[] = {60, 100, 120};
    int size = sizeof(wt)/ sizeof(int);
    int capacity = 50;

    cout << "Maximum Profit (Recursive) : " << knapsackRecursive(wt, val, capacity ,size) << endl;
    cout << "Maximum Profit (TopDown DP) : " << knapsackTopDownDP(wt, val, capacity ,size) << endl;
    cout << "Maximum Profit (BottomUp DP) : " << knapsackBottomUpDP(wt, val, capacity ,size) << endl;

    return 0;
}