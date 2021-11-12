using namespace std;

#include <iostream>
#include <vector>
#include <map>

#define MOD 998244353

long long k,N,A,H,pw[33];

vector<int> eval(int n,int m) {
	if(n == 1) return {1};
	vector<int> res = eval(n / 2,m & ((1 << (n / 2 - 1)) - 1));
	vector<int> r = eval(n / 2,(m >> ((n / 2) - 1)) & ((1 << (n / 2 - 1)) - 1));
	for(int i : r) res.push_back(i);
	for(int i = 0;i < n;++i) {
		res[i] = res[i] * 2 - 1;
		if(res[i] == 1 && ((m >> (n - 2)) ^ (i < n / 2))) {
			res[i]++;
		}
	}
	return res;
}

long long get_hash(vector<int> v,int shift = 0) {
	long long res = 0;
	for(int i = 0;i < v.size();++i) {
		res += pw[v[i]] * (i + 1 + shift) % MOD;
		if(res >= MOD) res -= MOD;
	}
	return res;
}

int main() {
	cin >> k >> A >> H;
	N = 1 << k;
	pw[0] = 1;
	for(int i = 1;i <= (1 << k);++i) {
		pw[i] = pw[i - 1] * A % MOD;
	}
	if(k <= 4) {
		for(int i = 0;i < (1 << (N - 1));++i) {
			vector<int> v = eval(N,i);
			if(get_hash(v) == H) {
				for(int j = 0;j < v.size();++j) {
					cout << v[j] << " \n"[j == v.size() - 1];
				}
				return 0;
			}
		}
	}else{
		for(int j = 0;j < 2;++j) {
			map<int,int> m;
			for(int i = 0;i < (1 << ((N / 2) - 1));++i) {
				vector<int> v = eval(N / 2,i);
				for(int& c : v) {
					c = c * 2 - 1;
					if(c == 1 && j) c++;
				}
				m[get_hash(v)] = i;
			}
			for(int i = 0;i < (1 << ((N / 2) - 1));++i) {
				vector<int> v = eval(N / 2,i);
				for(int& c : v) {
					c = c * 2 - 1;
					if(c == 1 && !j) c++;
				}
				long long cur = get_hash(v,N / 2);
				if(m.count((H - cur + MOD) % MOD)) {
					vector<int> res = eval(N / 2,m[(H - cur + MOD) % MOD]);
					for(int& c : res) {
						c = c * 2 - 1;
						if(c == 1 && j) c++;
					}
					for(int c : v) res.push_back(c);
					for(int j = 0;j < res.size();++j) {
						cout << res[j] << " \n"[j == res.size() - 1];
					}
					return 0;
				}
			}
		}
	}
	cout << -1 << endl;
	return 0;
}