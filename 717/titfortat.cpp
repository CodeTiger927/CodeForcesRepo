using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 105

int N,K,arr[MAXN];

void solve() {
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i < N - 1;++i) {
		if(arr[i] <= K) {
			K -= arr[i];
			arr[N - 1] += arr[i];
			arr[i] = 0;
		}else{
			arr[i] -= K;
			arr[N - 1] += K;
			K = 0;
			break;
		}
	}
	for(int i = 0;i < N;++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return;

}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}