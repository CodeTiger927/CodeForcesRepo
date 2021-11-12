using namespace std;

#include <iostream>
#include <vector>
#include <set>

#define MAXN 150005
#define MAXM 1000005

int N,Q,arr[MAXN],root[MAXM];
vector<int> pd[MAXM];

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	root[b] = a;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	root[1] = 1;
	for(int i = 2;i < MAXM;++i) {
		root[i] = i;
		if(pd[i].size() == 0) {
			for(int j = i;j < MAXM;j += i) {
				pd[j].push_back(i);
			}
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j : pd[arr[i]]) {
			merge(arr[i],j);
		}
	}
	set<pair<int,int>> edges;
	for(int i = 0;i < N;++i) {
		vector<int> nodes = pd[arr[i] + 1];
		nodes.push_back(arr[i]);
		for(int& x : nodes) {
			x = findR(x);
		}
		for(int j = 0;j < nodes.size();++j) {
			for(int k = j + 1;k < nodes.size();++k) {
				int a = nodes[j];
				int b = nodes[k];
				if(a == b) continue;
				edges.insert({min(a,b),max(a,b)});
			}
		}
	}
	for(int i = 0;i < Q;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		a = findR(arr[a]);
		b = findR(arr[b]);
		if(a == b) {
			cout << 0 << "\n";
		}else if(edges.count({min(a,b),max(a,b)})) {
			cout << 1 << "\n";
		}else{
			cout << 2 << "\n";
		}
	}
	return 0;
}