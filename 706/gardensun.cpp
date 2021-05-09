using namespace std;

#include <iostream>
#define MAXN 505

int N,M;
bool arr[MAXN][MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			char c;
			cin >> c;
			arr[i][j] = (c == 'X');
		}
	}
	for(int i = (N % 3 == 0);i < N;) {
		for(int j = 0;j < M;++j) {
			arr[i][j] = true;
		}
		i += 3;
		if(i >= N) break;
		if(M == 1 || (!arr[i - 1][1] && !arr[i - 2][1])) {
			arr[i - 1][0] = arr[i - 2][0] = true;
		}else{
			arr[i - 1][1] = arr[i - 2][1] = true;
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cout << (arr[i][j] ? 'X' : '.');
		}
		cout << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}