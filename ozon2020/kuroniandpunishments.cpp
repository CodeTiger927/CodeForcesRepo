using namespace std;

#include <iostream>
#include <set>
#include <time.h>
#include <random>
#include <math.h>
#include <chrono>

#define MAXN 200005

int N;
long long arr[MAXN];
set<long long> s;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
long long randval() {
    return uniform_int_distribution<int>(0, N - 1)(rng);
}

void factor(long long c) {
	if(c <= 1) return;
	for(long long i = 2;i <= sqrt(c);++i) {
		if(c % i == 0) {
			s.insert(i);
			while(c % i == 0) c /= i;
		}
	}
	if(c > 1) s.insert(c);
	return;
}

int main() {
	srand(time(NULL));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int it = 0;it < 30;++it) {
		int i = randval();
		long long c = arr[i];
		factor(c);
		factor(c - 1);
		factor(c + 1);
	}
	long long ans = N;
	for(long long i : s) {
		long long cur = 0;
		for(int j = 0;j < N;++j) {
			if(arr[j] < i) {
				cur += i - arr[j];
			}else{
				cur += min(arr[j] % i,i - (arr[j] % i));
			}
		}
		ans = min(ans,cur);
	}
	cout << ans << endl;
	return 0;
}