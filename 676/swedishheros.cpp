using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N,K;
long long arr[MAXN],mul[MAXN],ind[MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		ind[i] = i;
		mul[i] = 1;
	}
	sort(ind,ind + N,[&](int a,int b) {return arr[a] < arr[b];});
	while((N + K) % 3 != 1) K++;
	while(K + 3 <= N && arr[ind[K]] + arr[ind[K + 1]] + arr[ind[K + 2]] < 0) K += 3;
	for(int i = 0;i < K;++i) mul[ind[i]] = -1;
	long long ans = 0;
	bool work = false;
	for(int i = 0;i < N;++i) {
		ans += arr[i] * mul[i];
		if(i && mul[i] == mul[i - 1]) {
			work = true;
		}
	}
	if(!work) {
		long long d = arr[ind[K - 1]] - arr[ind[K]];
		if(K >= 3) d = max(d,arr[ind[K - 1]] + arr[ind[K - 2]] + arr[ind[K - 3]]);
		if(K + 3 <= N) d = max(d,-(arr[ind[K]] + arr[ind[K + 1]] + arr[ind[K + 2]]));
		ans += 2 * d;
	}
	cout << ans << endl;
	return 0;
}