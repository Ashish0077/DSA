#include<bits/stdc++.h>
using namespace std;

int LCS_Recursive(string x, string y, int lenX, int lenY) {

    /*
        Base condition
        when the length of the string x and y is Zero
        then there will be NO common subsequence!!
    */
    if(lenX == 0 || lenY == 0)
        return 0;

    /*
        When the last char of the strings matches we can say one char
        matched and we can look for next char in lenX - 1 and lenY - 1
    */
    if (x[lenX - 1] == y[lenY - 1])
        return 1 + LCS_Recursive(x, y, lenX - 1, lenY - 1);
    /*
        When the character does not matches we have two choices
        decrease the len of one string and not of other and choose 
        max option from it
    */
    else 
        return max(LCS_Recursive(x, y, lenX -1, lenY), LCS_Recursive(x, y, lenX, lenY - 1));
}

int DP[1000][1000];
int LCS_TopDownDP(string x, string y, int lenX, int lenY) {

    /*
        Base condition
        when the length of the string x and y is Zero
        then there will be NO common subsequence!!
    */
    if(lenX == 0 || lenY == 0)
        return 0;

    /*
        Check if we have already computed the solution
    */
    if(DP[lenX][lenY] != -1)
        return DP[lenX][lenY];

    /*
        When the last char of the strings matches we can say one char
        matched and we can look for next char in lenX - 1 and lenY - 1
        and memoize it.
    */
    if (x[lenX - 1] == y[lenY - 1])
        DP[lenX][lenY] = 1 + LCS_TopDownDP(x, y, lenX - 1, lenY - 1);
    /*
        When the character does not matches we have two choices
        decrease the len of one string and not of other and choose 
        max option from it and Memoize it.
    */
    else 
        DP[lenX][lenY] = max(LCS_TopDownDP(x, y, lenX -1, lenY), LCS_TopDownDP(x, y, lenX, lenY - 1));

    return DP[lenX][lenY];
}

int LCS_BottomUpDP(string x, string y, int lenX, int lenY) {

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


    for(int i = 1; i < lenX + 1; i++) {
        for(int j = 1; j < lenY + 1; j++)
            if (x[i - 1] == y[j - 1])
                DP[i][j] = 1 + DP[i - 1][j - 1];
            else 
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
    }

    return DP[lenX][lenY];
}

int main() {

    memset(DP, -1, sizeof(DP));

    string x = "abcdgh";
    string y = "abedfhr";

    cout << "LCS (Recursive) : " << LCS_Recursive(x, y, x.length(), y.length()) << endl;
    cout << "LCS (TopDown Up) : " << LCS_TopDownDP(x, y, x.length(), y.length()) << endl;
    cout << "LCS (BottomUp Up) : " << LCS_BottomUpDP(x, y, x.length(), y.length()) << endl;

    return 0;
}