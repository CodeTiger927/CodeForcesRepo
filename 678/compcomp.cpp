using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 100005

int N,arr[MAXN];
vector<int> pos[MAXN];
vector<pair<int,int>> queries[MAXN];
bool appear[MAXN];

struct segTree {
	int l,r,v;
	segTree* le;
	segTree* ri;
	segTree(int _l,int _r): l(_l),r(_r),v(-MAXN) {
		if(l != r) {
			int m = (l + r) >> 1;
			le = new segTree(l,m);
			ri = new segTree(m + 1,r);
		}
	}
	void upd(int x,int _v) {
		if(x > r || x < l) return;
		if(l == r) {
			v = _v;
			return;
		}
		le -> upd(x,_v);
		ri -> upd(x,_v);
		v = min(le -> v,ri -> v);
	}

	int search(int x) {
		if(v > x) return MAXN;
		if(l == r) {
			if(v <= x) return l;
			return MAXN;
		}
		if(le -> v > x) {
			return ri -> search(x);
		}
		return le -> search(x);
	}
};

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		pos[arr[i]].push_back(i);
	}
	for(int i = 1;i <= N;++i) {
		int last = 0;
		for(int j : pos[i]) {
			if(j - 1 >= last) queries[j - 1].push_back({last,i});
			last = j + 1;
		}
		if(last < N) queries[N - 1].push_back({last,i});
	}
	segTree st = segTree(1,N);
	for(int i = 0;i < N;++i) {
		st.upd(arr[i],i);
		for(auto q : queries[i]) {
			if(st.search(q.first - 1) == q.second) {
				appear[q.second] = true;
			}
		}
	}
	for(int i = 1;i <= N;++i) {
		if(!appear[i]) {
			cout << i << endl;
			return 0;
		}
	}
	if(st.search(-1) == MAXN) {
		cout << N + 2 << endl;
		return 0;
	}
	cout << N + 1 << endl;
	return 0;
}