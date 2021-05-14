using namespace std;

#include <iostream>
#include <vector>

int N;
vector<pair<int,int>> ans;

void solve(int l,int r) {
	int n = r - l + 1;
	if(n == 1) return;
	if((n & (n - 1)) == 0) {
		int m = (l + r) >> 1;
		solve(l,m);
		solve(m + 1,r);
		for(int i = l;i <= m;++i) {
			ans.push_back({i,i + (n >> 1)});
		}
		return;
	}
	int p = 1;
	while((p << 1) < n) p <<= 1;
	solve(l,l + p - 1);
	solve(r - p + 1,r);
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	solve(1,N);
	cout << ans.size() << "\n";
	for(int i = 0;i < ans.size();++i) {
		cout << ans[i].first << " " << ans[i].second << "\n";
	}
	return 0;
}