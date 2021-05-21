using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005
#define LOG 19

int N,dep[MAXN],sz[MAXN],par[MAXN][LOG],tin[MAXN],tout[MAXN],pos[MAXN],t;
vector<int> edges[MAXN];
long long ans[MAXN];

void dfs(int v) {
	sz[v] = 1;
	tin[v] = t++;
	for(int u : edges[v]) {
		if(u == par[v][0]) continue;
		par[u][0] = v;
		dep[u] = dep[v] + 1; 
		dfs(u);
		sz[v] += sz[u];
	}
	tout[v] = t;
	return;
}

int LCA(int u,int v) {
	if(dep[v] < dep[u]) return LCA(v,u);
	int dif = dep[v] - dep[u];
	for(int i = 0;i < LOG;i++) {
		if((dif >> i) & 1) {
			v = par[v][i];
		}
	}
	if(u == v) {
		return u;
	}
	for(int i = LOG - 1;i >= 0;i--) {
		if(par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int top(int v) {
	for(int i = LOG - 1;i >= 0;--i) {
		if(par[v][i]) {
			v = par[v][i];
		}
	}
	return v;
}

bool isAnc(int x,int y) {
	if(tin[y] >= tin[x] && tin[y] < tout[x]) return true;
	return false;
}

bool onPath(int x,int y,int v) {
	if(isAnc(x,y)) {
		return (isAnc(x,v) && isAnc(v,y));
	}
	int a = LCA(x,y);
	return (isAnc(a,v) && (isAnc(v,x) || isAnc(v,y)));
}

bool across = false;

void solve() {
	cin >> N;
	for(int i = 0;i <= N;++i) {
		edges[i].clear();
		par[i][0] = 0;
		ans[i] = 0;
	}
	across = false;
	ans[0] = 1ll * N * (N - 1) / 2;
	t = 0;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	for(int i = 1;i < LOG;++i) {
		for(int j = 0;j < N;++j) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
	ans[1] = ans[0];
	for(int v : edges[0]) {
		ans[1] -= 1ll * sz[v] * (sz[v] - 1) / 2;
	}
	int h1 = 0;
	int h2 = 0;
	for(int i = 1;i < N;++i) {
		if(!onPath(h1,h2,i)) {
			if(across) {
				if(isAnc(h1,i)) {
					h1 = i;
				}else if(isAnc(h2,i)) {
					h2 = i;
				}else{
					break;
				}
			}else{
				// h1 is always ancestor
				if(isAnc(i,h1)) {
					h1 = i;
				}else if(isAnc(h2,i)) {
					h2 = i;
				}else{
					if(LCA(i,h2) == h1) {
						across = true;
						h1 = i;
					}else{
						break;
					}
				}
			}
		}
		// cout << i << " " << h1 << " " << h2 << " " << across << endl;
		if(across) {
			ans[i + 1] = 1ll * sz[h1] * sz[h2];
		}else{
			if(h1 == 0) {
				ans[i + 1] = 1ll * (N - sz[top(h2)]) * sz[h2];
			}else{
				ans[i + 1] = 1ll * (N + 1 - sz[h1]) * sz[h2];
			}
		}
	}

	for(int i = 0;i < N;++i) {
		ans[i] -= ans[i + 1];
	}
	for(int i = 0;i <= N;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}