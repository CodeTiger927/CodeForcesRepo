using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define MAXN 71

int N,M,A,B,sz[MAXN],cmp[MAXN],rev[MAXN],dist[MAXN][131072];
vector<pair<int,int>> edges[MAXN];
vector<int> edges2[MAXN],four;

void dfs(int cur,int root) {
	if(cmp[cur]) return;
	cmp[cur] = root;
	sz[root]++;
	for(int i = 0;i < edges2[cur].size();++i) {
		int nxt = edges2[cur][i];
		dfs(nxt,root);
	}
	return;
}

int main() {
	cin >> N >> M >> A >> B;
	for(int i = 0;i < M;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		edges[a].push_back({b,c});
		edges[b].push_back({a,c});
		if(c == A) {
			edges2[a].push_back(b);
			edges2[b].push_back(a);
		}
	}
	int cnt = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < 131072;++j) {
			dist[i][j] = 1e9;
		}
		if(cmp[i]) continue;
		dfs(i,++cnt);
		if(sz[cnt] > 3) {
			rev[cnt] = four.size();
			four.push_back(cnt);
		}
	}
	queue<pair<int,pair<int,int>>> qa,qb;
	dist[0][sz[cmp[0]] > 3 ? (1 << rev[cmp[0]]) : 0] = 0;
	qa.push({0,{(sz[cmp[0]] > 3 ? (1 << rev[cmp[0]]) : 0),0}});
	qb.push({0,{(sz[cmp[0]] > 3 ? (1 << rev[cmp[0]]) : 0),0}});
	while(!qa.empty() || !qb.empty()) {
		pair<int,pair<int,int>> cur;
		if(qa.empty()) {
			cur = qb.front();
			qb.pop();
		}else if(qb.empty()) {
			cur = qa.front();
			qa.pop();
		}else if(dist[qa.front().first] < dist[qb.front().first]) {
			cur = qa.front();
			qa.pop();
		}else{
			cur = qb.front();
			qb.pop();
		}
		int curN = cur.first;
		int curM = cur.second.first;
		if(cur.second.second != dist[curN][curM]) continue;
		for(int i = 0;i < edges[curN].size();++i) {
			pair<int,int> nxt = edges[curN][i];
			int newM = curM ^ ((sz[cmp[nxt.first]] > 3 && cmp[nxt.first] != cmp[curN]) ? (1 << rev[cmp[nxt.first]]) : 0);
			if(sz[cmp[nxt.first]] > 3 && cmp[nxt.first] != cmp[curN] && curM & (1 << rev[cmp[nxt.first]])) continue;
			if(nxt.second == B && cmp[nxt.first] == cmp[curN]) continue;
			if(nxt.second + dist[curN][curM] < dist[nxt.first][newM]) {
				dist[nxt.first][newM] = nxt.second + dist[curN][curM];
				if(nxt.second == A) {
					qa.push({nxt.first,{newM,dist[nxt.first][newM]}});
				}else{
					qb.push({nxt.first,{newM,dist[nxt.first][newM]}});
				}
			}
		}
	}
	for(int i = 0;i < N;++i) {
		int curM = 1e9;
		for(int j = 0;j < 131072;++j) {
			curM = min(curM,dist[i][j]);
		}
		cout << curM << " ";
	}
	cout << endl;
}