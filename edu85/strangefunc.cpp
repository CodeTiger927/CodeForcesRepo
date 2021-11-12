#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 500005

#define INF 1e18

int N,M;

long long st[1048576];
long long arr[MAXN];
long long cost[MAXN];
long long target[MAXN];
long long dp[MAXN];

vector<long long> nums[MAXN];

void update(int x,long long v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = v;
		return;
	}
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	st[p] = st[2 * p + 1] + st[2 * p + 2];
	return;
}

void update(int x,long long v) {
	update(x,v,0,MAXN,0);
	return;
}

long long getSum(int a,int b,int l,int r,int p) {
	if(r < a || l > b) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return getSum(a,b,l,m,2 * p + 1) + getSum(a,b,m + 1,r,2 * p + 2);
}

long long getSum(int a,int b) {
	if (a > b) return 0;
	return getSum(a,b,0,MAXN,0);
}

void solve(int l,int r,int a,int b,int lvl) {
	if(l > r || a > b) return;
	int cur = (a + b) / 2;
	int curI = nums[target[lvl]][cur];
	if(nums[target[lvl - 1]][l] > curI) {
		dp[curI] = INF;
		solve(l,r,cur + 1,b,lvl);
	}else{
		long long cost = INF;
		int record = -1;
		for(int i = l;i <= r;++i) {
			int nextI = nums[target[lvl - 1]][i];
			if(nextI > curI) break;
			long long curCost = getSum(nextI + 1,curI - 1) + dp[nextI];
			if(curCost < cost) {
				cost = curCost;
				record = i;
			}
		}
		dp[curI] = cost;
		record = max(record,l);
		solve(l,record,a,cur - 1,lvl);
		solve(record,r,cur + 1,b,lvl);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		nums[arr[i]].push_back(i);
		dp[i] = INF;
	}
	for(int i = 0;i < N;++i) {
		cin >> cost[i];
		update(i,cost[i]);
	}
	cin >> M;
	for(int i = 0;i < M;++i) {
		cin >> target[i];
	}


	int curLvl = 0;

	long long ans = INF;

	for(int i = 0;i < M;++i) {
		// cout << "level " << i << endl;
		int cur = target[i];
		if(i == 0) {
			for(int j = 0;j < nums[cur].size();++j) {
				int next = nums[cur][j];
				dp[next] = getSum(0,next - 1);
			}
		}else{
			solve(0,nums[target[i - 1]].size() - 1,0,nums[cur].size() - 1,i);
		}
		while(curLvl < cur) {
			++curLvl;
			for(int j = 0;j < nums[curLvl].size();++j) {
				if(cost[nums[curLvl][j]] > 0) {
					update(nums[curLvl][j],0);
				}
			}
		}
		if(i == M - 1) {
			for(int j = 0;j < nums[cur].size();++j) {
				int next = nums[cur][j];
				dp[next] += getSum(next + 1,N - 1);
				ans = min(ans,dp[next]);
			}
		}
	}
	// cout << ans << endl;
	if(ans > 1e15) {
		cout << "NO" << endl;
	}else{
		cout << "YES" << endl;
		cout << ans << endl;
	}

}