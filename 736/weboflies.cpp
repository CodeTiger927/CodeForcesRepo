using namespace std;

#include <iostream>

#define MAXN 200005

int N,M,Q,ind[MAXN];

bool calc(int x) {
	return !ind[x];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		ind[min(a,b)]++;
	}
	int ans = 0;
	for(int i = 1;i <= N;++i) {
		ans += calc(i);
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		int t,u,v;
		cin >> t;
		if(t == 1) {
			cin >> u >> v;
			ans -= calc(min(u,v));
			ind[min(u,v)]++;
			ans += calc(min(u,v));
		}else if(t == 2) {
			cin >> u >> v;
			ans -= calc(min(u,v));
			ind[min(u,v)]--;
			ans += calc(min(u,v));
		}else{
			cout << ans << endl;
		}
	}
	return 0;
}