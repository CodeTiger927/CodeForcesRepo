using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 2005
#define MAXM 4000005

int N,M,dep[MAXM],out[MAXM],td[MAXM],inzh[MAXM],f,ans;
bool inCycle[MAXM],used[MAXM];

int c2n(int i,int j) {
	return i * M + j;
}

void dfs(int x,int p) {
	if(dep[x]) return;
	inzh[x] = 1;
	td[x] = 1;
	dep[x] = (p == -1 ? 0 : dep[p]) + 1;
	if(~out[x]) {
		if(inzh[out[x]]) {
			f = out[x];
			td[x] = dep[x] - dep[out[x]] + 1;
		}else{
			dfs(out[x],x);
			if(~f) {
				// cout << f << endl;
				td[x] = td[out[x]];
			}else{
				td[x] = td[out[x]] + 1;
			}
			if(f == x) f = -1;
		}
	}
	inzh[x] = 0;
	if(td[x] > td[ans]) ans = x;
	return;
}

void solve() {
	ans = 0;
	f = -1;
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			out[c2n(i,j)] = -1;
			dep[c2n(i,j)] = td[c2n(i,j)] = 0;
			char c;
			cin >> c;
			int x = i;
			int y = j;
			if(c == 'L') y--;
			if(c == 'R') y++;
			if(c == 'D') x++;
			if(c == 'U') x--;
			if(x >= 0 && x < N && y >= 0 && y < M) {
				out[c2n(i,j)] = (c2n(x,y));
			}
		}
	}
	for(int i = 0;i < N * M;++i) {
		if(!dep[i]) dfs(i,-1);
	}
	int x = ans / M + 1;
	int y = ans % M + 1;
	cout << x << " " << y << " " << td[ans] << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}