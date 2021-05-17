using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 300005

int N,Q,arr[MAXN],st[1048576],ans[MAXN];
vector<pair<int,int>> queries[MAXN];

void upd(int x,int v) {
	x++;
	while(x < MAXN) {
		st[x] += v;
		x += x & -x;
	}
	return;
}

int qry(int x) {
	x++;
	int res = 0;
	while(x) {
		res += st[x];
		x -= x & -x;
	}
	return res;
}


int main() {
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		if(arr[i] > i + 1) {
			arr[i] = -1;
		}else{
			arr[i] = i + 1 - arr[i];
		}
	}

	for(int i = 0;i < Q;++i) {
		int l,r;
		cin >> l >> r;
		r = N - r - 1;
		queries[r].push_back({l,i});
	}

	for(int i = 0;i < N;++i) {
		if(arr[i] != -1) {
			int l = 0;
			int r = i;
			int total = qry(i);
			while(l < r) {
				// cout << l << " " << r << endl;
				int m = (l + r + 1) >> 1;
				if(total - qry(m - 1) >= arr[i]) {
					l = m;
				}else{
					r = m - 1;
				}
			}
			// cout << i << " " << l << " " << (qry(i) - qry(l - 1)) << endl;
			if(qry(i) - qry(l - 1) >= arr[i]) upd(l,1);
		}
		for(pair<int,int> q : queries[i]) {
			ans[q.second] = qry(i) - qry(q.first - 1);
		}
	}
	for(int i = 0;i < Q;++i) {
		cout << ans[i] << endl;
	}
	return 0;
}