using namespace std;

#include <iostream>

#define MAXN 2005

int N;
long long arr[MAXN],pref[MAXN],sum;

void solve() {
	sum = 0;
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		pref[i + 1] = pref[i] ^ arr[i];
		sum ^= arr[i];
	}
	if(sum == 0) {
		cout << "YES" << endl;
		return;
	}
	for(int i = 0;i < N;++i) {
		for(int j = i + 1;j < N;++j) {
			if(pref[i + 1] == sum && pref[j + 1] == 0) {
				cout << "YES" << endl;
				return;
			}
		}
	}
	cout << "NO" << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}