using namespace std;

#include <iostream>

int ans[505][505];

int main() {
	int N;
	cin >> N;
	if(N <= 2) {
		cout << -1 << endl;
		return 0;
	}
	int t = 1;
	for(int i = N;i >= 4;--i) {
		if(i & 1) {
			for(int j = 1;j <= i;++j) {
				ans[i][j] = t++;
			}
			for(int j = i - 1;j >= 1;--j) {
				ans[j][i] = t++;
			}
		}else{
			for(int j = 1;j <= i;++j) {
				ans[j][i] = t++;
			}
			for(int j = i - 1;j >= 1;--j) {
				ans[i][j] = t++;
			}
		}
	}
	ans[3][1] = t++;
	ans[2][2] = t++;
	ans[3][2] = t++;
	ans[3][3] = t++;
	ans[1][2] = t++;
	ans[1][3] = t++;
	ans[2][1] = t++;
	ans[2][3] = t++;
	ans[1][1] = t++;
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= N;++j) {
			cout << ans[i][j] << " \n"[j == N];
		}
	}
	return 0;
}