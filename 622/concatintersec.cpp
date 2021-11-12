using namespace std;

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 500005

int N,M;
string a,b,c;

string rev(string a) {
	reverse(a.begin(),a.end());
	return a;
}

struct bit {
	long long bit[MAXN];
	void upd(int x,long long v) {
		x++;
		while(x < MAXN) {
			bit[x] += v;
			x += x & -x;
		}
		return;
	}
	long long get(int x) {
		x++;
		long long res = 0;
		while(x) {
			res += bit[x];
			x -= x & -x;
		}
		return res;
	}
} cnt,sum;

vector<int> z_func(const string& s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for(int i = 1;i < n; ++i) {
		z[i] = i >= r ? 0 : min(z[i - l], r - i);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
			++z[i];
		}
		if(i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

int main() {
	cin >> N >> M >> a >> b >> c;
	auto pre = z_func(c.substr(0,M - 1) + "#" + a);
	auto suf = z_func(rev(c.substr(1,M)) + "#" + rev(b));
	pre.erase(pre.begin(),pre.begin() + M);
	suf.erase(suf.begin(),suf.begin() + M);
	reverse(suf.begin(),suf.end());
	long long ans = 0;
	for(int i = 2 - M;i < N;++i) {
		if(i + M - 2 < N) {
			int cur = M - 1 - suf[i + M - 2];
			cnt.upd(cur,1);
			sum.upd(cur,cur);
		}
		if(i >= 0) {
			ans += pre[i] * cnt.get(pre[i]) - sum.get(pre[i]);
			int cur = M - 1 - suf[i];
			cnt.upd(cur,-1);
			sum.upd(cur,-cur);
		}
	}
	cout << ans << endl;
	return 0;
}