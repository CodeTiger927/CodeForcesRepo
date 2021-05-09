using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,f[MAXN],suf[MAXN];
bool smF[MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		int a,b;
		cin >> a >> b;
		if(a <= N && b <= N || a > N && b > N) {
			cout << -1 << endl;
			return 0;
		}
		if(a <= N) {
			f[a] = b;
			smF[a] = true;
		}else{
			f[b] = a;
		}
	}
	for(int i = N;i >= 1;--i) {
		suf[i] = max(suf[i + 1],f[i]);
	}
	int m = f[1];
	int last = 1;
	int ans = 0;
	for(int i = 1;i <= N;++i) {
		m = min(m,f[i]);
		if(m > suf[i + 1]) {
			int prev = 1e9;
			int prev2 = 1e9;
			int res = 0;
			for(int j = last;j <= i;++j) {
				if(f[j] < prev) {
					prev = f[j];
					res += !smF[j];
				}else if(f[j] < prev2) {
					prev2 = f[j];
					res += smF[j];
				}else{
					cout << -1 << endl;
					return 0;
				}
			}
			ans += min(res,i - last + 1 - res);
			last = i + 1;
		}
	}
	cout << ans << endl;
	return 0;
}