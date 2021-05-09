using namespace std;

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <vector>

#define MAXN 100005

int N,M,K;
unordered_map<string,int> m;
vector<int> edges[MAXN],ans;
string pats[MAXN],strs[MAXN];
int visited[MAXN];
bool cycle = false;

void dfs(int cur) {
	visited[cur] = 1;
	for(int i = 0;i < edges[cur].size();++i) {
		int nxt = edges[cur][i];
		if(visited[nxt] == 1) cycle = true;
		if(!visited[nxt]) dfs(nxt);
	}
	visited[cur] = 2;
	ans.push_back(cur);
}

bool match(int a,int b) {
	for(int i = 0;i < K;++i) {
		if(pats[a][i] != '_' && pats[a][i] != strs[b][i]) return false;
	}
	return true;
}

int main() {
	cin >> N >> M >> K;
	for(int i = 1;i <= N;++i) {
		cin >> pats[i];
		m[pats[i]] = i;
	}
	for(int i = 1;i <= M;++i) {
		int cur;
		cin >> strs[i] >> cur;
		if(!match(cur,i)) {
			cout << "NO" << endl;
			return false;
		}
		vector<int> v;
		for(int j = 0;j < (1 << K);++j) {
			string str = strs[i];
			for(int k = 0;k < K;++k) {
				if(j & (1 << k)) {
					str[k] = '_';
				}
			}
			if(m[str]) v.push_back(m[str]); 
		}
		for(int j = 0;j < v.size();++j) {
			if(v[j] == cur) continue;
			edges[v[j]].push_back(cur);
		}
	}
	for(int i = 1;i <= N;++i) {
		if(visited[i]) continue;
		dfs(i);
	}
	if(cycle) {
		cout << "NO" << endl;
	}else{
		cout << "YES" << endl;
		for(int i = 0;i < N;++i) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}