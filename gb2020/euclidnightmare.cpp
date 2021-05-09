using namespace std;

#include <iostream>
#include <vector>

#define MAXN 500005
#define MOD 1000000007

// Disjoint Union Find DSU
int root[MAXN],szDSU[MAXN];

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

int N,M;

int main() {
	initDSU();
	cin >> N >> M;
	vector<int> v;
	long long ans = 1;
	for(int i = 0;i < N;++i) {
		int a,b,k;
		b = M + 1;
		cin >> k >> a;
		if(k == 2) {
			cin >> b;
		}
		if(!checkDSU(a,b)) {
			mergeDSU(a,b);
			v.push_back(i + 1);
			ans = (ans << 1) % MOD;
		}
	}
	cout << ans << " " << v.size() << endl;
	for(int i = 0;i < v.size();++i) {
		cout << v[i] << " ";
	}
	cout << endl;
	return 0;
}