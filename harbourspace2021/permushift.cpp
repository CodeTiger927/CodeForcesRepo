using namespace std;

#include <iostream>
#include <chrono>
#include <random>
#include <set>

using namespace chrono;

#define MAXN 300005

mt19937 rng(high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<long long unsigned> distribution(0,1e9);

int N,M,arr[MAXN],arr2[MAXN],tmp[MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		arr[i]--;
		tmp[i] = 0;
	}
	set<int> ans;
	for(int i = 0;i < 100;++i) {
		int cur = distribution(rng) % N;
		int shift = (cur + N - arr[cur]) % N;
		if(ans.count(shift)) {
			continue;
		}
		for(int j = 0;j < N;++j) {
			tmp[arr[j]] = j;
			arr2[j] = arr[j];
		}
		int cnt = 0;
		for(int j = 0;j < N;++j) {
			int need = (N + j - shift) % N;
			if(need != arr2[j]) {
				cnt++;
				int nxt = tmp[need];
				swap(tmp[arr2[j]],tmp[need]);
				swap(arr2[j],arr2[nxt]);
			}
		}
		if(cnt <= M) {
			ans.insert(shift);
		}
	}
	cout << ans.size();
	for(int k : ans) {
		cout << " " << k;
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}