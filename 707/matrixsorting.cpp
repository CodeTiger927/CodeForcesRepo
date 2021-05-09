using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#define MAXN 1505

int inv[MAXN],a[MAXN][MAXN],rev[MAXN],b[MAXN][MAXN],p[MAXN],N,M;
bool cut[MAXN];
vector<int> flip[MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> a[i][j];
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> b[i][j];
		}
	}
	vector<int> que;
	for(int j = 0;j < M;++j) {
		for(int i = 0;i < N - 1;++i) {
			if(b[i][j] > b[i + 1][j]) {
				inv[j]++;
				flip[i].push_back(j);
			}
		}
		if(inv[j] == 0) {
			que.push_back(j);
		}
	}
	for(int i = 0;i < que.size();++i) {
		int cur = que[i];
		for(int j = 0;j < N - 1;++j) {
			if(!cut[j] && b[j][cur] < b[j + 1][cur]) {
				cut[j] = true;
				for(auto v : flip[j]) {
					inv[v]--;
					if(inv[v] == 0) {
						que.push_back(v);
					}
				}
			}
		}
	}
	reverse(que.begin(),que.end());
	iota(p,p + N,0);
	for(int i = 0;i < que.size();++i) {
		for(int j = 0;j < N;++j) {
			rev[p[j]] = j;
		}
		auto cmp = [&](int x,int y) {
			if(a[x][que[i]] == a[y][que[i]]) {
				return rev[x] < rev[y];
			}
			return a[x][que[i]] < a[y][que[i]];
		};
		sort(p,p + N,cmp);
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			if(b[i][j] != a[p[i]][j]) {
				cout << -1 << endl;
				return 0;
			}
		}
	}
	cout << que.size() << endl;
	for(int i = 0;i < que.size();++i) {
		cout << (que[i] + 1) << " ";
	}
	cout << endl;
	return 0;
}