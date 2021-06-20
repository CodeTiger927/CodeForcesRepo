using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,M;
long long target[MAXN];
vector<int> edges[MAXN];
bool d[MAXN],vis[MAXN];

void dfs(int v) {
	if(vis[v]) return;
	vis[v] = true;
	for(int u : edges[v]) {
		if(vis[u]) continue;
		d[u] = d[v] ^ 1;
		dfs(u);
	}
	return;
}

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		edges[i].clear();
		d[i] = vis[i] = false;
	}
	for(int i = 0;i < N;++i) {
		cin >> target[i];
	}
	long long sum = 0;
	for(int i = 0;i < N;++i) {
		long long cur;
		cin >> cur;
		target[i] = cur - target[i];
		sum += target[i];
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	if(abs(sum) % 2 == 1) {
		cout << "NO" << endl;
		return;
	}
	dfs(0);
	long long odd_sum = 0;
	long long even_sum = 0;
	for(int i = 0;i < N;++i) {
		for(int u : edges[i]) {
			if(d[i] == d[u]) {
				cout << "YES" << endl;
				return;
			}
		}
		if(d[i]) {
			odd_sum += target[i];
		}else{
			even_sum += target[i];
		}
	}
	if(odd_sum == even_sum) {
		cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
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