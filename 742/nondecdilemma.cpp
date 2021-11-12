using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define MAXN 200005

int N,M,arr[MAXN];

long long calc(int a,int b) {
	int n = b - a + 1;
	return 1ll * n * (n + 1) / 2;
}

struct node {
	int l,r;
	node *lp,*rp;
	set<pair<int,int>> s;
	long long ans;

	node(int _l,int _r): l(_l),r(_r) {
		ans = calc(l,r);
		s.insert({l,r});
		if(l == r) return;
		int m = (l + r) >> 1;
		lp = new node(l,m);
		rp = new node(m + 1,r);
		
	}

	void upd(int a) {
		if(a > r || a < l) return;
		modify(a);
		if(l == r) return;
		lp -> upd(a);
		rp -> upd(a);
		return;
	}

	long long getAns(int a,int b) {
		set<pair<int,int>> all;
		long long res = gather(a,b,all);
		// cout << "DONE " << res << endl;
		for(auto itr = all.begin();itr != all.end();++itr) {
			int lb = itr -> first;
			int rb = itr -> second;
			while(next(itr) != all.end()) {
				if(arr[itr -> second] <= arr[next(itr) -> first] && itr -> second + 1 == next(itr) -> first) {
					rb = next(itr) -> second;
					res -= calc(itr -> first,itr -> second);
					all.erase(itr++);
				}else{
					break;
				}
			}
			res -= calc(itr -> first,itr -> second);
			all.erase(itr);
			itr = all.insert({lb,rb}).first;
			res += calc(lb,rb);
		}
		return res;
	}

	long long gather(int a,int b,set<pair<int,int>>& all) {
		long long res = 0;
		if(a > r || b < l) return 0;
		if(a <= l && b >= r) {
			all.insert(*s.begin());
			if(s.size() > 1) {
				all.insert(*s.rbegin());
			}
			return ans;
		}
		res += lp -> gather(a,b,all);
		res += rp -> gather(a,b,all);
		return res;
	}

	void modify(int x) {
		if(l == r) return;
		auto p = prev(s.lower_bound({x,MAXN}));
		
		pair<int,int> cur = *p;
		int a = cur.first;
		int b = cur.second;
		
		s.erase(p);
		ans -= calc(a,b);
		int lx = a;
		int rx = b;
		if(x != a) {
			if(arr[x] < arr[x - 1]) {
				s.insert({a,x - 1});
				ans += calc(a,x - 1);
				lx = x;
			}
		}
		
		if(x != b) {
			if(arr[x + 1] < arr[x]) {
				s.insert({x + 1,b});
				ans += calc(x + 1,b);
				rx = x;
			}
		}
		s.insert({lx,rx});
		ans += calc(lx,rx);
		if(x == a && x > l && arr[x] >= arr[x - 1]) {
			p = prev(s.lower_bound({x,MAXN}));
			auto lp = prev(p);
			int lb = lp -> first;
			int rb = p -> second;
			ans -= calc(p -> first,p -> second);
			s.erase(p);
			ans -= calc(lp -> first,lp -> second);
			s.erase(lp);
			s.insert({lb,rb});
			ans += calc(lb,rb);
		}
		if(x == b && x < r && arr[x + 1] >= arr[x]) {
			p = prev(s.lower_bound({x,MAXN}));
			auto rp = next(p);
			int lb = p -> first;
			int rb = rp -> second;
			ans -= calc(p -> first,p -> second);
			s.erase(p);
			ans -= calc(rp -> first,rp -> second);
			s.erase(rp);
			s.insert({lb,rb});
			ans += calc(lb,rb);
		}
	}
};

node* st;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	st = new node(0,N - 1);
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		st -> upd(i);
	}
	for(int i = 0;i < M;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		if(a == 1) {
			arr[--b] = c;
			st -> upd(b);
		}else{
			b--;c--;
			cout << (st -> getAns(b,c)) << endl;
		}
	}
	return 0;
}