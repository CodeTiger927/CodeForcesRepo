using namespace std;

#include <iostream>

long long con(int n,int k) {
	long long ans = 0;
	for(int i = 0;i < n;++i) {
		ans = 10ll * ans + k;
	}
	return ans;
}

long long N;

void solve() {
	cin >> N;
	int ans = 0;
	for(int i = 1;i < 15;++i) {
		for(int j = 1;j <= 9;++j) {
			if(con(i,j) <= N) {
				ans++;
			}else{
				break;
			}
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}