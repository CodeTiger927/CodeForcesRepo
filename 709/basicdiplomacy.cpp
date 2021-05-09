using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005

int N,M,ans[MAXN],cnt[MAXN];
vector<int> v[MAXN];

void solve() {
	int N,M;
	cin >> N >> M;
	int lim = (M + 1) / 2;
	for(int i = 1;i <= N;++i) {
		cnt[i] = 0;
	}
	for(int i = 0;i < M;++i) {
		int k;
		cin >> k;
		v[i].clear();
		for(int j = 0;j < k;++j) {
			int cur;
			cin >> cur;
			v[i].push_back(cur);
		}
	}
	for(int i = 0;i < M;++i) {
		if(v[i].size() == 1) {
			ans[i] = v[i][0];
			cnt[v[i][0]]++;
			if(cnt[v[i][0]] > lim) {
				cout << "NO" << endl;
				return;
			}
		}
	}
	for(int i = 0;i < M;++i) {
		if(v[i].size() != 1) {
			if(cnt[v[i][0]] + 1 > lim) {
				ans[i] = v[i][1];
				cnt[v[i][1]]++;
			}else{
				ans[i] = v[i][0];
				cnt[v[i][0]]++;
			}
		}
	}

	for(int i = 1;i <= N;++i) {
		if(cnt[i] > lim) {
			cout << "NO" << endl;
			return;
		}
	}
	cout << "YES" << endl;
	for(int i = 0;i < M;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}