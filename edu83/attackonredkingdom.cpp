using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 300005
#define MAXM 55

int N,A,B,C,per;
long long arr[MAXN],grun[MAXN][3];

long long get(long long x,int y) {
	if(x < MAXM) return grun[x][y];
	return grun[(x - MAXM) % per + MAXM][y];
}

int mex(const vector<long long>& v) {
	for(int i = 0;i < v.size();++i) {
		if(!count(v.begin(),v.end(),i)) return i;
	}
	return v.size();
}

void solve() {
	cin >> N >> A >> B >> C;
	for(int i = 0;i < N;++i) cin >> arr[i];
	for(int i = 1;;++i) {
		int a = max(i - A,0);
		int b = max(i - B,0);
		int c = max(i - C,0);
		grun[i][0] = mex({grun[a][0],grun[b][1],grun[c][2]});
		grun[i][1] = mex({grun[a][0],grun[c][2]});
		grun[i][2] = mex({grun[a][0],grun[b][1]});
		if(i > MAXM + 4) {
			bool f = true;
			for(int j = 0;j < 5;++j) {
				for(int k = 0;k < 3;++k) {
					f &= grun[j + MAXM][k] == grun[i - 4 + j][k];
				}
			}
			if(f) {
				per = i - 4 - MAXM;
				break;
			}
		}
	}
	long long sum = 0;
	for(int i = 0;i < N;++i) {
		sum ^= get(arr[i],0);
	}
	int ans = 0;
	for(int i = 0;i < N;++i) {
		int t = sum ^ get(arr[i],0);
		long long a = max(0ll,arr[i] - A);
		long long b = max(0ll,arr[i] - B);
		long long c = max(0ll,arr[i] - C);
		ans += (get(a,0) == t);
		ans += (get(b,1) == t);
		ans += (get(c,2) == t);
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}