using namespace std;

#include <iostream>
#include <vector>

#define MAXN 15

int N,Q,arr[MAXN];
long long fact[MAXN];

void findPermu(long long x) {
	vector<int> v;
	for(int i = 0;i < min(MAXN,N);++i) {
		v.push_back(max(0,N - MAXN) + i + 1);
	}
	for(int i = 0;i < min(MAXN,N);++i) {
		int cur = x / fact[min(MAXN,N) - i - 1];
		x %= fact[min(MAXN,N) - i - 1];
		arr[i] = v[cur];
		v.erase(v.begin() + cur);
	}
	return;
}

int main() {
	long long sum = 0;
	cin >> N >> Q;
	arr[0] = fact[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = fact[i - 1] * i;
		arr[i] = i + 1;
	}
	if(N > MAXN) {
		for(int i = 0;i < MAXN;++i) {
			arr[i] = i + 1 + (N - MAXN);
		}
	}
	int counter = 0;
	for(int i = 0;i < Q;++i) {
		int a;
		cin >> a;
		if(a == 1) {
			int l,r;
			cin >> l >> r;
			l--;r--;
			long long ans = 0;
			if(N <= MAXN) {
				for(int j = l;j <= r;++j) ans += arr[j];
			}else{
				if(l < (N - MAXN)) {
					long long ri = min(r,N - MAXN - 1);
					ans += 1ll * (l + ri + 2) * (ri - l + 1) / 2;
				}
				if(r >= (N - MAXN)) {
					long long le = max(l,N - MAXN);
					for(int j = le - N + MAXN;j <= r - N + MAXN;++j) {
						ans += arr[j];
					}
				}
			}
			cout << ans << endl;
		}else{
			long long x;
			cin >> x;
			sum += x;
			findPermu(sum);
		}
	}
}