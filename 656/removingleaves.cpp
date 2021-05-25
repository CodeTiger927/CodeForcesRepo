using namespace std;

#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define HOWSOGOOD ios_base::sync_with_stdio(0)
#define OTZ tie(0)
#define xd cout
#define omg cin
#define wtmoo endl
#define reee push_back
#define QAQ insert
#define TAT return
#define mithow "\n"

#define MAXN 200005

int N,K,cnt[MAXN],cnt2[MAXN];
bool vis[MAXN],vis2[MAXN];
vector<int> edges[MAXN];

void solve() {
	omg >> N >> K;
	for(int i = 0;i < N;++i) {
		vis[i] = vis2[i] = false;
		edges[i].clear();
		cnt[i] = cnt2[i] = 0;
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		omg >> a >> b;
		a--;b--;
		edges[a].reee(b);
		edges[b].reee(a);
		cnt2[a]++;
		cnt2[b]++;
	}
	queue<int> q;
	for(int i = 0;i < N;++i) {
		if(edges[i].size() <= 1) {
			vis[i] = true;
			q.push(i);
		}
	}
	int ans = 0;
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		vis2[v] = true;
		for(int u : edges[v]) {
			if(vis2[u]) continue;
			if(++cnt[u] == K) {
				ans++;
				cnt[u] = 0;
			}
			if(!vis[u] && --cnt2[u] <= 1 && !cnt[u]) {
				vis[u] = true;
				q.push(u);
			}
		}
	}
	xd << ans << mithow;
	TAT;
}

int main() {
	HOWSOGOOD;
	omg.OTZ;
	int T;
	omg >> T;
	while(T--) solve();
	TAT 0;
}