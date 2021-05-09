using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAXN 100005


int N,M,X;
int arr[MAXN],height[MAXN],ans[MAXN];

void solve() {
	cin >> N >> M >> X;
	vector<pair<int,int>> v;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		v.push_back({-arr[i],i});
		height[i] = 0;
	}
	priority_queue<pair<int,int>> pq;
	for(int i = 0;i < M;++i) {
		pq.push({0,i});
	}
	sort(v.begin(),v.end());
	for(int i = 0;i < N;++i) {
		int curH = -v[i].first;
		int curI = v[i].second;

		auto cur = pq.top();
		pq.pop();
		int bH = -cur.first;
		int bI = cur.second;

		ans[curI] = bI + 1;
		height[bI] += curH;
		pq.push({-height[bI],bI});
	}
	int biggest = 0;
	int smallest = 1e9;
	for(int i = 0;i < M;++i) {
		biggest = max(biggest,height[i]);
		smallest =  min(smallest,height[i]);
	}
	if(biggest - smallest > X) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	for(int i = 0;i < N;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return;
}


int main() {
	int T;
	cin >> T;
	while(T--) solve();
}