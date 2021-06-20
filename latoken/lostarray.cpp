using namespace std;

#include <iostream>
#include <cstring>
#include <queue>

#define MAXN 505

int N,K,par[MAXN];

int main() {
	cin >> N >> K;
	memset(par,-1,sizeof(par));
	queue<int> q;
	par[0] = 0;
	q.push(0);
	while(!q.empty()) {
		// number of selected
		int cur = q.front();
		q.pop();
		for(int i = 0;i <= K;++i) {
			if(cur >= (K - i) && (N - cur) >= i) {
				if(par[cur + i - (K - i)] != -1) continue;
				par[cur + i - (K - i)] = cur;
				q.push(cur + i - (K - i));
			}
		}
	}
	if(par[N] == -1) {
		cout << -1 << endl;
		return 0;
	}
	vector<int> v = {N};
	int cur = N;
	while(cur) {
		v.push_back(cur = par[cur]);
	}
	vector<int> nsel,sel;
	for(int i = 1;i <= N;++i) {
		nsel.push_back(i);
	}
	long long ans = 0;
	for(int i = v.size() - 1;i > 0;--i) {
		// x + (a - b) = y -> a - b = y - x
		// a + b = K
		// a = (y - x + K) / 2
		// b = (K + x - y) / 2
		int a = (v[i - 1] - v[i] + K) / 2;
		int b = (K + v[i] - v[i - 1]) / 2;
		cout << "?";
		vector<int> csel,cnsel;
		for(int i = 0;i < a;++i) {
			int cur = nsel.back();
			nsel.pop_back();
			csel.push_back(cur);
			cout << " " << cur;
		}
		for(int i = 0;i < b;++i) {
			int cur = sel.back();
			sel.pop_back();
			cnsel.push_back(cur);
			cout << " " << cur;
		}
		sel.insert(sel.end(),csel.begin(),csel.end());
		nsel.insert(nsel.end(),cnsel.begin(),cnsel.end());
		cout << endl;
		long long res;
		cin >> cur;
		ans ^= cur; 
	}
	cout << "! " << ans << endl;
	return 0;
}