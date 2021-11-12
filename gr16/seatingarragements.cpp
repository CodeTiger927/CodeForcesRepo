using namespace std;

#include <iostream>
#include <set>
#include <algorithm>

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
#define MAXN 305

int N,M;
vector<pair<int,int>> rows[MAXN],v;

void solve() {
	cin >> N >> M;
	// cout << N << " " << M << endl;
	v.clear();
	for(int i = 0;i < N;++i) {
		rows[i].clear();
	}
	for(int i = 0,t = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			int cur;
			cin >> cur;
			v.push_back({cur,t++});
		}
	}
	sort(v.begin(),v.end());
	long long ans = 0;
	for(int i = 0,t = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			rows[i].push_back(v[t++]);
		}
		sort(rows[i].begin(),rows[i].end(),[&](pair<int,int> a,pair<int,int> b) {return a.second < b.second;});
		ordered_set os;
		for(int j = 0;j < M;++j) {
			ans += os.order_of_key(make_pair(rows[i][j].first,0));
			os.insert(rows[i][j]);
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}