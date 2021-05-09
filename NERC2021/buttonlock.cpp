using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXN 1025

int D,N,mt[MAXN],arr[MAXN];
bool vis[MAXN];
vector<int> edges[MAXN];

bool kuhn(int v) {
	if(vis[v]) return false;
	vis[v] = true;
	for(int u : edges[v]) {
		if(mt[u] == -1 || kuhn(mt[u])) {
			mt[u] = v;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> D >> N;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < D;++j) {
			char c;
			cin >> c;
			arr[i] += (c - '0') << j;
		}
	}
	sort(arr,arr + N,[&](int a,int b) {return __builtin_popcount(a) > __builtin_popcount(b);});

	for(int i = 0;i < N;++i) {
		for(int j = 0;j < i;++j) {
			if((arr[i] & arr[j]) == arr[i]) edges[i].push_back(j);
		}
	}
	memset(mt,-1,sizeof(mt));
	for(int i = 0;i < N;++i) {
		memset(vis,0,sizeof(vis));
		kuhn(i);
	}
	vector<int> ans;
	memset(vis,0,sizeof(vis));
	for(int i = 0;i < N;++i) {
		if(vis[i]) continue;
		vis[i] = true;
		ans.push_back(-1);
		int a,b;
		for(a = mt[i],b = arr[i];a != -1;b = arr[a],a = mt[a]) {
			vis[a] = true;
			for(int j = 0;j < D;++j) {
				if((arr[a] ^ b) & (1 << j)) ans.push_back(j);
			}
		}		
		for(int j = 0;j < D;++j) if(b & (1 << j)) ans.push_back(j);
	}


	cout << (ans.size() - 1) << endl;
	for(int i = ans.size() - 1;i >= 1;--i) {
		if(ans[i] == -1) {
			cout << "R ";
		}else{
			cout << ans[i] << " ";
		}
	}
	cout << endl;
}