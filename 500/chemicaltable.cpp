using namespace std;

#include <iostream>
#include <vector>

#define MAXNM 400005

vector<int> edges[MAXNM];
bool visited[MAXNM];
int N,M;

void dfs(int cur) {
	if(visited[cur]) return;
	visited[cur] = true;
	for(int i = 0;i < edges[cur].size();++i) {
		int next = edges[cur][i];
		if(visited[next]) continue;
		dfs(next);
	}
	return;
}

int main() {
	int N,M,Q;
	cin >> N >> M >> Q;
	for(int i = 1;i <= Q;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b + N);
		edges[b + N].push_back(a);
	}
	int cnt = 0;
	for(int i = 1;i <= N + M;++i) {
		cnt += !visited[i];
		dfs(i);
	}
	cout << (cnt - 1) << endl;
	return 0;
}