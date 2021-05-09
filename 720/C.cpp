using namespace std;

#include <iostream>

#define MAXN 20005

int N,arr[MAXN];
int ans[4] = {3,1,4,2};

int ask1(int i,int j,int x) {
	cout << "? " << 1 << " " << i << " " << j << " " << x << endl;
	int res;
	// res = max(min(ans[i - 1],x),min(ans[j - 1],x + 1));
	// cout << res << endl;
	cin >> res;
	return res;
}

int ask2(int i,int j,int x) {
	cout << "? " << 2 << " " << i << " " << j << " " << x << endl;
	int res;
	// res = min(max(ans[i - 1],x),max(ans[j - 1],x + 1));
	// cout << res << endl;
	cin >> res;
	return res;
}

void answer() {
	cout << "!";
	for(int i = 1;i <= N;++i) {
		cout << " " << arr[i];
	}
	cout << endl;
	return;
}

void solve() {
	cin >> N;
	// N = 4;
	int isN = N;
	for(int i = 1;i < N;i += 2) {
		int cur = ask1(i,i + 1,N - 1);
		if(cur == N) {
			isN = i + 1;
			break;
		}else if(cur == N - 1) {
			if(ask1(i + 1,i,N - 1) == N) {
				isN = i;
			}
		}
	}
	for(int i = 1;i <= N;++i) {
		if(i == isN) {
			arr[i] = N;
			continue;
		}
		arr[i] = ask2(i,isN,1);
	}
	answer();
	return;
}

int main() {
	int T;
	// T = 1;
	cin >> T;
	while(T--) solve();
}