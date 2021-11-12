using namespace std;

#include <iostream>

#define MAXN 1005

int N;
unsigned long long arr[MAXN];
string seq = "";

bool test(int i,int j) {
	int open = 0;
	for(int k = i;k <= j;++k) {
		if(seq[k] == '(') {
			open++;
		}else{
			open--;
			if(open < 0) return false;
		}
	}
	return open == 0;
}

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		seq += string(arr[i],"()"[i & 1]);
	}
	int ans = 0;
	for(int i = 0;i < seq.size();++i) {
		for(int j = i;j < seq.size();++j) {
			ans += test(i,j);
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T = 1;
	// cin >> T;
	while(T--) solve();
}