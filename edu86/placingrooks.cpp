using namespace std; 

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define MAXN 200005
#define MOD 998244353

long long factorial[MAXN], inverse[MAXN]; 

long long pow(long long a, long long b)  {
	long long res = 1; 
  	while(b > 0) {
		if (b % 2 == 1) { 
			res = (res * a) % MOD; 
		} 
		a = (a * a) % MOD; 
  		b >>= 1; 
	}
	return res; 
} 
  
long long nCk(int n,int k) { 
	if (k < 0 || k > n) { 
		return 0; 
	}
	long long ans = factorial[n]; 
	ans = (ans * inverse[n - k]) % MOD; 
	ans = (ans * inverse[k]) % MOD; 
	return ans; 
} 

void preCompute() { 
	long long fact = 1; 
  
	factorial[0] = 1; 
	inverse[0] = 1; 
  
	for(int i = 1;i < MAXN;++i) {
		fact = (fact * i) % MOD; 
		factorial[i] = fact; 
		inverse[i] = pow(factorial[i],MOD - 2);
	}
}

long long exp(long long a,long long b) {
	if(b == 0) return 1;
	if(b == 1) return a;
	long long res = exp(a,b >> 1);
	if(b & 1) {
		return a * (res * res % MOD) % MOD;
	}
	return res * res % MOD;
}

int N,K;

int main() {
	cin >> N >> K;
	preCompute();
	if(K > N - 1) {
		cout << 0 << endl;
		return 0;
	}
	long long ans = 0;
	int c = N - K;
	for(int i = c;i >= 0;--i) {
		if(i % 2 == c % 2) {
			ans += exp(i,N) * nCk(c,i) % MOD;
		}else{
			ans += MOD - exp(i,N) * nCk(c,i) % MOD;
		}
		if(ans >= MOD) ans -= MOD;
	}
	ans = ans * nCk(N,c) % MOD;
	if(K > 0) {
		ans <<= 1;
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return 0;

  
	return 0; 
} 