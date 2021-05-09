using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define MAXN 200005

vector<pair<int,int>> edges[MAXN];
int sz[MAXN],parent[MAXN],N,fib[MAXN];
bool cut[MAXN];

void precalc() {
	fib[1] = 1;
	int cur1 = 1;
	int cur2 = 2;
	while(cur2 < MAXN) {
		fib[cur2] = cur1;
		swap(cur2,cur1);
		cur2 += cur1;
	}
	return;
}

void dfs(int cur) {
	sz[cur] = 1;
	for(int i = 0;i < edges[cur].size();++i) {
		pair<int,int> nxt = edges[cur][i];
		if(cut[nxt.second] || parent[cur] == nxt.first) continue;
		parent[nxt.first] = cur;
		dfs(nxt.first);
		sz[cur] += sz[nxt.first];
	}
	return;
}

bool check(int cur) {
	parent[cur] = cur;
	dfs(cur);
	int curS = sz[cur];
	if(curS == 1) return true;
	if(!fib[curS]) return false;
	int cur1 = fib[curS];
	int cur2 = curS - fib[curS];
	queue<pair<int,int>> q;
	q.push({cur,-1});
	int record = -1;
	int record2 = -1;
	while(!q.empty()) {
		int c = q.front().first;
		if(sz[c] == cur1 || sz[c] == cur2) {
			record = c;
			record2 = q.front().second;
			break;
		}
		q.pop();
		for(int i = 0;i < edges[c].size();++i) {
			pair<int,int> nxt = edges[c][i];
			if(cut[nxt.second] || parent[c] == nxt.first) continue;
			parent[nxt.first] = c;
			q.push(nxt);
		}
	}
	if(record == -1) return false;
	cut[record2] = true;
	return (check(cur) && check(record));

}

int main() {
	precalc();
	int N;
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back({b,i});
		edges[b].push_back({a,i});
	}
	if(check(0)) {
		cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
	return 0;
}