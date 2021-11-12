using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 505

int N,M,a[MAXN][MAXN],b[MAXN][MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		string s;
		cin >> s;
		for(int j = 0;j < M;++j) {
			a[i][j] = (s[j] == 'B');
		}
	}
	int ans = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			b[i][j] = (a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1]) & 1;
			ans += b[i][j];
		}
	}
	bool third = false;
	for(int i = 0;i < N - 1;++i) {
		for(int j = 0;j < M - 1;++j) {
			third |= b[i][j] && b[i][M - 1] && b[N - 1][j] && b[N - 1][M - 1];
		}
	}
	cout << (ans - third) << endl;
	return 0;
}