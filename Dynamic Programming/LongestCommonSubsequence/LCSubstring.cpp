#include<bits/stdc++.h>
using namespace std;

int LCSubstring(string x, string y, int lenX, int lenY) {

    /*
        Rows represent len + 1 of string x
        Column represent len + 1 of String y
    */
    int DP[lenX + 1][lenY + 1];

    /*
        First Row when the len of string x is 0 there is no subsequence hence zero
    */
    for(int i = 0; i < lenX + 1; i++)
        DP[i][0] = 0;
    /*
        First Column when the len of string y is 0 there is no subsequence hence zero
    */    
    for(int i = 1; i < lenY + 1; i++)
        DP[0][i] = 0;

    int max = INT_MIN; // this maintains the longest substring's length
    for(int i = 1; i < lenX + 1; i++) {
        for(int j = 1; j < lenY + 1; j++) {
            if (x[i - 1] == y[j - 1])
                DP[i][j] = 1 + DP[i - 1][j - 1];
            else
                DP[i][j] = 0;

            if(max < DP[i][j])
                max = DP[i][j];
        }
    }
    return max;
}

int main() {

    string x = "abcfghi";
    string y = "abcdghi";

    cout << "substring length : " << LCSubstring(x, y, x.length(), y.length()) << endl;

    return 0;
}