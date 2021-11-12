using namespace std;

#include <iostream>

#define MOD 1000000007
#define MAXN 200005
#define MAXK 55

int N,Q,K1 = 3,K2 = 2;
long long arr[MAXN],choose[MAXN][MAXK],sum[MAXN][MAXK],sum2[MAXN][MAXK];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long pow(long long x,long long y) {
	if(y == 0) return 1;
	if(y == 1) return x;
	long long res = pow(x,y >> 1);
	if(y & 1) {
		return x * (res * res % MOD) % MOD;
	}
	return res * res % MOD;
}

long long P(long long x,long long n,long long K) {
	long long res = 0;
	for(int i = 0;i <= K;++i) {
		res += (sum2[n - 1][i] * choose[K][i] % MOD) * pow(x,i) % MOD;
		if(res >= MOD) res -= MOD;
	}
	return res;
}

long long findInit(long long s,long long d,long long n) {
	return (MOD + (s * 2ll * inv(n) % MOD) % MOD - (n - 1) * d % MOD) * inv(2) % MOD;
}

long long getSum(int a,int b,long long K) {
	return (MOD + sum[b + 1][K] - sum[a][K]) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	for(int i = 0;i <= N;++i) {
		choose[i][0] = 1;
		for(int j = 1;j <= min(i,5);++j) choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % MOD;
	}
	sum2[0][0] = 1;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		for(int j = 0;j <= 5;++j) {
			sum[i + 1][j] = sum[i][j] + pow(arr[i],j);
			sum2[i + 1][j] = sum2[i][j] + pow(i + 1,j);
			if(sum[i][j] >= MOD) sum[i][j] -= MOD;
			if(sum2[i][j] >= MOD) sum2[i][j] -= MOD;
		}
	}
	for(int i = 0;i < Q;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		int n = b - a + 1;
		long long s1 = getSum(a,b,K1);
		long long s2 = getSum(a,b,K2);
		long long init = findInit((sum[b + 1][1] - sum[a][1] + MOD) % MOD,c,b - a + 1);
		long long s3 = init == 0 ? (sum2[n - 1][K1] * pow(c,K1) % MOD) : pow(init,K1) * P(1ll * c * inv(init) % MOD,n,K1) % MOD;
		long long s4 = init == 0 ? (sum2[n - 1][K2] * pow(c,K2) % MOD) : pow(init,K2) * P(1ll * c * inv(init) % MOD,n,K2) % MOD;
		cout << (s1 == s3 && s2 == s4 ? "Yes" : "No") << "\n";
	}
	return 0;
}