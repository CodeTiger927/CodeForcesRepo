using namespace std;

#include <iostream>
#include <vector>
#include <cstring>

#define MAXN 500005

int N,pref[MAXN],sizes[MAXN];
long long dp[MAXN];
vector<int> v;
string str;

int st[1048576];

void update(int x,int v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = v;
		return;
	}
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	st[p] = max(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,int v) {
	update(x,v,0,MAXN,0);
}

int getMax(int a,int b,int l,int r,int p) {
	if(l > b || r < a) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return max(getMax(a,b,l,m,2 * p + 1),getMax(a,b,m + 1,r,2 * p + 2));
}

int getMax(int a,int b) {
	return getMax(a,b,0,MAXN,0);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	long long ans = 0;
	cin >> N >> str;
	

	str += '0';
	dp[0] = 0;
	if(str[0] == '1') pref[0] = 1;
	if(str.size() > 1 && str[0] == '1' && str[1] == '0') v.push_back(1);
	int last = (str[0] == '0');
	for(int i = 1;i < N;++i) {
		pref[i] = pref[i - 1];
		if(str[i] == '0') {
			dp[i] = dp[i - 1];
			if(str[i - 1] == '1') {
				if(!v.empty()) {
					dp[i] += (1ll * v.back() * (v.back() + 1)) / 2;
				}
			}
			last = i + 1;
		}else{
			int sz = i - last + 1;
			int f = getMax(sz + 1,N);
			update(sz,i);

			if(str[i + 1] == '0') {
				sizes[i] = sz;
				v.push_back(i - last + 1);
			}
			
			if(sizes[f] <= sz) {
				dp[i] += 1ll * sz * last;
				continue;
			}
			dp[i] = dp[f];
			dp[i] += 1ll * (last - f + sz - 1) * sz;
			dp[i] += 1ll * (sizes[f] + sz + 1) * (sizes[f] - sz) / 2;
		}
	}
	for(int i = 0;i < N;++i) {
		ans += dp[i];
	}
	for(int i = 0;i < v.size();++i) {
		long long n = v[i];
		ans += (1ll * n * (n + 1) * (n + 1) / 2) - (1ll * n * (n + 1) * (2 * n + 1) / 6);
	}
	cout << ans << endl;
	return 0;

}