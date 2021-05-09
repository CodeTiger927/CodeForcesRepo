using namespace std;

#include <iostream>

#define MAXN 200005
#define LOGN 20

long long st[MAXN][LOGN];
int N,M,Q,cnt[MAXN],pref[MAXN],arr[MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		cnt[--arr[i]]++;
	}
	for(int i = 1;i <= M;++i) {
		pref[i] = pref[i - 1] + cnt[i - 1];
	}
	for(int i = 1;i < LOGN;++i) {
		for(int j = 0;j < M;++j) {
			if(j + (1 << i) < M) {
				st[j][i] = st[j][i - 1] ^ st[j + (1 << (i - 1))][i - 1];
				if((pref[j + (1 << i)] - pref[j + (1 << (i - 1))]) & 1) st[j][i] ^= (1 << (i - 1));
			}
		}
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		int l,r;
		cin >> l >> r;
		l--;r--;
		long long res = 0;
		for(int i = LOGN - 1;i >= 0;--i) {
			if(l + (1 << i) <= r) {
				res ^= st[l][i];
				if((pref[r + 1] - pref[l + (1 << i)]) & 1) res ^= (1 << i);
				l += (1 << i);
			}
		}
		cout << "AB"[res == 0];
	}
	cout << endl;
	return 0;
}