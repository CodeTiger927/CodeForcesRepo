using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005

// Disjoint Union Find DSU
int root[MAXN],szDSU[MAXN];
vector<int> all[MAXN];

// Call this first please
void initDSU() {
	for(int i = 0;i < MAXN;++i) {
		root[i] = i;
		szDSU[i] = 1;
	}
}

int findR(int x) {
	if(root[x] != root[root[x]]) {
		root[x] = findR(root[x]);
	}
	return root[x];
}

void mergeDSU(int a,int b) {
	int aR = findR(a);
	int bR = findR(b);
	if(aR == bR) return;
	if(szDSU[aR] > szDSU[bR]) swap(aR,bR);
	szDSU[bR] += szDSU[aR];
	root[aR] = bR;
	return;
}

bool checkDSU(int a,int b) {
	return (findR(a) == findR(b));
}

int N,M,arr[MAXN],ans[MAXN],ans2[MAXN];
bool visited[MAXN];

int main() {
	initDSU();
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
	}
	for(int i = 1;i <= N;++i) {
		mergeDSU(i,arr[i]);
		if(arr[arr[i]] != arr[i]) {
			cout << -1 << endl;
			return 0;
		}
	}
	for(int i = 1;i <= N;++i) {
		all[findR(i)].push_back(i);
	}
	for(int i = 1;i <= N;++i) {
		int curR = findR(i);
		if(visited[curR]) continue;
		visited[curR] = true;
		M++;
		for(int i = 0;i < all[curR].size();++i) {
			ans[all[curR][i]] = M;
		}
		ans2[ans[curR]] = arr[curR];
	}
	for(int i = 1;i <= N;++i) {
		if(i <= M && ans[ans2[i]] != i) {
			cout << -1 << endl;
			return 0;
		}
		if(ans2[ans[i]] != arr[i]) {
			cout << -1 << endl;
			return 0;
		}
	}
	cout << M << endl;
	for(int i = 1;i <= N;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
	for(int i = 1;i <= M;++i) {
		cout << ans2[i] << " ";
	}
	cout << endl;
	return 0;
}