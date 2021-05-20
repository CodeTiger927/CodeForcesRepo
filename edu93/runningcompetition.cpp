using namespace std;

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>

#define MAXN 200005
#define MOD 998244353


long long modpow(long long n,long long e) {
    long long res = 1;
    while (e) {
        if (e & 1) res = res * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}

struct ntt {
    const int logn = 20;
    const int sz = 1 << logn;
    const long long g = 3;
    vector<vector<long long>> w;
    vector<vector<long long>> invw;
    vector<vector<int>> rev;
    ntt() {
        long long wpow = modpow(g, (MOD - 1) / (1 << logn));
        w.resize(logn + 1);
        invw.resize(logn + 1);
        rev.resize(logn + 1);
        for (int i = 0; i < logn; i++) {
            w[i].resize(1 << i);
            invw[i].resize(1 << i);
            rev[i].resize(1 << i);
            long long m = modpow(wpow, (1 << (logn - i - 1)));
            long long invm = modpow(m, MOD - 2);
            w[i][0] = 1;
            invw[i][0] = 1;
            for (int j = 1; j < (1 << i); j++) {
                w[i][j] = w[i][j - 1] * m % MOD;
                invw[i][j] = invw[i][j - 1] * invm % MOD;
            }
            if (i == 0) continue;
            for (int j = 1, k = 0; j < (1 << i); j++) {
                int bit = 1 << (i - 1);
                for (; k & bit; bit /= 2) k ^= bit;
                k ^= bit;
                if (j < k) rev[i][j] = k;
            }
        }
    }
    void ntt_calc(vector<long long> &a, int ln, int n, bool invert) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            if (i < rev[ln][i]) swap(a[i], a[rev[ln][i]]);
        }
        for (int i = 1; i <= ln; i++) {
            int len = 1 << i;
            for (int j = 0; j < n; j += len) {
                for (int k = 0; k < len / 2; k++) {
                    long long mul = invert ? invw[i - 1][k] : w[i - 1][k];
                    long long u = a[j + k];
                    long long v = a[j + k + len / 2] * mul % MOD;
                    a[j + k] = (u + v) % MOD;
                    a[j + k + len / 2] = (u - v + MOD) % MOD;
                }
            }
        }
        if (invert) {
            long long inv = modpow(n, MOD - 2);
            for (int i = 0; i < n; i++) {
                a[i] = a[i] * inv % MOD;
            }
        }
    }
    void mul(vector<long long> &a, vector<long long> &b, vector<long long> &c) {
        int n = 1;
        int ln = 0;
        while (n < (a.size() + b.size())) {
            n *= 2;
            ln++;
        }
        a.resize(n);
        b.resize(n);
        c.resize(n);
        ntt_calc(a, ln, n, false);
        ntt_calc(b, ln, n, false);
        for (int i = 0; i < n; i++) {
            c[i] = a[i] * b[i] % MOD;
        }
        ntt_calc(c, ln, n, true);
    }
};


ntt NTT;

int N,Q,X,Y,arr[MAXN],dp[MAXN],ans[(int)5e5 + 5];
vector<long long> A,B,C;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> X >> Y;
    A = vector<long long>(X + 1,0);
    B = vector<long long>(X + 1,0);

    memset(ans,-1,sizeof(ans));

    for(int i = 0;i < N + 1;++i) {
        cin >> arr[i];
        A[arr[i]] = 1;
        B[X - arr[i]] = 1;
    }
    NTT.mul(A,B,C);

    for(int i = X + 1;i < C.size();++i) {
        if(C[i]) {
            int cur = i - X + Y;
            for(int j = cur;j < (int)5e5 + 5;j += cur) {
                if(ans[j] == -1) {
                    ans[j] = 2 * cur;
                }else{
                    ans[j] = max(ans[j],2 * cur);
                }
            }
        }
    }
    cin >> Q;
    for(int i = 0;i < Q;++i) {
        int x;
        cin >> x;
        cout << ans[x / 2] << " ";
    }
    cout << endl;
	return 0;
}