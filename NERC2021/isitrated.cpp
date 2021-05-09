using namespace std;

#include <iostream>
#include <cstring>
#include <chrono>
#include <random>
#include <time.h>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define MAXN 1005

int N,M,wa[MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		string str;
		cin >> str;
		long double vote0 = 0;
		long double sum = 0;
		for(int j = 0;j < N;++j) {
			long double cur = powl(0.75,wa[j]);
			vote0 += cur * (str[j] == '0');
			sum += cur;
		}
		cout << (uniform_real_distribution<long double>(0,1)(rng) < (vote0 / sum) ? 0 : 1) << endl;
		int ans,m;
		cin >> ans;
		for(int j = 0;j < N;++j) {
			wa[j] += (str[j] == '1') ^ ans;
			m = min(m,wa[j]);
		}
		for(int i = 0;i < N;++i) {
			wa[i] -= m;
		}
	}
	return 0;
}