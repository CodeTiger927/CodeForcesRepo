using namespace std;

#include <iostream>

#define MAXN 200005

int N,K,arr[MAXN],pre[MAXN];

bool test(int m) {
	for(int i = 0;i < N;++i) {
		pre[i + 1] = (arr[i] >= m ? 1 : -1) + pre[i];
	}
	int run = 1e9;
	for(int i = K;i <= N;++i) {
		run = min(run,pre[i - K]);
		int cur = pre[i] - run;
		if(cur > 0) {
			return true;
		}
	}
	return false;
}

int main() {
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	int l = 1;
	int r = N;
	while(l < r) {
		int m = (l + r + 1) >> 1;
		if(test(m)) {
			l = m;
		}else{
			r = m - 1;
		}
	}
	cout << l << endl;
	return 0;
}