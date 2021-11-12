using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 1000005

int N,M,a[MAXN],b[MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b,b + N);
	vector<int> v;
	for(int i = 0;i < N;++i) {
		if(a[i] != b[i]) v.push_back(i);
	}
	if(v.size() == 0) {
		cout << "YES" << endl;
		return;
	}
	int dist = N - 1;
	for(int i = 1;i < v.size() - 1;++i) {
		dist = min(dist,max(v[i],N - 1 - v[i]));
	}
	if(dist >= M) {
		cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}