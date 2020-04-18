#include <bits/stdc++.h>
using namespace std;
#define int long long

int minCoins(int coins[], int sum, int size) {

    int DP[size + 1][sum + 1];

    // initializing the first row of the matrix with INT_MAX -1
    for(int i = 0; i < sum + 1; i++)
        DP[0][i] = INT_MAX - 1;
    // initializing the first column with 0
    for(int j = 1; j < size + 1; j++)
        DP[j][0] = 0;

    // initializing the second row of the matrix with number of coins required by it
    for(int j = 1; j < sum + 1; j++)
        if(j % coins[0] == 0)
            DP[1][j] = j / coins[0];
        else
            DP[1][j] = INT_MAX - 1;
    
    for(int i = 2; i < size + 1; i++) {
        for(int j = 1; j < sum + 1; j++)
            if(coins[i - 1] <= j)
                DP[i][j] = min(1 + DP[i][j - coins[i - 1]], DP[i - 1][j]);
            else
                DP[i][j] = DP[i - 1][j];
    }
    
    return DP[size][sum];
}

int32_t main() {

    int coins[] = {9, 6, 5, 1};
    int sum  = 35; 
    int size = sizeof(coins)/sizeof(int);
    cout << "Min Coins : " << minCoins(coins, sum, size) << endl;

    return 0;
}