using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 305

int N,cnt[3][2];
char arr[MAXN][MAXN];

void solve() {
	cin >> N;
	int K = 0;
	memset(cnt,0,sizeof(cnt));
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		for(int j = 0;j < N;++j) {
			arr[i][j] = str[j];
			if(arr[i][j] == 'X') {
				K++;
				cnt[(i + j) % 3][0]++;
			}else if(arr[i][j] == 'O') {
				K++;
				cnt[(i + j) % 3][1]++;
			}
		}
	}
	for(int a = 0;a < 3;++a) {
		for(int b = 0;b < 3;++b) {
			if(a == b) continue;
			if(cnt[a][0] + cnt[b][1] <= K / 3) {
				for(int i = 0;i < N;++i) {
					for(int j = 0;j < N;++j) {
						if((i + j) % 3 == a && arr[i][j] != '.') {
							arr[i][j] = 'O';
						}else if((i + j) % 3 == b && arr[i][j] != '.') {
							arr[i][j] = 'X';
						}
						cout << arr[i][j];
					}
					cout << endl;
				}
				return;
			}
		}
	}
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}