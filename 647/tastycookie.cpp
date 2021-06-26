using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 200000

int N;
long long M,K,a[MAXN],b[MAXN];
vector<bool> v;

void add(long long x,bool y) {
	M += x;
	K += 1ll * x * y;
	if(K <= MAXN) {
		for(int i = 0;i < x;++i) v.push_back(y);
	}
	return;
}

void rev() {
	add(1,0);
	reverse(a,a + N);
}

void rol() {
	add(1,1);
	for(int i = N - 1;i >= 1;--i) a[i] -= a[i - 1];
}

bool cmpf() {
	bool res = true;
	for(int i = 0;i < N;++i) res &= a[i] == b[i];
	return res;
}

bool cmpr() {
	bool res = true;
	for(int i = 0;i < N;++i) res &= a[i] == b[N - i - 1];
	return res;
}

bool inc() {
	bool res = true;
	for(int i = 0;i < N - 1;++i) res &= a[i] < a[i + 1];
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) cin >> b[i];
	for(int i = 0;i < N;++i) cin >> a[i];
	if(N == 1) {
		if(a[0] == b[0]) {
			cout << "SMALL" << endl << 0 << endl;
			return 0;
		}else{
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}else if(N == 2) {
		if(a[0] != b[0] || a[1] != b[1]) {
			if(a[0] > a[1]) rev();
			for(;a[0] > min(b[0],b[1]) && a[0] != a[1];rev()) {
				add((a[1] - 1) / a[0],1);
				a[1] %= a[0];
			}
			if(a[0] == min(b[0],b[1]) && a[1] >= max(b[0],b[1]) && !((a[1] - max(b[0],b[1])) % a[0])) {
				add((a[1] - max(b[0],b[1])) / a[0],1);
				a[1] = max(b[0],b[1]);
				if(a[0] != b[0]) rev();
			}else{
				cout << "IMPOSSIBLE" << endl;
				return 0;
			}
		}
	}else{
		while(!cmpf() && !cmpr()) {
			if(!inc()) rev();
			if(!inc()) break;
			rol();
		}
		if(cmpr()) rev();
		if(!cmpf()) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}
	reverse(v.begin(),v.end());
	if(K <= MAXN) {
		cout << "SMALL" << endl << M << endl;
		for(bool i : v) cout << (i ? 'P' : 'R');
		cout << endl;
	}else{
		cout << "BIG" << endl;
		cout << K << endl;
	}
	return 0;
}