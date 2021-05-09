using namespace std;

#include <iostream>

#define MAXN 200005

int N,arr[MAXN],freq[MAXN],pre[MAXN],val[2 * MAXN],D,cnt;

int solve(int v) {
	int res = 0;
	for(int i = 0;i < 2 * N;++i) {
		val[i] = N;
	}
	val[N] = -1;
	for(int i = 0;i < N;++i) {
		pre[i + 1] = pre[i];
		if(arr[i] == v) {
			pre[i + 1]++;
		}else if(arr[i] == D) {
			pre[i + 1]--;
		}
		res = max(res,i - val[N + pre[i + 1]]);
		val[N + pre[i + 1]] = min(val[N + pre[i + 1]],i);
	}
	return res;
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		freq[arr[i]]++;
		if(freq[arr[i]] > freq[D]) {
			D = arr[i];
		}
	}
	for(int i = 1;i <= N;++i) {
		if(freq[i] == freq[D] && i != D) cnt++;
	}
	if(cnt) {
		cout << N << endl;
		return 0;
	}
	int ans = 0;
	for(int i = 1;i <= 100;++i) {
		if(i != D) ans = max(ans,solve(i));
	}
	cout << ans << endl;
	return 0;

}