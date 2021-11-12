#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
 
using namespace std;
 
#include <iostream>
#include <vector>
#include <algorithm>
 
#define MAXN 3000005
#define MOD 1000000007
 
int N,Q;
long long fact[MAXN],invf[MAXN],tmp[MAXN],invn[MAXN];
 
long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}
 
long long nCr(long long a,long long b) {
	// cout << fact[a] << " " << invf[b] << " " << invf[a - b] << endl;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}
 
vector<long long> bin(int x) {
	vector<long long> res;
	res.reserve(x + 1);
	for(int i = 0;i <= x;++i) {
		res.push_back(nCr(x,i));
	}
	return res;
}
 
void sub(vector<long long>& a,vector<long long>& b) {
	for(int i = 0;i < b.size();++i) {
		a[i] -= b[i];
		if(a[i] < 0) a[i] += MOD;
	}
	return;
}
 
vector<long long> div(vector<long long>& a,vector<long long>& b) {
	vector<long long> res;
	res.reserve(a.size() - b.size());
	for(int i = a.size() - 1;i >= b.size() - 1;--i) {
		long long m = a[i] % MOD;
		res.push_back(m);
		for(int j = 0;j < b.size();++j) {
			a[i - j] = (MOD + a[i - j] - (m * b[b.size() - 1 - j] % MOD)) % MOD;
		}
	}
	reverse(res.begin(),res.end());
	return res;
}
 
int main() {
	fact[0] = invf[0] = 1;
	invn[1] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (i * fact[i - 1]) % MOD;
		if(i > 1) invn[i] = (MOD - (MOD/i) * invn[MOD%i] % MOD) % MOD;
		invf[i] = invf[i - 1] * invn[i] % MOD;
	}
	// S = ((1 + x)^(3N + 3) - (1 + x)^3) / (1 + 3x + 3x^2)
	scanf("%d %d",&N,&Q);
	vector<long long> a = bin(3 * N + 3);
	vector<long long> b = bin(3);
	sub(a,b);
	vector<long long> c = {3,3,1};
	vector<long long> ans = div(a,c);
 
	for(int i = 0;i < Q;++i) {
		int cur;
		scanf("%d",&cur);
		printf("%d\n",ans[cur + 1]);
	}
	return 0;
}