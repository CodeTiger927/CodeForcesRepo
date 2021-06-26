using namespace std;

#include <iostream>

#define MAXN 100005

int N,M,arr[MAXN],la[MAXN],lb[MAXN],ra[MAXN],rb[MAXN],track[MAXN][2],dp[MAXN][2],ans[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i] >> la[i] >> lb[i] >> ra[i] >> rb[i];
	}
	la[0] = ra[0] = 0;
	lb[0] = rb[0] = M;
	int l = N + 1;
	int r = N + 1;
	bool lw = true;
	bool rw = true;
	int lba = 0;
	int lbb = M;
	int rba = 0;
	int rbb = M;
	dp[N + 1][0] = dp[N + 1][0] = N + 2;
	for(int i = N;i >= 0;--i) {
		lba = max(lba,la[i]);
		rba = max(rba,ra[i]);
		lbb = min(lbb,lb[i]);
		rbb = min(rbb,rb[i]);
		// cout << i << " " << r << " " << lba << " " << lbb << " " << rw << endl;
		// cout << i << " " << l << " " << rba << " " << rbb << " " << lw << endl;
		if(arr[i] >= lba && arr[i] <= lbb && rw) {
			dp[i][0] = r;
		}
		if(arr[i] >= rba && arr[i] <= rbb && lw) {
			dp[i][1] = l;
		}
		if(dp[i][0]) {
			lw = true;
			l = i;
			rba = ra[i];
			rbb = rb[i];
		}
		if(dp[i][1]) {
			rw = true;
			r = i;
			lba = la[i];
			lbb = lb[i];
		}
		lw &= arr[i] >= la[i] && arr[i] <= lb[i];
		rw &= arr[i] >= ra[i] && arr[i] <= rb[i];
	}
	int cur = 0;
	bool c = 0;
	if(dp[0][0]) {
		c = false;
	}else if(dp[0][1]) {
		c = true;
	}else{
		cout << "No" << endl;
		return 0;
	}
	cout << "Yes" << endl;
	while(cur < N + 1) {
		int n = dp[cur][c];
		for(++cur;cur <= n;++cur) {
			ans[cur] = !c;
		}
		cur--;
		c ^= 1;
	}
	for(int i = 1;i <= N;++i) {
		cout << ans[i] << " \n"[i == N];
	}
	return 0;
}