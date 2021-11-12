using namespace std;

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 200005
#define MAXM 300005

struct BIT {
	long long bit[MAXM + 5];
	void upd(int x,long long v) {
		x++;
		while(x < MAXM) {
			bit[x] += v;
			x += (x & -x);
		}
		return;
	}

	long long get(int x) {
		x++;
		long long res = 0;
		while(x) {
			res += bit[x];
			x -= x & -x;
		}
		return res;
	}

	long long getSum(int l,int r) {
		return get(r) - get(l - 1);
	}
} A,B;

int N,arr[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	long long ans = 0;
	long long pref = 0;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		ans += 1ll * i * arr[i];
		ans += A.get(arr[i]);
		ans += pref;
		pref += arr[i];
		for(int j = arr[i];j < MAXM;j += arr[i]) {
			ans -= B.getSum(j,min(MAXM - 1,j + arr[i] - 1)) * j;
			A.upd(j,-arr[i]);
		}
		B.upd(arr[i],1);
		cout << ans << " ";
	}
	cout << endl;
	return 0;
}