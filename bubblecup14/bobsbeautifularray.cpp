using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 1005

int N,M,a[MAXN],s1,s2,dp[(int)1.4e7];
vector<int> v[2],ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
		v[a[i] & 1].push_back(a[i]);
	}
	sort(a,a + N);
	if(unique(a,a + N) - a != N) {
		cout << "YES" << endl << 0;
		for(int i = 0;i < N - 1;++i) {
			cout << " " << a[i];
		}
		cout << endl;
		return 0;
	}
	if(!v[0].empty()) {
		vector<int> f;
		if(v[0].size() >= 3) {
			f = {v[0][0],v[0][1],v[0][2]};
		}else if(v[1].size() >= 2) {
			f = {v[0][0],v[1][0],v[1][1]};
		}else{
			cout << "NO" << endl;
			return 0;
		}
		cout << "YES" << endl;
		int x = (f[0] + f[1] - f[2]) / 2;
		int y = (f[0] + f[2] - f[1]) / 2;
		int z = (f[1] + f[2] - f[0]) / 2;
		cout << x << " " << y << " " << z;
		for(int i = 0;i < N;++i) {
			if(a[i] != f[0] && a[i] != f[1] && a[i] != f[2]) cout << " " << (a[i] - x);
		}
		cout << endl;
		return 0;
	}
	M = min(N,26);
	s1 = s2 = -1;
	for(int i = 0;i < (1 << M);++i) {
		if(__builtin_popcount(i) != M / 2) continue;
		int s = 0;
		for(int j = 0;j < M;++j) {
			if(i & (1 << j)) s += v[1][j];
		}
		if(dp[s]) {
			s1 = dp[s];
			s2 = i;
			break;
		}
		dp[s] = i;
	}
	if(s1 == -1) {
		cout << "NO" << endl;
		return 0;
	}
	int ss = s1 & s2;
	s1 ^= ss;
	s2 ^= ss;
	vector<int> v1,v2,ff;
	for(int i = 0;i < M;++i) {
		if(s1 & (1 << i)) v1.push_back(v[1][i]);
		if(s2 & (1 << i)) v2.push_back(v[1][i]);
	}
	for(int i = 0;i < v1.size();++i) {
		ff.push_back(v1[i]);
		ff.push_back(v2[i]);
	}
	ans.push_back(0);
	for(int i = 1;i < ff.size();++i) {
		ans.push_back(ff[i - 1] - ans.back());
	}
	for(int i = 0;i < N;++i) {
		if(i >= M || (1 << i) & ~(s1 | s2)) {
			ans.push_back(v[1][i]);
		}
	}
	cout << "YES" << endl;
	for(int i = 0;i < N;++i) {
		cout << ans[i] << " \n"[i == N - 1];
	}
	return 0;
}