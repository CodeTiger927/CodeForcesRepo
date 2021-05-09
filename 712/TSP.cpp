using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

int N;
long long ans;
vector<pair<int,int>> v;

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		int a,b;
		cin >> a >> b;
		v.push_back({a,b});
		ans += b;
	}
	sort(v.begin(),v.end());
	long long m = v[0].first + v[0].second;
	for(int i = 1;i < N;++i) {
		ans += max(0ll,v[i].first - m);
		m = max(m,1ll * v[i].first + v[i].second);
	}
	cout << ans << endl;
	return 0;
}