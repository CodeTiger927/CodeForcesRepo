using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 100005

int N,dp[MAXN][2],parent[MAXN],head[MAXN][2][2];
bool choose[MAXN][2];
vector<int> edges[MAXN],child[MAXN];

void dfs(int u) {
	if(u != 0 && edges[u].size() == 1) {
		dp[u][0] = dp[u][1] = 0;
		head[u][0][0] = head[u][0][1] = head[u][1][0] = head[u][1][1] = u;
		return;
	}
	int sum = 0;
	for(int v : edges[u]) {
		if(v == parent[u]) continue;
		parent[v] = u;
		dfs(v);
		child[u].push_back(v);
		sum += dp[v][1];
	}
	sort(child[u].begin(),child[u].end(),[&](int a,int b) {return (dp[a][0] - dp[a][1]) < (dp[b][0] - dp[b][1]);});
	choose[u][0] = 0;
	dp[u][0] = min(dp[u][0],sum + 2 * (int)child[u].size());
	head[u][0][0] = u;
	head[u][0][1] = head[child[u].back()][1][1];
	if(sum + dp[child[u][0]][0] - dp[child[u][0]][1] + 2 * ((int)child[u].size() - 1) < dp[u][0]) {
		dp[u][0] = sum + dp[child[u][0]][0] - dp[child[u][0]][1] + 2 * ((int)child[u].size() - 1);
		choose[u][0] = 1;
		head[u][0][0] = u;
		head[u][0][1] = head[child[u].back()][1][1];
	}
	choose[u][0] = 0;
	dp[u][1] = dp[u][0];
	head[u][1][0] = head[u][0][0];
	head[u][1][1] = head[u][0][1];
	if(child[u].size() >= 2) {
		dp[u][1] = min(dp[u][1],sum + dp[child[u][0]][0] - dp[child[u][0]][1] + dp[child[u][1]][0] - dp[child[u][1]][1] + 2 * ((int)child[u].size() - 2));
		choose[u][1] = 1;
		head[u][1][0] = head[child[u][0]][0][1];
		head[u][1][1] = head[child[u][1]][0][1];
	}
	return;
}

bool check(int a,int b,int c,int d) {
	if(a == c && b == d) return true;
	if(a == d && b == c) return true;
	return false;
}

void printAns(int u,int b) {
	if(child[u].size() == 0) return;
	if(b == 1) {
		if(choose[u][b] == 0) {
			printAns(u,0);
		}else{
			printAns(child[u][0],0);
			if(child[u].size() >= 2) printAns(child[u][1],0);
			int head1 = head[u][1][0];
			for(int i = 2;i < child[u].size();++i) {
				printAns(child[u][i],1);
				if(check(u + 1,child[u][i] + 1,head[child[u][i]][1][0] + 1,head1 + 1)) {
					head1 = head[child[u][i]][1][1];
					continue;
				}
				cout << u + 1 << " " << child[u][i] + 1 << " " << head[child[u][i]][1][0] + 1 << " " << head1 + 1 << endl;
				head1 = head[child[u][i]][1][1];	
			}
		}
	}else{
		if(choose[u][b] == 0) {
			int head1 = u;
			for(int i = 0;i < child[u].size();++i) {
				printAns(child[u][i],1);
				if(check(u + 1,child[u][i] + 1,head[child[u][i]][1][0] + 1,head1 + 1)) {
					head1 = head[child[u][i]][1][1];
					continue;
				}
				cout << u + 1 << " " << child[u][i] + 1 << " " << head[child[u][i]][1][0] + 1 << " " << head1 + 1 << endl;
				head1 = head[child[u][i]][1][1];	
			}
		}else{
			printAns(child[u][0],0);
			int head1 = head[child[u][0]][0][1];
			for(int i = 1;i < child[u].size();++i) {
				printAns(child[u][i],1);
				if(check(u + 1,child[u][i] + 1,head[child[u][i]][1][0] + 1,head1 + 1)) {
					head1 = head[child[u][i]][1][1];
					continue;
				}
				cout << u + 1 << " " << child[u][i] + 1 << " " << head[child[u][i]][1][0] + 1 << " " << head1 + 1 << endl;
				head1 = head[child[u][i]][1][1];
			}
		}
	}
	return;
}

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		edges[i].clear();child[i].clear();
		dp[i][0] = dp[i][0] = 1e9;
		parent[i] = 0;
		head[i][0][0] = head[i][0][1] = head[i][1][0] = head[i][1][1] = 0;
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	cout << dp[0][1] / 2 << endl;
	printAns(0,1);
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}