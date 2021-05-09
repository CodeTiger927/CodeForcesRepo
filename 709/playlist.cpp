using namespace std;

#include <iostream>
#include <queue>

#define MAXN 100005

int arr[MAXN],nxt[MAXN];
bool del[MAXN];

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

void solve() {
	int N;
	cin >> N;
	queue<pair<int,int>> q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		nxt[i] = (i + 1) % N;
		del[i] = false;
	}
	for(int i = 0;i < N;++i) {
		if(gcd(arr[i],arr[nxt[i]]) == 1) {
			q.push({i,nxt[i]});
		}
	}
	vector<int> ans;
	while(!q.empty()) {
		pair<int,int> cur = q.front();
		q.pop();
		int a = cur.first;
		int b = cur.second;
		if(del[a] || del[b]) continue;
		del[b] = true;
		ans.push_back(b + 1);
		nxt[a] = nxt[b];
		if(gcd(arr[a],arr[nxt[a]]) == 1) {
			q.push({a,nxt[a]});
		}
	}
	cout << ans.size() << " ";
	for(int i = 0;i < ans.size();++i) {
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