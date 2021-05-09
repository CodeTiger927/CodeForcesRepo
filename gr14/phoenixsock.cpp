using namespace std;

#include <iostream>

#define MAXN 200005

int N,L,R,cntL[MAXN],cntR[MAXN],cnt[MAXN];

void solve() {
	cin >> N >> L >> R;
	for(int i = 1;i <= N;++i) {
		cntL[i] = cntR[i] = cnt[i] = 0;
	}
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		if(i < L) {
			cntL[cur]++;
		}else{
			cntR[cur]++;
		}
	}
	if(R > L) {
		for(int i = 1;i <= N;++i) {
			swap(cntL[i],cntR[i]);
		}
		swap(L,R);
	}
	int K = (L - R) / 2;
	int ans = 0;
	for(int i = 1;i <= N;++i) {
		cnt[i] = cntL[i] - cntR[i];
		if(cnt[i] > 0) {
			int n = min(K,cnt[i] / 2);
			K -= n;
			cnt[i] -= 2 * n;
		}
		ans += abs(cnt[i]);
	}
	ans += (L - R);
	ans /= 2;
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}