using namespace std;

#include <iostream>
#include <cstring>
#include <set>
#include <vector>

#define MAXN 400005

int N,M,arr[MAXN],root[MAXN],sz[MAXN];
vector<bool> sand[MAXN];
set<int> cols[MAXN],edges[MAXN];
vector<pair<int,int>> all;

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a,b);
	sz[a] += sz[b];
	root[b] = a;
	return;
}

int toN(int a,int b) {
	return a * M + b;
}

void addEdge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	all.push_back({a,b});
	// cout << a << " " << b << endl;
	edges[b].insert(a);
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		sand[i].resize(M);
		for(int j = 0;j < M;++j) {
			root[toN(i,j)] = toN(i,j);
			sz[toN(i,j)] = 1;
			sand[i][j] = str[j] == '#';
			if(sand[i][j]) {
				if(i > 0 && sand[i - 1][j]) merge(toN(i,j),toN(i - 1,j));
				if(j > 0 && sand[i][j - 1]) merge(toN(i,j),toN(i,j - 1));
				cols[j].insert(i);
			}
		}
	}
	for(int i = 0;i < M;++i) {
		cin >> arr[i];
	}
	for(int counter = 0;counter < 15;++counter) {

	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			if(!sand[i][j]) continue;

			// down
			auto itr = cols[j].upper_bound(i);
			if(itr != cols[j].end()) {
				int down = *itr;
				addEdge(toN(i,j),toN(down,j));
			}
			// left
			if(j > 0 && cols[j - 1].size() != 0) {
				itr = cols[j - 1].upper_bound(i);
				if(itr != cols[j - 1].end()) {
					int le = *itr;
					addEdge(toN(i,j),toN(le,j - 1));
				}
			}
			// right
			if(j < M - 1 && cols[j + 1].size() != 0) {
				itr = cols[j + 1].upper_bound(i);
				if(itr != cols[j + 1].end()) {
					int ri = *itr;
					addEdge(toN(i,j),toN(ri,j + 1));
				}
			}
		}
	}
	for(auto p : all) {
		if(edges[p.first].count(p.second) && edges[p.second].count(p.first)) {
			merge(p.first,p.second);
		}
	}

	}

	for(int i = 0;i < N * M;++i) {
		edges[i].clear();
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			if(!sand[i][j]) continue;

			// down
			auto itr = cols[j].upper_bound(i);
			if(itr != cols[j].end()) {
				int down = *itr;
				addEdge(toN(i,j),toN(down,j));
			}
			// left
			if(j > 0 && cols[j - 1].size() != 0) {
				itr = cols[j - 1].upper_bound(i);
				if(itr != cols[j - 1].end()) {
					int le = *itr;
					addEdge(toN(i,j),toN(le,j - 1));
				}
			}
			// right
			if(j < M - 1 && cols[j + 1].size() != 0) {
				itr = cols[j + 1].upper_bound(i);
				if(itr != cols[j + 1].end()) {
					int ri = *itr;
					addEdge(toN(i,j),toN(ri,j + 1));
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			if(!sand[i][j]) continue;
			if(toN(i,j) != findR(toN(i,j))) continue;
			ans += (edges[toN(i,j)].size() == 0);
			// if(inD[toN(i,j)] == 0) {
			// 	cout << i << " " << j << endl;
			// }
		}
	}
	cout << ans << endl;
	return 0;
}