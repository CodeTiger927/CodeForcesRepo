using namespace std;

#include <iostream>
#include <cstring>
#include <chrono>
#include <random>

int ask(int n,int l,int l2) {
	cout << "? " << n << " " << n << endl;
	for(int i = 0;i < n;++i) cout << (l + i) << " ";
	cout << endl;
	for(int i = 0;i < n;++i) cout << (l2 + i) << " ";
	cout << endl;
	string res;
	cin >> res;
	if(res == "FIRST") return 0;
	if(res == "SECOND") return 1;
	return 2;
}

int N,K;

void solve() {
	cin >> N >> K;
	for(int i = 0;i < 30;++i) {
		int cur = rand() % (N - 1) + 2;
		int res = ask(1,1,cur);
		if(res == 1) {
			cout << "! 1" << endl;
			return;
		}
	}
	for(int i = 1;i <= N / 2;) {
		int res = ask(i,1,i + 1);
		if(res == 0) {
			int l = i + 1;
			int r = 2 * i;
			while(l < r) {
				int m = (l + r) >> 1;
				int cur = ask(m - l + 1,1,l);
				if(cur == 0) {
					r = m;
				}else{
					l = m + 1;
				}
			}
			cout << "! " << l << endl;
			return;
		}
		if(i == N / 2) {
			cout << "! " << N << endl;
			return;
		}
		i = min(i << 1,N / 2);
	}
	return;
}

int main() {
	std::srand ( unsigned (std::chrono::system_clock::now().time_since_epoch().count() ) );
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}