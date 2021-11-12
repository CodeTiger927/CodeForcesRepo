using namespace std;

#include <iostream>
#include <vector>
#include <assert.h>

#define MAXN 1000005
#define MAXM 8192

int N,a[MAXN],b[MAXM],ans[MAXM];
vector<int> g[MAXM];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < MAXM;++i) {
		g[i].push_back(0);
		b[i] = MAXM;
	}
	ans[0] = 1;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
		for(int j : g[a[i]]) {
			int n = a[i] ^ j;
			if(n >= MAXM) continue;
			ans[n] = 1;
			while(b[n] > 0 && b[n] > a[i]) {
				g[--b[n]].push_back(n);
			}
		}
		g[a[i]].clear();
	}
	int cnt = 0;
	for(int i = 0;i < MAXM;++i) cnt += ans[i];
	cout << cnt << endl;
	for(int i = 0;i < MAXM;++i) {
		if(ans[i]) cout << i << " ";
	}
	cout << endl;
	return 0;
}