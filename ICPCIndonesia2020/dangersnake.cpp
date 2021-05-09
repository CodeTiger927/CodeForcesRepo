using namespace std;

#include <iostream>

#define MAXN 2005
#define MOD 1000000007

int N,M,R,x[MAXN],y[MAXN],pref[MAXN][MAXN];
long long arr[MAXN],fact[MAXN],invf[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long choose(long long a,long long b) {
	if(a < b) return 0;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

long long getSum(int x1,int x2,int y1,int y2) {
	if(x1 > x2 || y1 > y2) return 0ll;
	x1 = max(x1,1);
	y1 = max(y1,1);
	x2 = min(x2,1000);
	y2 = min(y2,1000);
	return max(0,pref[x2][y2] - pref[x2][y1 - 1] - pref[x1 - 1][y2] + pref[x1 - 1][y1 - 1]);
}

long long getKillNum(int x,int y) {
	return getSum(x - R,x + R,y - R,y + R);
}

int main() {
	cin >> N >> M >> R;
	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (i * fact[i - 1]) % MOD;
		invf[i] = inv(fact[i]);
	}
	for(int i = 0;i < N;++i) {
		cin >> x[i] >> y[i] >> arr[i];
		pref[x[i]][y[i]]++;
	}
	for(int i = 1;i <= 1000;++i) {
		for(int j = 1;j <= 1000;++j) {
			pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
		}
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			long long cnt = 0;
			int x1 = max(x[i],x[j]) - R;
			int x2 = min(x[i],x[j]) + R;
			int y1 = max(y[i],y[j]) - R;
			int y2 = min(y[i],y[j]) + R;

			long long both = getSum(x1,x2,y1,y2);
			cnt += choose(N,M) - choose(N - both,M);
			if(cnt < 0) cnt += MOD;

			long long a = getKillNum(x[i],y[i]) - both;
			long long b = getKillNum(x[j],y[j]) - both;
			cnt += (2ll * MOD + choose(N - both,M) - choose(N - both - a,M) - choose(N - both - b,M) + choose(N - both - a - b,M)) % MOD;
			if(cnt >= MOD) cnt -= MOD;

			ans += 1ll * (cnt * arr[i] % MOD) * arr[j] % MOD;
			if(ans >= MOD) ans -= MOD;
		}
	}
	cout << ans << endl;
	return 0;
}