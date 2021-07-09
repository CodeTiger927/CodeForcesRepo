using namespace std;

#include <iostream>
#include <math.h>

#define MAXN 100005

int N;
long long K,arr[MAXN],sol[MAXN];

long long val(long long x,long long a) {
	return a - 1 - 3ll * (x - 1) * (x - 1) - 3ll * (x - 1);
}

long long get(long long x) {
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		long long l = 0;
		long long r = arr[i];
		while(l < r) {
			long long m = (l + r) / 2;
			long long c = val(m,arr[i]);
			if(c > x) {
				l = m + 1;
			}else if(c < x) {
				r = m - 1;
			}else{
				l = r = m;
			}
		}
		if(val(l,arr[i]) < x) l--;
		sol[i] = l;
		ans += l;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	long long r = 4e18;
	long long l = -4e18;
	for(int i = 0;i < N;++i) cin >> arr[i];
	while(l < r) {
		long long m = l + (r - l) / 2;
		long long c = get(m);
		if(c < K) {
			r = m - 1;
		}else if(c > K) {
			l = m + 1;
		}else{
			l = r = m;
		}
	}
	long long ans;
	while((ans = get(l)) < K) l--;
	int idx = 0;
	while(ans > K) {
		if(val(sol[idx],arr[idx]) == l) {
			sol[idx]--;
			ans--;
		}
		idx++;
	}
	for(int i = 0;i < N;++i) {
		cout << sol[i] << " \n"[i == N - 1];
	}
	return 0;
}