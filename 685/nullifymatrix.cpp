using namespace std;

#include <iostream>

#define MAXN 105

int N,M,arr[MAXN][MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> arr[i][j];
		}
	}
	bool ans = true;
	for(int i = 0;i <= N + M - 2;++i) {
		int sum = 0;
		for(int j = 0;j <= i && j < N;++j) {
			int k = i - j;
			if(k >= M) continue;
			sum ^= arr[j][k];
		}
		if(sum) ans = false;
	}
	if(ans) {
		cout << "Jeel" << endl;
	}else{
		cout << "Ashish" << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}