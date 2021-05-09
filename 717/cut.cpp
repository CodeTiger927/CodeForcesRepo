using namespace std;

#include <iostream>
#include <set>

#define MAXN 100005

int N,Q,arr[MAXN],st[MAXN][18],st2[MAXN][18],log[MAXN];

int spf[MAXN];

void sieve() {
	for(int i = 1;i < MAXN;i++) {
		spf[i] = i;
	}
	for(int i = 4;i < MAXN;i += 2) {
		spf[i] = 2;
	}
	for(int i = 3;i * i < MAXN;i++) {
		if(spf[i] == i) {
			for(int j = i * i;j < MAXN;j += i) {
				if(spf[j] == j) spf[j] = i;
			}
		}
	}
	return;
}

void build() {
	register int i;
	register int j;
	log[1] = 0;
	for(i = 2;i < MAXN;++i) {
		log[i] = log[i / 2] + 1;
	}
	for(j = 1;j < 18;++j) {
		for(i = 0;i + (1 << j) <= N;++i) {
			st[i][j] = min(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
		}
	}
}

inline int getMin(int l,int r) {
	int j = log[r - l + 1];
	return min(st[l][j],st[r - (1 << j) + 1][j]);
}

set<int> s[MAXN];

int main() {
	sieve();
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		long long cur = arr[i];
		while(cur != 1) {
			long long curP = spf[cur];
			s[curP].insert(i);
			while(spf[cur] == curP) cur /= curP;
		}
	}
	for(int i = 0;i < N;++i) {
		int curM = N;
		long long cur = arr[i];
		while(cur != 1) {
			long curP = spf[cur];
			auto itr = s[curP].upper_bound(i);
			if(itr != s[curP].end()) curM = min(curM,*itr - 1);
			while(spf[cur] == curP) cur /= curP;
		}
		st[i][0] = curM;
	}
	build();
	for(int i = 0;i < N;++i) {
		int l = i;
		int r = N - 1;
		while(l < r) {
			int m = (l + r + 1) >> 1;
			if(getMin(i,m) < m) {
				r = m - 1;
			}else{
				l = m;
			}
		}
		st2[i][0] = l;
		if(getMin(i,N - 1) >= N - 1) st2[i][0] = N;
	}
	st2[N][0] = N;
	for(int i = 1;i < 18;++i) {
		st2[N][i] = N;
		for(int j = 0;j < N;++j) {
			st2[j][i] = st2[min(N,st2[j][i - 1] + 1)][i - 1];
		}
	}
	for(int i = 0;i < Q;++i) {
		int l,r;
		cin >> l >> r;
		l--;r--;
		int ans = 0;
		for(int j = 17;j >= 0;--j) {
			if(l > r) break;
			// cout << l << " " << r << " " << j << endl;
			if(st2[l][j] < r) {
				ans += (1 << j);
				l = st2[l][j] + 1;
			}
		}
		cout << ans + 1 << endl;
	}
	return 0;
}