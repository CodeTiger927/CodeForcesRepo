using namespace std;

#include <iostream>
#include <array>
#include <vector>

#define MAXN 1005

int N,M,ans[MAXN][MAXN];
string str;
vector<array<int,3>> pts;
array<int,3> p0,d;

void solve() {
	pts.clear();
	cin >> N >> M;
	p0 = {0,0,0};
	d = {0,1,2};

	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			int cur;
			cin >> cur;
			cur--;
			pts.push_back({i,j,cur});
		}
	}
	cin >> str;
	for(int i = 0;i < M;++i) {
		if(str[i] == 'R') {
			p0[d[1]] = (p0[d[1]] + 1) % N;
		}else if(str[i] == 'L') {
			p0[d[1]] = (p0[d[1]] - 1 + N) % N;
		}else if(str[i] == 'D') {
			p0[d[0]] = (p0[d[0]] + 1) % N;
		}else if(str[i] == 'U') {
			p0[d[0]] = (p0[d[0]] - 1 + N) % N;
		}else if(str[i] == 'I') {
			swap(d[1],d[2]);
		}else{
			swap(d[0],d[2]);
		}
	}
	for(int i = 0;i < pts.size();++i) {
		array<int,3> c = {(pts[i][0] + p0[0]) % N,(pts[i][1] + p0[1]) % N,(pts[i][2] + p0[2]) % N};
		ans[c[d[0]]][c[d[1]]] = c[d[2]] + 1;
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}