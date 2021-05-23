using namespace std;

#include <iostream>
#include <vector>
#include <set>

#define MAXN 200005

int N,l[MAXN],r[MAXN],t[MAXN];
set<pair<int,pair<bool,int>>> upd;
set<pair<int,int>> s[2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> l[i] >> r[i] >> t[i];
		t[i]--;
		upd.insert({l[i],{0,i}});
		upd.insert({r[i],{1,i}});
	}
	int ans = 0;
	for(auto p : upd) {
		int i = p.second.second;
		if(p.second.first) {
			int j = t[i];
			int k = !t[i];
			if(s[j].count({r[i],i}) && !s[k].empty()) {
				ans++;
				s[k].erase(s[k].begin());
			}
			if(s[j].count({r[i],i})) s[j].erase(make_pair(r[i],i));
		}else{
			s[t[i]].insert({r[i],i});
		}
	}
	cout << N - ans << endl;
	return 0;
}