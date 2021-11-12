using namespace std;

#include <iostream>
#include <map>
#include <vector>

#define MAXN 500005
#define MOD 998244353

int N,M;
long long arr[MAXN];
map<long long,long long> m;
vector<int> edges[MAXN];

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

void solve() {
	cin >> N >> M;
	m.clear();
	for(int i = 1;i <= N;++i) {
		edges[i].clear();
		cin >> arr[i];
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		edges[b].push_back(a);
	}
	for(int i = 1;i <= N;++i) {
		if(edges[i].size() == 0) continue;
		long long cur = 0;
		for(int j : edges[i]) {
			cur ^= (j * 2950122451ll);
		}
		m[cur] += arr[i];
	}
	long long ans = 0;
	for(auto a : m) {
		ans = gcd(ans,a.second);
	}
	cout << ans << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}