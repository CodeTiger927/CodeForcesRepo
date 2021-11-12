#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<queue>
#include<cmath>
#include<deque>
#include<stack>
#include<iomanip>
#include<random>
#include<cstdio>
#include<string>
#include<cstring>
#include<fstream>
#include<numeric>
#include<bitset>
#include<cassert>
 
using namespace std;
 
const int N = 21, M = 31607;
 
int mul(int a, int b) {
    return a * b % M;
}
 
int p(int a, int n) {
    int res = 1;
    while (n) {
        if (n % 2) {
            res = mul(res, a);
        }
        a = mul(a, a);
        n /= 2;
    }
    return res;
}
 
bool have[M];
int inv[M];
 
int d(int a, int b) {
    if (!have[b]) {
        have[b] = true;
        inv[b] = p(b, M - 2);
    }
    return mul(a, inv[b]);
}
 
int a[N][N], n;
int val[N], prod[N];
 
void print(int mask) {
    for (int i = 0; i < n + 2; i++) {
        cout << ((mask >> i) & 1);
    }
}
 
int f(int i, int mask) {/*
    cout << "------------ now in  ---------  " << i << endl;
    cout << "mask: ";
    print(mask);
    cout << endl;
    cout << "val: ";
    for (int i = 0; i < n; i++) {
        cout << val[i] << " ";
    }
    cout << endl;*/
    if (i == n + 2) {
        int res = 1;
        for (int i = 0; i < n; i++) {
            res = mul(res, (1 - d(prod[i], val[i]) + M) % M);
        }/*
        cout << "dp[" << i << "][";
        print(mask);
        cout << "] =  " << res << endl;*/
        return res;
    }
    int res = f(i + 1, mask);
    int p = 1;
    if (i == 0) {
        for (int j = 0; j < n; j++) {
            p = mul(p, a[j][j]);
            val[j] = mul(val[j], a[j][j]);
        }
        res = (res - mul(f(i + 1, mask | (1 << i)), p) + M) % M;
        for (int j = 0; j < n; j++) {
            val[j] = d(val[j], a[j][j]);
        }
    }
    else if (i == 1) {
        for (int j = 0; j < n; j++) {
            if ((mask & 1) && 2 * j == n - 1) continue;
            p = mul(p, a[j][n - 1 - j]);
            val[n - 1 - j] = mul(val[n - 1 - j], a[j][n - 1 - j]);
        }
        res = (res - mul(f(i + 1, mask | (1 << i)), p) + M) % M;
        for (int j = 0; j < n; j++) {
            if ((mask & 1) && 2 * j == n - 1) continue;
            val[n - 1 - j] = d(val[n - 1 - j], a[j][n - 1 - j]);
        }
    }
    else {
        for (int j = 0; j < n; j++) {
            if ((mask & 1) && i - 2 == j || (mask & 2) && i - 2 + j == n - 1) continue;
            p = mul(p, a[i - 2][j]);
            val[j] = mul(val[j], a[i - 2][j]);
        }
        res = (res - mul(f(i + 1, mask | (1 << i)), p) + M) % M;
        for (int j = 0; j < n; j++) {
            if ((mask & 1) && i - 2 == j || (mask & 2) && i - 2 + j == n - 1) continue;
            val[j] = d(val[j], a[i - 2][j]);
        }
    }/*
    cout << "dp[" << i << "][";
    print(mask);
    cout << "] =  " << res << endl;*/
    return res;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //cout << fixed << setprecision(30);
    int _ = 1;
    //cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            val[i] = 1;
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    prod[j] = 1;
                }
                cin >> a[i][j];
                a[i][j] = d(a[i][j], 10000);
                prod[j] = mul(prod[j], a[i][j]);
            }
        }/*
        cout << "prod: ";
        for (int i = 0; i < n; i++) {
            cout << prod[i] << " ";
        }
        cout << endl;
        int x = 1;
        for (int i = 0; i < n; i++) {
            x = mul(x, (1 - prod[i] + M) % M);
        }
        cout << "x: " << x << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }*/
        cout << (M + 1 - f(0, 0)) % M << endl;
        // cout << f(0,0) * 512 % M << endl;
        // cout << f(4,2) * 512 % M << endl;
    }
}
