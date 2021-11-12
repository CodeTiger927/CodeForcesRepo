using namespace std;

#include <iostream>
#include <map>

#define MAXN 55

int N,M;
bool g[MAXN][MAXN];

int main() {
	cin >> N >> M;
	// Ramsey Theory orz
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		if(a < MAXN && b < MAXN) g[a][b] = g[b][a] = true;
	}
	for(int a = 1;a <= min(48,N);++a) {
		for(int b = a + 1;b <= min(48,N);++b) {
			for(int c = b + 1;c <= min(48,N);++c) {
				for(int d = c + 1;d <= min(48,N);++d) {
					for(int e = d + 1;e <= min(48,N);++e) {
						if((g[a][b] && g[a][c] && g[a][d] && g[a][e] && g[b][c] && g[b][d] && g[b][e] && g[c][d] && g[c][e] && g[d][e]) || (!g[a][b] && !g[a][c] && !g[a][d] && !g[a][e] && !g[b][c] && !g[b][d] && !g[b][e] && !g[c][d] && !g[c][e] && !g[d][e])) {
							cout << a << " " << b << " " << c << " " << d << " " << e << endl;
							return 0;
						}
					}
				}
			}
		}
	}
	cout << -1 << endl;
	return 0;
}