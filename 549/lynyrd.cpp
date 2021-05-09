using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 200005

int st[524288];

void update(int x,int v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = min(st[p],v);
		return;
	}
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	st[p] = min(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,int v) {
	update(x,v,0,MAXN,0);
}

int getMin(int a,int b,int l,int r,int p) {
	if(l > b || r < a) return 9999999;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return min(getMin(a,b,l,m,2 * p + 1),getMin(a,b,m + 1,r,2 * p + 2));
}

int getMin(int a,int b) {
	return getMin(a,b,0,MAXN,0);
}

int N,M,Q;
int reverseMap[MAXN],arr[MAXN],tracker[MAXN],nxt[MAXN][20];

int main() {
	for(int i = 0;i < 524288;++i) {
		st[i] = 9999999;
	}
	cin >> N >> M >> Q;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		reverseMap[cur] = i;
	}
	for(int i = 0;i < M;++i) {
		int cur;
		cin >> cur;
		arr[i] = reverseMap[cur];
	}
	memset(tracker,-1,sizeof(tracker));
	for(int i = M - 1;i >= 0;--i) {
		nxt[i][0] = tracker[(arr[i] + 1) % N];
		if(nxt[i][0] == -1) nxt[i][0] = M;
		tracker[arr[i]] = i;
	}
	nxt[M][0] = M;
	for(int i = 1;i < 20;++i) {
		for(int j = 0;j <= M;++j) {
			nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
		}
	}
	for(int i = 0;i < M;++i) {
		int cur = i;
		for(int j = 19;j >= 0;--j) {
			if((N - 1) & (1 << j)) {
				cur = nxt[cur][j];
			}
		}
		update(i,cur);	
	}
	string ans = "";
	for(int i = 0;i < Q;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		if(getMin(a,b) <= b) {
			ans += '1';
		}else{
			ans += '0';
		}
	}
	cout << ans << endl;
	return 0;
}