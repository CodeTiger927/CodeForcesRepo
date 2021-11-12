using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <set>

#define MAXN 100005

int N,M,K,r1[MAXN],r2[MAXN];
map<int,int> g[MAXN];
set<pair<int,int>> rows;
set<int> row[MAXN],col[MAXN]; 
vector<pair<int,int>> ans;

int findR(int* r,int x) {
	return r[x] == r[r[x]] ? r[x] : r[x] = findR(r,r[x]);
}

void merge(int* r,int a,int b) {
	a = findR(r,a);
	b = findR(r,b);
	if(a == b) return;
	r[b] = a;
	return;
}

void mergeR(int a,int b) {
	for(auto itr = row[b].begin();itr != row[b].end();++itr) {
		g[a][*itr] = g[b][*itr];
		row[a].insert(*itr);
		col[*itr].erase(b);
		col[*itr].insert(a);
	}
	return;
}

void mergeC(int a,int b) {
	for(auto itr = col[b].begin();itr != col[b].end();++itr) {
		g[*itr][a] = g[*itr][b];
		col[a].insert(*itr);
		row[*itr].erase(b);
		row[*itr].insert(a);
	}
	return;
}

int main() {
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		r1[i] = r2[i] = i;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		merge(r1,a,b);
	}
	for(int i = 0;i < K;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		merge(r2,a,b);
	}
	if(M < K) swap(r1,r2);
	for(int i = 0;i < N;++i) {
		int a = findR(r1,i);
		int b = findR(r2,i);
		g[a][b] = i;
		row[a].insert(b);
		col[b].insert(a);
	}
	for(int i = 0;i < N;++i) {
		if(i != findR(r1,i)) continue;
		rows.insert({-row[i].size(),i});
	}
	while(rows.size() > 1) {
		int a = rows.begin() -> second;
		rows.erase(rows.begin());
		int b = rows.begin() -> second;
		rows.erase(rows.begin());
		int x = *row[a].begin();
		int y = *row[b].begin();
		if(x == y) x = *row[a].rbegin();
		ans.push_back({g[a][x],g[b][y]});
		if(col[x].size() < col[y].size()) swap(x,y);
		mergeR(a,b);
		mergeC(x,y);
		rows.insert(make_pair(-row[a].size(),a));
	}
	cout << ans.size() << endl;
	for(auto [a,b] : ans) {
		cout << (a + 1) << " " << (b + 1) << endl;
	}
	return 0;
}