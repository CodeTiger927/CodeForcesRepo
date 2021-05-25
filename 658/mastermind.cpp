using namespace std;

#include <iostream>
#include <set>
#include <queue>
#include <vector>

#define MAXN 100005

int N,x,y,arr[MAXN],ans[MAXN];
vector<int> ind[MAXN];
bool mis[MAXN];

void solve() {
	cin >> N >> x >> y;
	set<int> s;
	for(int i = 1;i <= N + 1;++i) {
		ind[i].clear();
		s.insert(i);
	}
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		ans[i] = 0;
		mis[i] = false;
		ind[arr[i]].push_back(i);
		s.erase(arr[i]);
	}
	priority_queue<pair<int,int>> pq;
	for(int i = 1;i <= N + 1;++i) {
		if(ind[i].size()) pq.push({ind[i].size(),i});
	}
	for(int i = 0;i < x;++i) {
		pair<int,int> cur = pq.top();
		pq.pop();
		ans[ind[cur.second].back()] = cur.second;
		ind[cur.second].pop_back();
		pq.push({ind[cur.second].size(),cur.second});
	}
	int mf = pq.top().first;

	if(mf * 2 > 2 * N - x - y) {
		cout << "NO" << endl;
		return;
	}
	vector<int> all;
	for(int i = 1;i <= N + 1;++i) {
		for(int x : ind[i]) all.push_back(x);
	}
	int cnt = N - y;
	for(int i = 0;i < all.size();++i) {
		ans[all[i]] = arr[all[(i + (N - x) / 2) % (N - x)]];
		if(ans[all[i]] == arr[all[i]]) {
			ans[all[i]] = *s.begin();
			mis[all[i]] = true;
			cnt--;
		}
	}
	int i = 0;
	while(cnt) {
		if(!mis[all[i]]) {
			cnt--;
			ans[all[i]] = *s.begin();
		}
		i++;
	}
	cout << "YES" << endl;
	for(int i = 0;i < N;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}