using namespace std; 

#include <iostream> 
#include <algorithm>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update> 

#define MAXN 1000005

int N,M,a[MAXN],b[MAXN],p[MAXN],s[MAXN],d[MAXN];
ordered_set os;
vector<int> v;

void solve(int l,int r,int x,int y) {
	if(l > r) return;
	int m = (l + r) >> 1;
	p[x] = s[y + 1] = 0;
	for(int i = x;i <= y;++i) {
		p[i + 1] = p[i] + (a[i] > b[m]);
	}
	for(int i = y;i >= x;--i) {
		s[i] = s[i + 1] + (a[i] < b[m]);
	}
	d[m] = x;
	for(int i = x;i <= y + 1;++i) {
		if(p[i] + s[i] < p[d[m]] + s[d[m]]) d[m] = i;
	}
	solve(l,m - 1,x,d[m] - 1);
	solve(m + 1,r,d[m],y);
}

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
	}
	for(int i = 0;i <= N;++i) {
		p[i] = s[i] = 0;
	}
	for(int i = 0;i < M;++i) {
		cin >> b[i];
	}
	sort(b,b + M);
	solve(0,M - 1,0,N - 1);
	v.clear();
	for(int i = 0,j = 0;i <= N;++i) {
		for(;j < M && d[j] <= i;++j) {
			v.push_back(b[j]);
		}
		if(i < N) v.push_back(a[i]);
	}
	long long ans = 0;
	os.clear();
	for(int i = 0;i < N + M;++i) {
		ans += os.size() - os.order_of_key({v[i] + 1,-1});
		os.insert({v[i],i});
	}
	cout << ans << "\n";
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