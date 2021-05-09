using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

pair<int,int> pts[4];

pair<int,int> minmax(pair<int,int> o) {
	return {min(o.first,o.second),max(o.first,o.second)};
}

pair<int,int> range(pair<int,int> a,pair<int,int> b) {
	return {max({0,a.first - b.second,b.first - a.second}),max({0,a.second - b.first,b.second - a.first})};
}

void solve() {
	long long ans = 1e18;
	for(int i = 0;i < 4;++i) {
		cin >> pts[i].first >> pts[i].second;
	}
	vector<int> p = {0,1,2,3};
	do {
		long long cur = 0;
		auto x1 = minmax(pts[p[0]].first,pts[p[1]].first);
		auto x2 = minmax(pts[p[2]].first,pts[p[3]].first);
		cur += (x1.second - x1.first) + (x2.second - x2.first);
		auto segX = range(x1,x2);

		auto y1 = minmax(pts[p[0]].second,pts[p[3]].second);
		auto y2 = minmax(pts[p[1]].second,pts[p[2]].second);
		cur += (y1.second - y1.first) + (y2.second - y2.first);
		auto segY = range(y1,y2);

		cur += 2 * max(0,max(segX.first,segY.first) - min(segX.second,segY.second));
		ans = min(ans,cur);
	}while(next_permutation(p.begin(),p.end()));
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}