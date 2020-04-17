#include <bits/stdc++.h>
using namespace std;

int coinChangeRecursive(int coins[], int sum, int size) {

    // base case
    if(sum == 0)
        return 1;
    // base case
    if(size == 0)
        return 0;
    
    if(coins[size - 1] <= sum)
        return (coinChangeRecursive(coins, sum - coins[size - 1], size) + coinChangeRecursive(coins, sum, size - 1));
    else
        return coinChangeRecursive(coins, sum, size - 1);
}

int DP[1000][1000];
int coinChangeTopDownDP(int coins[], int sum, int size) {

    // base case
    if(sum == 0)
        return 1;
    // base case
    if(size == 0)
        return 0;
        
    if(DP[size][sum] != -1)
        return DP[size][sum];
    
    if(coins[size - 1] <= sum)
        DP[size][sum] = (coinChangeRecursive(coins, sum - coins[size - 1], size) + coinChangeRecursive(coins, sum, size - 1));
    else
        DP[size][sum] = coinChangeRecursive(coins, sum, size - 1);
    
    return DP[size][sum];
}

int coinChangeBottomUpDP(int coins[], int sum, int size) {

    int DP[size + 1][sum + 1];

    for(int i = 0; i < size + 1; i++)
        DP[i][0] = 1;
    for(int j = 1; j < sum + 1; j++)
        DP[0][j] = 0;
    
    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < sum + 1; j++)
            if(coins[i - 1] <= j)
                DP[i][j] = DP[i][j - coins[i - 1]] + DP[i - 1][j];
            else
                DP[i][j] = DP[i - 1][j];
    }
    
    return DP[size][sum];

}

int main() {

    memset(DP, -1, sizeof(DP));

    int coins[] = {1, 2, 3};
    int sum  = 5; 
    int size = sizeof(coins)/sizeof(int);

    cout << "Maximum Ways (Recursive) : " << coinChangeRecursive(coins, sum, size) << endl;
    cout << "Maximum Ways (TopDown DP) : " << coinChangeTopDownDP(coins, sum, size) << endl;
    cout << "Maximum Ways (BottomUp DP) : " << coinChangeBottomUpDP(coins, sum, size) << endl;

    return 0;
}