using namespace std;

#include <iostream>

#define MAXN 505

int arr[MAXN][MAXN];

int main() {
	int N,M;
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> arr[i][j];
			if((i + j) & 1) {
				cout << 720720 << " ";
			}else{
				cout << (720720 + arr[i][j] * arr[i][j] * arr[i][j] * arr[i][j]) << " ";
			}
		}
		cout << endl;
	}
	return 0;
}