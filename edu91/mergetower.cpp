using namespace std;

#include <iostream>
#include <set>

#define MAXN 200005

int N,M,ans[MAXN];
set<int> s[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i) {
		int cur;
		cin >> cur;
		s[cur].insert(i);
	}
	int sum = 0;
	for(int i = 1;i <= M;++i) {
		for(auto itr = s[i].begin();next(itr) != s[i].end();++itr) {
			if(*next(itr) - *itr > 1) ans[i]++;
		}
		ans[i]++;
		sum += ans[i];
	}
	cout << sum - 1 << "\n";
	for(int i = 0;i < M - 1;++i) {
		int a,b;
		cin >> a >> b;
		sum -= ans[a] + ans[b];
		if(s[a].size() < s[b].size()) {
			swap(s[a],s[b]);
			swap(ans[a],ans[b]);
		}
		for(int x : s[b]) {
			auto itr = s[a].insert(x);
			bool pre = !!s[a].count(x - 1);
			bool nxt = !!s[a].count(x + 1);
			if(pre && nxt) {
				ans[a]--;
			}else if(!pre && !nxt) {
				ans[a]++;
			}
		}
		sum += ans[a];
		cout << sum - 1 << "\n";
	}
	return 0;
}