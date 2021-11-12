using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,arr[MAXN],pre[MAXN];
vector<int> ans;

bool check(int l,int r) {
	if(pre[r] ^ pre[l - 1]) return false;
	if((r - l) & 1) return false;
	if(l != r) return true;
	return arr[l] == 0;
}

void solve(int l,int r) {
	if(l == r) return;
	for(int i = l;i < r;i += 2) {
		ans.push_back(i);
	}
	for(int i = r - 4;i >= l;i -= 2) {
		ans.push_back(i);
	}
	return;
}

void solve() {
	ans.clear();
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		pre[i] = pre[i - 1] ^ arr[i];
	}
	if(pre[N]) {
		cout << "NO" << endl;
		return;
	}
	if(N & 1) {
		solve(1,N);
	}else if(~N & 1) {
		for(int i = 1;i < N;++i) {
			if(check(1,i) && check(i + 1,N)) {
				solve(1,i);
				solve(i + 1,N);
				break;
			}
		}
		if(ans.size() == 0) {
			cout << "NO" << endl;
			return;
		}
	}
	cout << "YES" << endl;
	cout << ans.size() << endl;
	for(int i = 0;i < ans.size();++i) {
		cout << ans[i] << " \n"[i == ans.size() - 1];
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}