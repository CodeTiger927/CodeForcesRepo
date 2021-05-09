// Basically APIO BOAT. Key idea: Sort by median

using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 100005

int N,M,K,pre[MAXN];
pair<int,int> segs[MAXN];

int main() {
	cin >> N >> M >> K;
	for(int i = 0;i < M;++i) {
		cin >> segs[i].first >> segs[i].second;
	}
	sort(segs,segs + M,[&](pair<int,int> a,pair<int,int> b) {return (a.first + a.second) < (b.first + b.second);});
	for(int i = 1;i <= N - K + 1;++i) {
		int cur = 0;
		for(int j = 0;j < M;++j) {
			cur += max(0,min(i + K - 1,segs[j].second) - max(i,segs[j].first) + 1);
			pre[j] = max(pre[j],cur);
		}
	}
	int ans = pre[M - 1];
	for(int i = 1;i <= N - K + 1;++i) {
		int cur = 0;
		for(int j = M - 1;j > 0;--j) {
			cur += max(0,min(i + K - 1,segs[j].second) - max(i,segs[j].first) + 1);
			ans = max(ans,pre[j - 1] + cur);
		}
	}
	cout << ans << endl;
	return 0;
}