using namespace std;

#include <iostream>
#include <set>

int N,A,B;

void solve(int A,int B,set<int>& ans) {
	N = A + B;
	int a = (N + 1) / 2;
	int b = N / 2;
	if(A >= a) {
		int m = A - a;
		for(int i = 0;i <= min(A - m,B);++i) {
			// cout << i << endl;
			ans.insert(m + 2 * i);
		}
	}else{
		int m = B - b;
		for(int i = 0;i <= min(B - m,A);++i) {
			ans.insert(m + 2 * i);
		}
	}
	return;
}

void solve() {
	cin >> A >> B;
	set<int> ans;
	solve(A,B,ans);
	solve(B,A,ans);
	cout << ans.size() << endl;
	for(auto itr = ans.begin();itr != ans.end();++itr) {
		cout << *itr << " \n"[next(itr) == ans.end()];
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}