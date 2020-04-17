/*
    Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. Determine the maximum value obtainable by cutting up the rod and selling the pieces
*/
#include <bits/stdc++.h>
using namespace std;

int cutRodRecurisve(int len[], int price[], int size, int rodLen) {

    if(rodLen == 0 || size == 0)
        return 0;

    if(len[size - 1] <= rodLen)
        return max(price[size - 1] + cutRodRecurisve(len, price, size, rodLen - len[size - 1]), cutRodRecurisve(len, price, size - 1, rodLen));
    else
        return cutRodRecurisve(len, price, size - 1, rodLen);

}

int DP[1000][1000];
int cutRodTopDownDP(int len[], int price[], int size, int rodLen) {

    if(rodLen == 0 || size == 0)
        return 0;
    
    if(DP[size][rodLen] != -1)
        return DP[size][rodLen];

    if(len[size - 1] <= rodLen)
        DP[size][rodLen] = max(price[size - 1] + cutRodTopDownDP(len, price, size, rodLen - len[size - 1]), cutRodTopDownDP(len, price, size - 1, rodLen));
    else
        DP[size][rodLen] = cutRodTopDownDP(len, price, size - 1, rodLen);
    
    return DP[size][rodLen];
}

int cutRodBottomUpDP(int len[], int price[], int size, int rodLen) {

    int DP[size + 1][rodLen + 1];

    for(int i = 0; i < size + 1; i++)
        DP[i][0] = 0;
    for(int j = 0; j < rodLen + 1; j++)
        DP[0][j] = 0;
    
    for(int i = 1; i < size + 1; i++) {
        for(int j = 1; j < rodLen + 1; j++) {
            if(len[i - 1] <= j)
                DP[i][j] = max(price[i - 1] + DP[i][j - len[i - 1]], DP[i - 1][j]);
            else
                DP[i][j] = DP[i - 1][j];
        }
    }

    return DP[size][rodLen];
}

int main() {

    memset(DP, -1, sizeof(DP));

    int len[] = {1, 2, 3, 4, 5, 6, 8};
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int size = sizeof(len)/sizeof(int);
    int rodLength = len[size - 1]; // asumming the length of rod is equal to maximum length avialable for cutting the rod

    cout << "Maximum Profit (Recursive) : " << cutRodRecurisve(len, price, size, rodLength) << endl;
    cout << "Maximum Profit (TopDown DP) : " << cutRodTopDownDP(len, price, size, rodLength) << endl;
    cout << "Maximum Profit (BottomUp DP) : " << cutRodBottomUpDP(len, price, size, rodLength) << endl;

    return 0;
}