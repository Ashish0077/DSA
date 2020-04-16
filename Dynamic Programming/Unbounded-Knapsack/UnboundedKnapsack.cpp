#include <bits/stdc++.h>
using namespace std;

int knapsackRecursive(int wt[], int val[], int capacity, int size) {

    if(size == 0 || capacity == 0)
        return 0;
    
    if(wt[size - 1] <= capacity)
        return max(val[size - 1] + knapsackRecursive(wt, val, capacity - wt[size - 1], size),knapsackRecursive(wt, val, capacity, size - 1));
    else
        return knapsackRecursive(wt, val, capacity, size - 1);
}

int DP[1000][1000];
int knapsackTopDownDP(int wt[], int val[], int capacity, int size) {

    if(size == 0 || capacity == 0)
        return 0;
    
    if(DP[size][capacity] != -1)
        return DP[size][capacity];
    
    if(wt[size - 1] <= capacity)
        DP[size][capacity] = max(val[size - 1] + knapsackRecursive(wt, val, capacity - wt[size - 1], size),knapsackRecursive(wt, val, capacity, size - 1));
    else
        DP[size][capacity] = knapsackRecursive(wt, val, capacity, size - 1);
    
    return DP[size][capacity];
}

int knapsackBottomUpDP(int wt[], int val[], int capacity, int size) {

    int DP[size + 1][capacity + 1];

    for(int i = 0; i < size + 1; i++)
        DP[i][0] = 0;
    for(int j = 1; j < capacity + 1; j++)
        DP[0][j] = 0;
    
    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < capacity + 1; j++)
            if(wt[i - 1] <= j)
                DP[i][j] = max(val[i - 1] + DP[i][j - wt[i - 1]], DP[i - 1][j]);
            else
                DP[i][j] = DP[i - 1][j];
    }
    
    return DP[size][capacity];

}

int main() {

    memset(DP, -1, sizeof(DP));

    int val[] = {10, 40, 50, 70};
    int wt[]  = {1, 3, 4, 5}; 
    int size = sizeof(wt)/sizeof(int);
    int capacity = 8;

    cout << "Maximum Profit (Recursive) : " << knapsackRecursive(wt, val, capacity, size) << endl;
    cout << "Maximum Profit (TopDown DP) : " << knapsackTopDownDP(wt, val, capacity, size) << endl;
    cout << "Maximum Profit (BottomUp DP) : " << knapsackBottomUpDP(wt, val, capacity, size) << endl;

    return 0;
}