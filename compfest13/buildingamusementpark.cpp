using namespace std;

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAXN 100005
#define PI 3.1415926

int N,K,x[MAXN],y[MAXN];

int solve(double r) {
	int cnt = 0;
	vector<pair<double,int>> v;
	for(int i = 0;i < N;++i) {
		double d = sqrt(1ll * x[i] * x[i] + 1ll * y[i] * y[i]);
		if(d > 2 * r) continue;
		double th = acos(d / 2 / r);
		double an = atan2(y[i],x[i]);
		double l = an - th;
		double r = an + th;
		while(l < 0) l += 2 * PI;
		while(r < 0) r += 2 * PI;
		v.push_back({l,1});
		v.push_back({r,-1});
		if(l > r) cnt++;
	}
	int res = cnt;
	sort(v.begin(),v.end());
	for(auto p : v) res = max(res,cnt += p.second);
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> x[i] >> y[i];
	}
	double l = 0;
	double r = 2e5;
	for(int i = 0;i < 50;++i) {
		double m = (l + r) / 2;
		if(solve(m) >= K) {
			r = m;
		}else{
			l = m;
		}
	}
	cout << fixed << setprecision(10) << l << endl;
}