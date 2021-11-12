using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 5005
#define MOD 1000000007

int N,M,cntl[MAXN],cntr[MAXN],s[MAXN],ans1,ans2;
vector<int> cows[MAXN];

void upd(int x) {
	long long res = 0;
	long long ways = 1;
	for(int i = 1;i <= N;++i) {
		int l = upper_bound(cows[i].begin(),cows[i].end(),cntl[i]) - cows[i].begin();
		int r = upper_bound(cows[i].begin(),cows[i].end(),cntr[i]) - cows[i].begin();
		if(!l && !r) continue;
		if(i == x) {
			if(r >= l) r--;
			res += 1 + !!r;
			if(r) ways = 1ll * ways * r % MOD;
		}else if(!l || !r || (l == 1 && r == 1)) {
			res++;
			ways = 1ll * ways * (l + r) % MOD;
		}else{
			res += 2;
			ways = 1ll * ways * (1ll * min(l,r) * (max(l,r) - 1) % MOD) % MOD;
		}
	}
	if(res >= ans1) ans2 = (ans1 == res ? ans2 : 0) + ways;
	if(ans2 >= MOD) ans2 -= MOD;
	ans1 = max(ans1,(int)res);
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> s[i];
		cntr[s[i]]++;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		cows[a].push_back(b);
	}
	for(int i = 1;i <= N;++i) {
		sort(cows[i].begin(),cows[i].end());
	}
	upd(0);
	for(int i = 0;i < N;++i) {
		cntl[s[i]]++;
		cntr[s[i]]--;
		auto it = lower_bound(cows[s[i]].begin(),cows[s[i]].end(),cntl[s[i]]);
		if(it != cows[s[i]].end() && *it == cntl[s[i]]) upd(s[i]);
	}
	cout << ans1 << " " << ans2 << endl;
	return 0;
}