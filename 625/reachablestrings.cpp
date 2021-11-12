using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 200005
#define MOD 1000000007
#define MOD2 99824435

int N,Q;
long long a[MAXN][2],b[MAXN],p[MAXN];

long long get(int x,int l) {
	return (MOD + a[x + l - 1][x & 1] - p[b[x + l - 1] - b[x - 1]] * a[x - 1][x & 1] % MOD) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	p[0] = 1;
	cin >> N;
	for(int i = 1;i <= N;++i) {
		char c;
		cin >> c;
		b[i] = b[i - 1] + !(c & 1);
		p[i] = MOD2 * p[i - 1] % MOD;
		for(int j = 0;j < 2;++j) {
			if(c & 1) {
				a[i][j] = a[i - 1][j];
			}else{
				a[i][j] = (MOD2 * a[i - 1][j] + ((i & 1) ^ j) + c) % MOD;
			}
		}
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		int a,b,l;
		cin >> a >> b >> l;
		cout << (get(a,l) == get(b,l) ? "YES" : "NO") << endl;
	}
	
	return 0;
}