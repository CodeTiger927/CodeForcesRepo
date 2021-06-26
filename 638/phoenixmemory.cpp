using namespace std;

#include <iostream>
#include <set>

#define MAXN 200005

struct node {
	int l,r;
	pair<int,int> v;
	node *lp,*rp;
	node(int _l,int _r): l(_l),r(_r),v({MAXN,MAXN}) {
		if(_l == _r) return;
		int m = (l + r) >> 1;
		lp = new node(l,m);
		rp = new node(m + 1,r);
	}

	void upd(int x,pair<int,int> _v) {
		if(x > r || x < l) return;
		if(l == r) {
			v = _v;
			return;
		}
		lp -> upd(x,_v);
		rp -> upd(x,_v);
		v = min(lp -> v,rp -> v);
		return;
	}

	pair<int,int> getMin(int a,int b) {
		if(a > r || b < l) return {MAXN,MAXN};
		if(a <= l && b >= r) return v;
		return min(lp -> getMin(a,b),rp -> getMin(a,b));
	}
};

int N,l[MAXN],r[MAXN],ans[MAXN],where[MAXN];
set<pair<int,int>> segs[MAXN];

void show() {
	for(int i = 1;i <= N;++i) cout << ans[i] << " ";
	cout << endl;
}

int main() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> l[i] >> r[i];
		segs[l[i]].insert({r[i],i});
	}
	set<pair<int,int>> s;
	for(int i = 1;i <= N;++i) {
		s.insert(segs[i].begin(),segs[i].end());
		auto b = s.begin();
		ans[b -> second] = i;
		where[i] = b -> second;
		s.erase(b);
	}
	node* st = new node(1,MAXN);
	for(int i = 1;i <= N;++i) {
		st -> upd(i,{l[where[i]],i});
	}
	for(int i = 1;i <= N;++i) {
		pair<int,int> cur = st -> getMin(i + 1,r[where[i]]);
		if(cur.first == MAXN) continue;
		if(l[where[cur.second]] <= i) {
			cout << "NO" << endl;
			show();
			swap(ans[where[i]],ans[where[cur.second]]);
			show();
			return 0;
		}
	}
	cout << "YES" << endl;
	show();
	return 0;
}