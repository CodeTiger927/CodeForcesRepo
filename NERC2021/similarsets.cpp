using namespace std;

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>

#define MAXN 100005

int N,last[2 * MAXN];
vector<int> vs[MAXN],id;
vector<pair<int,int>> pairs[2 * MAXN];

void solve() {
	id.clear();
	cin >> N;
	const int sn = 400;
	for(int i = 0;i < N;++i) {
		int k;
		cin >> k;
		vs[i].resize(k);
		for(int j = 0;j < k;++j) {
			cin >> vs[i][j];
			id.push_back(vs[i][j]);
		}
	}
	sort(id.begin(),id.end());
	id.erase(unique(id.begin(),id.end()),id.end());
	for(int i = 0;i < N;++i) {
		for(int& j : vs[i]) {
			j = lower_bound(id.begin(),id.end(),j) - id.begin();
		}
	}
	for(int i = 0;i < id.size();++i) {
		last[i] = 0;
		pairs[i].clear();
	}

	for(int i = 0;i < N;++i) {
		if(vs[i].size() < sn) {
			for(int j : vs[i]) {
				for(int k : vs[i]) {
					if(j < k) pairs[j].push_back({k,i});
				}
			}
		}else{
			for(int j : vs[i]) last[j] = 1;
			for(int j = 0;j < N;++j) {
				if(i == j) continue;
				int x = 0;
				for(int k : vs[j]) {
					x += last[k];
				}
				if(x > 1) {
					cout << (i + 1) << " " << (j + 1) << "\n";;
					return;
				}
			}
			for(int j : vs[i]) last[j] = 0;
		}
	}
	for(int i = 0;i < id.size();++i) {
		for(pair<int,int> j : pairs[i]) {
			if(last[j.first]) {
				cout << last[j.first] << " " << (j.second + 1) << "\n";;
				return;
			}
			last[j.first] = j.second + 1;
		}
		for(pair<int,int> j : pairs[i]) {
			last[j.first] = 0;
		}
	}
	cout << -1 << "\n";
	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while(T--) solve();
}