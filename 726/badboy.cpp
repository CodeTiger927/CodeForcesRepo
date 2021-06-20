using namespace std;

#include <iostream>

long long getMin(long long a,long long b,long long c,long long d,long long e,long long f) {
	long long res = abs(a - c) + abs(b - d) + abs(c - e) + abs(d - f) + abs(e - a) + abs(f - b);
	swap(c,e);swap(d,f);
	return min(res,abs(a - c) + abs(b - d) + abs(c - e) + abs(d - f) + abs(e - a) + abs(f - b));
}

void solve() {
	long long N,M,x,y;
	cin >> N >> M >> x >> y;
	long long dx[9] = {1,x,N,1,x,N,1,x,N};
	long long dy[9] = {1,1,1,y,y,y,M,M,M};
	long long record = 0;
	pair<int,int> best = {-1,-1};
	for(int i = 0;i < 9;++i) {
		for(int j = 0;j < 9;++j) {
			long long cur = getMin(x,y,dx[i],dy[i],dx[j],dy[j]);
			if(cur >= record) {
				best = {i,j};
				record = cur;
			}
		}
	}
	int i = best.first;
	int j = best.second;
	cout << dx[i] << " " << dy[i] << " " << dx[j] << " " << dy[j] << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}