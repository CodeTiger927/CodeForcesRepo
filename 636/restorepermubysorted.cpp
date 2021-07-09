using namespace std;

#include <iostream>
#include <set>
#include <vector>

#define MAXN 205

int N;
set<int> ins[MAXN];
vector<int> vs[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		vs[i].clear();
		int k;
		cin >> k;
		for(int j = 0;j < k;++j) {
			int c;
			cin >> c;
			vs[i].push_back(c);
		}
	}
	for(int i = 1;i <= N;++i) {
		vector<int> ans = {i};
		for(int j = 0;j < N - 1;++j) {
			ins[j].clear();
			for(int c : vs[j]) ins[j].insert(c);
		}
		int lastEle = i;
		for(int j = 0;j < N - 1;++j) {
			int len1 = -1;
			for(int k = 0;k < N - 1;++k) {
				ins[k].erase(lastEle);
				if(ins[k].size() == 1) {
					if(len1 == -1) {
						len1 = k;
					}else{
						len1 = -2;
						break;
					}
				}
			}
			if(len1 == -2 || len1 == -1) break;
			lastEle = *ins[len1].begin();
			ans.push_back(lastEle);
		}

		
		if(ans.size() != N) continue;
		set<set<int>> all;
		for(int i = 0;i < N - 1;++i) all.insert(set<int>(vs[i].begin(),vs[i].end()));

		bool ok = true;
		for(int i = 1;i < N;++i) {
			set<int> seg = {ans[i]};
			bool found = false;
			for(int j = i - 1;j >= 0;--j) {
				seg.insert(ans[j]);
				if(all.count(seg)) {
					found = true;
					all.erase(seg);
					break;
				}
			}
			ok &= found;
		}
		if(ok) {
			for(int c : ans) cout << c << " ";
			cout << endl;
			return;
		}
	}
	cout << "Fail" << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}