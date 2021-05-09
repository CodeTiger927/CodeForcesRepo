using namespace std;

#include <iostream>

#define MAXN 505

int N,arr[MAXN],grid[MAXN][MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = N - 1;i >= 0;--i) {
		int x = i;
		int y = i;
		int cnt = arr[i];
		while(cnt--) {
			grid[x][y] = arr[i];
			if(x == N - 1 || grid[x + 1][y]) {
				if(y != 0 && !grid[x][y - 1]) {
					y--;
				}else{
					y++;
				}
			}else{
				x++;
			}
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j <= i;++j) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}