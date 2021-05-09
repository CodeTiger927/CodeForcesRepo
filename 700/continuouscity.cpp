using namespace std;

#include <iostream>
#include <vector>
#include <array>
#include <math.h>

int L,R;
vector<array<int,3>> edges;

void addE(int x,int y,int z) {
	if(x > y) swap(x,y);
	edges.push_back({x,y,z});
}

int build(int l,int r) {
	if(l > 1) {
		int n = build(1,r - l + 1);
		addE(n,n + 1,l - 1);
		return n + 1;
	}
	if(!(r & (r - 1))) {
		int n = log2(r) + 1;
		for(int i = 2;i <= n + 1;++i) {
			addE(1,i,1);
			for(int j = 2;j < i;++j) {
				addE(i,j,(1 << (j - 2)));
			}
		}
		return n + 1;
	}
	int k = log2(r);
	int n = build(1,1 << k);
	addE(1,n + 1,1);
	for(int i = 2;i <= n;++i) {
		if((r - 1) >> (i - 2) & 1) addE(i,n + 1,1 + ((r - 1) >> (i - 1) << (i - 1)));
	}
	return (n + 1);
}

int main() {
	cin >> L >> R;
	int N = build(L,R);
	cout << "YES" << endl;
	cout << N << " " << edges.size() << endl;
	for(int i = 0;i < edges.size();++i) {
		cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;
	}
	return 0;
}