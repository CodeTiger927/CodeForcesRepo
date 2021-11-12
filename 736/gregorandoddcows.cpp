using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 6005

int N,x[MAXN],y[MAXN];
long long cnt[2][2];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> x[i] >> y[i];
		x[i] /= 2;
		y[i] /= 2;
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		memset(cnt,0,sizeof(cnt));
		for(int j = i + 1;j < N;++j) {
			int nx = abs(x[j] - x[i]);
			int ny = abs(y[j] - y[i]);
			if(nx == 0 && ny == 0) continue;
			cnt[nx & 1][ny & 1]++;
		}
		// gcd(a,b) + gcd(c,d) + gcd(a - c,b - d) = even
		// if a and c are both even
		// if a is even but c is odd, b is even, and d can be whatever
		// if a is odd and c is odd, b and d shares same parity
		ans += (cnt[0][0] + cnt[0][1]) * (cnt[0][0] + cnt[0][1] - 1) / 2;
		ans += (cnt[0][0] * (cnt[1][0] + cnt[1][1]));
		ans += (cnt[1][0] * (cnt[1][0] - 1) / 2) + (cnt[1][1] * (cnt[1][1] - 1) / 2);
	}
	cout << ans << endl;
	return 0;
}