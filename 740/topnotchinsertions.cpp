using namespace std; 

#include <iostream> 
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define MAXN 400005
#define MOD 998244353

ordered_set os;


int N,M,a[MAXN],b[MAXN];
long long fact[MAXN],invf[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long nCr(long long a,long long b) {
	// cout << fact[a] << " " << invf[b] << " " << invf[a - b] << endl;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

void solve() {
	cin >> N >> M;
	vector<int> rollback;
	vector<pair<int,int>> arr;
	for(int i = 0;i < M;++i) {
		cin >> a[i] >> b[i];
		a[i]--;b[i]--;
	}
	set<int> s;
	for(int i = M - 1;i >= 0;--i) {
		auto it = os.find_by_order(b[i]);
		s.insert(*next(it));
		rollback.push_back(*it);
		os.erase(it);
	}
	while(rollback.size()) {
		os.insert(rollback.back());
		rollback.pop_back();
	}
	cout << nCr(2 * N - s.size() - 1,N) << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for(int i = 1;i < MAXN / 2;++i) {
		os.insert(i);
	}
	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (i * fact[i - 1]) % MOD;
		invf[i] = (inv(i) * invf[i - 1]) % MOD;
	}
	int T;
	cin >> T;
	while(T--) solve();
}