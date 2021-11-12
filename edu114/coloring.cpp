using namespace std;

#include <iostream>
#include <vector>
#include <set>
#include <map>

#define MAXN 1000005
#define MOD 998244353

int N,M,K,cntr[MAXN][2],cntc[MAXN][2],cnt[2],p2[MAXN];
map<pair<int,int>,int> m;
set<int> badr,badc,r,c;

void upd(int x,int y,int t,int cnt[MAXN][2],set<int>& bad,set<int>& s) {
	cnt[x][y] += t;
	if(cnt[x][0] > 0 && cnt[x][1] > 0) {
		bad.insert(x);
	}else{
		bad.erase(x);
	}
	if(cnt[x][0] > 0 || cnt[x][1] > 0) {
		s.insert(x);
	}else{
		s.erase(x);
	}
	return;
}

void upd(int x,int y,int t) {
	int col = (x & 1) ^ (y & 1);
	if(m.count({x,y})) {
		int n = col ^ m[{x,y}];
		cnt[n]--;
		upd(x,n,-1,cntr,badr,r);
		upd(y,n,-1,cntc,badc,c);
		m.erase({x,y});
	}
	if(t == -1) return;
	int n = col ^ t;
	cnt[n]++;
	upd(x,n,1,cntr,badr,r);
	upd(y,n,1,cntc,badc,c);
	m[{x,y}] = t;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	p2[0] = 1;
	for(int i = 1;i < MAXN;++i) p2[i] = (p2[i - 1] << 1) % MOD;
	for(int i = 0;i < K;++i) {
		int a,b,t;
		cin >> a >> b >> t;
		a--;b--;
		upd(a,b,t);
		int ans = 0;
		if(badr.size() > 0 && badc.size() > 0) {
			ans = 0;
		}else if(badr.size() > 0) {
			ans = p2[M - c.size()];
		}else if(badc.size() > 0) {
			ans = p2[N - r.size()];
		}else{
			if(r.size() == 0 && c.size() == 0) {
				ans = (p2[N] + p2[M] - 2) % MOD;
			}else{
				ans = (p2[N - r.size()] + p2[M - c.size()] - (cnt[0] == 0 || cnt[1] == 0)) % MOD;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}