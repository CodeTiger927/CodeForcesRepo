using namespace std;

#include <iostream>
#include <vector>
#include <unordered_map>

#define MAXN 100005
#define MOD 1000000007

int N,arr[MAXN];
long long fact[MAXN],avg;
unordered_map<int,int> cnt;

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		cnt[arr[i]]++;
		avg += arr[i];
	}
	if(avg % N != 0) {
		cout << 0 << endl;
		return 0;
	}
	avg /= N;
	fact[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	vector<int> le,eq,gr;
	for(int i = 0;i < N;++i) {
		if(arr[i] < avg) {
			le.push_back(i);
		}else if(arr[i] == avg) {
			eq.push_back(i);
		}else{
			gr.push_back(i);
		}
	}
	if(le.size() == 0) {
		cout << 1 << endl;
		return 0;
	}
	if(le.size() == 1 || gr.size() == 1) {
		long long ans = fact[N];
		for(auto p : cnt) {
			ans = (ans * inv(fact[p.second])) % MOD;
		}
		cout << ans << endl;
		return 0;
	}
	long long ans = fact[N];
	ans = (ans * inv(fact[N - eq.size()])) % MOD;
	ans = (ans * fact[le.size()]) % MOD;
	ans = (ans * fact[gr.size()]) % MOD;
	for(auto p : cnt) {
		ans = (ans * inv(fact[p.second])) % MOD;
	}
	ans = (ans * 2) % MOD;
	cout << ans << endl;
	return 0;
}