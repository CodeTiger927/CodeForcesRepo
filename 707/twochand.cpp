using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 500005
 
long long Extended_Euclid(long long a,long long b,long long &x,long long &y) {
	long long d;
	if(b == 0) {
		x = 1;y = 0;
		return a;
	}
	d = Extended_Euclid(b,a%b,y,x);
	y -= a / b * x;
	return d;
}

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}
 
long long crt(long long a,long long b,long long c,long long d) {
	long long e,x,y,m,n,ret;
	ret = 0;
	n = a * c;
	m = c;
	e = Extended_Euclid(a,m,x,y);
	ret = (ret + y * m * b) % n;
	m = a;
	e = Extended_Euclid(c,m,x,y);
	ret = (ret + y * m * d) % n;
	return (n + ret % n) % n;
}

long long N,M,arr[2 * MAXN],arr2[MAXN],rep[MAXN];
long long K;

int main() {
	cin >> N >> M >> K;
	long long g = gcd(N,M);
	long long total = N * M / g;
	memset(arr,-1,sizeof(arr));
	memset(rep,-1,sizeof(rep));
	for(int i = 0;i < N;++i) {
		long long cur;
		cin >> cur;
		arr[cur] = i;
	}
	for(int i = 0;i < M;++i) {
		cin >> arr2[i];
		if(arr[arr2[i]] == -1) continue;
		if(i % g != arr[arr2[i]] % g) continue;
		long long nxt = crt(M / g,(i + 1) / g,N / g,(arr[arr2[i]] + 1) / g) * g + ((i + 1) % g);
		if(nxt == 0) nxt = total;
		rep[i] = nxt;
	}
	long long l = 0;
	long long r = 1e18;
	while(l < r) {
		long long m = (l + r) >> 1;
		long long tot = 0;
		for(int i = 0;i < M;++i) {
			if(rep[i] == -1) continue;
			tot += ((m - rep[i] + total) / total);
		}
		long long act = m - tot;
		if(act >= K) {
			r = m;
		}else{
			l = m + 1;
		}
	}
	cout << l << endl;
	return 0;
}