using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 200005

int N,M,pre[MAXN],suf[MAXN];
string str,str2;

int main() {
	cin >> N >> M >> str >> str2;
	char cur = str2[0];
	int cnt = 0;
	for(int i = 0;i < N;++i) {
		if(str[i] == cur) {
			pre[++cnt] = i + 1;
			if(cnt == M + 1) break;
			cur = str2[cnt];
		}
	}
	cnt = M;
	cur = str2[M - 1];
	suf[M] = N + 1;
	for(int i = N - 1;i >= 0;--i) {
		if(str[i] == cur) {
			suf[--cnt] = i + 1;
			if(cnt == 0) break;
			cur = str2[cnt - 1];
		}
	}
	int ans = 0;
	for(int i = 1;i < M;++i) {
		// cout << suf[i] << " " << pre[i] << endl;
		ans = max(ans,suf[i] - pre[i]);
	}
	cout << ans << endl;
	return 0;
}