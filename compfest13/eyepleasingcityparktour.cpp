using namespace std;

#include <iostream>
#include <vector>
 
#define MAXN 200005
#define MOD 1000000007

int N,K;
long long m,rt,arr[MAXN],f[2][MAXN],g[2][MAXN],sz[MAXN],mx[MAXN],vis[MAXN],ans;
vector<int> edges[MAXN][2];
 
void add(int u,int fa,long long num,long long sum,int col,int fst){
	sum += arr[u];
	f[fst][num] = (f[fst][num] + sum) % MOD;
	g[fst][num]++;;
	m = max(m,num);
	for(int op : {0,1}){
		for(int v : edges[u][op]){
			if(v != fa && !vis[v]){
				add(v,u,num + (op != col),sum,op,fst);
			}
		}
	}
	return;
}
 
void upd(long long k,long long val){
	for(int i = 1;i <= m;++i){
		g[0][i] += g[0][i - 1];
		g[1][i] += g[1][i - 1];
	}
	if(val != -1) ans += (g[0][min(K,(int)m)] + g[1][min(K,(int)m)]) * val * k % MOD;
	for(int op : {0,1}){
		for(int i = 1;i <= m;++i){
			ans += k * f[op][i] * g[op][min(K - i + 1,(int)m)] % MOD;
			ans += k * f[op][i] * g[op ^ 1][min(K - i,(int)m)] % MOD;
			if(i <= K&& val !=- 1) ans += f[op][i] * k;
		}
	}
	ans %= MOD;
	for(int i = 1;i <= m;++i) f[0][i] = f[1][i] = g[0][i] = g[1][i] = 0;
	return;
}
 
void calc(int u,int fa,int num){
	mx[u]=0;
	for(int op : {0,1}){
		for(int v : edges[u][op]){
			if(!vis[v] && v != fa){
				calc(v,u,num);
				mx[u] = max(mx[u],sz[v]);
			}
		}
	}
	mx[u] = max(mx[u],num - sz[u]);
	if(mx[u] <mx[rt]) rt = u;
	return;
}
 
void dfs(int u,int fa){
	sz[u] = 1;
	for(int op:{0,1}){
		for(int v : edges[u][op]){
			if(!vis[v] && v != fa){
				dfs(v,u);
				sz[u] += sz[v];
			}
		}
	}
	return;
}
 
void solve(int x){
	vis[x] = 1;
	m = 0;
	for(int op:{0,1}){
		for(int v : edges[x][op]) {
			if(!vis[v]){
				add(v,0,1,arr[x] / 2,op,op);
			}
		}
	}
	upd(1,arr[x] / 2);
	for(int op:{0,1}){
		m = 0;
		for(int v : edges[x][op]) {
			if(!vis[v]) {
				add(v,0,1,arr[x] / 2,op,op);
				upd(-1,-1);
			}
		}
	}
	for(int op : {0,1}){
		for(int v : edges[x][op]) {
			if(!vis[v]) {
				rt = 0;
				dfs(v,0);
				calc(v,0,sz[v]);
				solve(rt);
			}
		}
	}
	return;
}
 
int main(){
	cin >> N >> K;
	K++;
	for(int i = 1;i <= N;++i){
		cin >> arr[i];
		arr[i] *= 2;
		ans += arr[i];
	}
	for(int i = 1;i < N;++i){
		int a,b,c;
		cin >> a >> b >> c;
		edges[a][c].push_back(b);
		edges[b][c].push_back(a);
	}
	mx[rt = 0] = N + 1;
	dfs(1,0);
	calc(1,0,sz[1]);
	solve(rt);
	ans += MOD;
	ans = ans * ((MOD + 1) / 2) % MOD;
	cout << ans << endl;	
	return 0;
}