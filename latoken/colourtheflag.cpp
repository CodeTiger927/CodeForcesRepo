using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 55

int N,M;
char arr[MAXN][MAXN];

void solve() {
	cin >> N >> M;
	int marker = -1;
	bool flag = false;
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		for(int j = 0;j < M;++j) {
			arr[i][j] = str[j];
			if(str[j] != '.') {
				int cur = (i + j + (arr[i][j] == 'W')) % 2;
				if(marker != -1 && cur != marker) {
					flag = true;
				}else{
					marker = cur;
				}
			}
		}
	}
	if(flag) {
		cout << "NO" << endl;
		return;
	}
	if(marker == -1) marker = 0;
	cout << "YES" << endl;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cout << "WR"[(i + j) % 2 == marker];
		}
		cout << endl;
	}
	return;

}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}