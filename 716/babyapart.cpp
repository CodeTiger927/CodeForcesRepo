using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 105

bool firstQuery(int a,int b) {
	cout << 1 << " " << a << " " << b << endl;
	int res;
	cin >> res;
	return res;
}

bool secondQuery(int x,int s,vector<int>& v) {
	cout << 2 << " " << x << " " << s;
	for(int i = 0;i < s;++i) cout << " " << v[i];
	cout << endl;
	int res;
	cin >> res;
	return res;
}

int N;
bool ans[MAXN][MAXN];

void solve() {
	cin >> N;
	vector<int> ham;
	for(int i = 0;i < N;++i) {
		ham.push_back(i);
		for(int j = 0;j < N;++j) {
			ans[i][j] = true;
		}
	}
	stable_sort(ham.begin(),ham.end(),firstQuery);
	int ptr = N - 1;
	for(int i = N - 1;i >= 0;--i) {
		if(ptr == i) {
			for(int j = 0;j <= i;++j) {
				for(int k = i + 1;k < N;++k) {
					ans[ham[k]][ham[j]] = false;
				}
			}
			ptr--;
		}
		while(ptr >= 0 && secondQuery(ham[i],ptr + 1,ham)) ptr--;
	}
	cout << 3 << endl;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			cout << ans[i][j];
		}
		cout << endl;
	}
	int status;
	cin >> status;
	if(status == -1) exit(0);
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		solve();
	} 
}