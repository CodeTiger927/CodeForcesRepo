using namespace std;

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define MAXL 45

long long N,basis[MAXL];
vector<pair<pair<long long,long long>,int>> ans;
vector<long long> v;

long long sum(long long a,long long b) {
	if(a != 0 && b != 0) ans.push_back({{a,b},0});
	return a + b;
}

long long xxor(long long a,long long b) {
	ans.push_back({{a,b},1});
	return a ^ b;
}

bool check(long long x) {
	for(int i = MAXL - 1;i >= 0;--i) {
		if(x & (1ll << i)) {
			if(!basis[i]) return false;
			x ^= basis[i];
		}
	}
	return true;
}

void insert(long long x) {
	if(check(x)) return;
	for(int i = MAXL - 1;i >= 0;--i) {
		if(x & (1ll << i)) {
			if(basis[i]) {
				x = xxor(x,basis[i]);
			}else{
				basis[i] = x;
				v.push_back(x);
				return;
			}
		}
	}
	return;
}

int main() {
	cin >> N;
	xxor(N,N);
	insert(N);
	while(!check(1)) {
		long long a = v[uniform_int_distribution<int>(0,v.size() - 1)(rng)];
		long long b = v[uniform_int_distribution<int>(0,v.size() - 1)(rng)];
		if(a + b >= (1ll << MAXL) || check(a + b)) continue;
		long long s = sum(a,b);
		insert(s);
	}
	cout << ans.size() << endl;
	for(int i = 0;i < ans.size();++i) {
		if(ans[i].second) {
			cout << ans[i].first.first << " ^ " << ans[i].first.second << endl; 
		}else{
			cout << ans[i].first.first << " + " << ans[i].first.second << endl; 
		}
	}
	return 0;
}