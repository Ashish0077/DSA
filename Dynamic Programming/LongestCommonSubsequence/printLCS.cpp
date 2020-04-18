#include<bits/stdc++.h>
using namespace std;

string LCS(string x, string y, int lenX, int lenY) {

    int DP[lenX + 1][lenY + 1];

    for(int i = 0; i < lenX + 1; i++)
        DP[i][0] = 0;
    for(int j = 1; j < lenY + 1; j++)
        DP[0][j] = 0;
    
    for(int i = 1; i < lenX + 1; i++) {
        for(int j = 1; j < lenX + 1; j++)
            if(x[i - 1] == y[j - 1])
                DP[i][j] = 1 + DP[i - 1][j - 1];
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
    }

    int i = lenX, j = lenY;
    string s;
    while(i > 0 && j > 0) {
        if(x[i - 1] == y[j - 1]) {
            s.push_back(x[i - 1]);
            i--;
            j--;
        } else {
            if(DP[i - 1][j] > DP[i][j - 1])
                i--;
            else
                j--;
        }
    }
    reverse(s.begin(), s.end());

    return s;
}

int main() {

    string x = "acbcf";
    string y = "abcdaf";

    cout << LCS(x, y, x.length(), y.length()) << endl;
}