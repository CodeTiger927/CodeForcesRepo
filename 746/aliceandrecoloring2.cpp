using namespace std;

#include <iostream>
#include <cstring>
#include <vector>
#include <cstring>

#define MAXN 505

int N,M,a[MAXN][MAXN],b[MAXN][MAXN],mt[MAXN];
bool used[MAXN];
vector<int> edges[MAXN];

bool try_kuhn(int v) {
	if(used[v]) return false;
	used[v] = true;
	for(int u : edges[v]) {
		if(mt[u] == -1 || try_kuhn(mt[u])) {
			mt[u] = v;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		string s;
		cin >> s;
		for(int j = 0;j < M;++j) {
			a[i][j] = (s[j] == 'B');
		}
	}
	int ans = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			b[i][j] = (a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1]) & 1;
			ans += b[i][j];
		}
	}
	for(int i = 0;i < N - 1;++i) {
		for(int j = 0;j < M - 1;++j) {
			if(b[i][j] && b[i][M - 1] && b[N - 1][j]) {
				edges[i].push_back(j);
			}
		}
	}
	int k = 0;
	memset(mt,-1,sizeof(mt));
	for(int i = 0;i < N;++i) {
		memset(used,0,sizeof(used));
		try_kuhn(i);
	}
	for(int i = 0;i < M;++i) k += mt[i] != -1;
	if(k & 1) {
		ans += b[N - 1][M - 1] ? -1 : 1;
	}
	cout << (ans - k) << endl;
	return 0;
}