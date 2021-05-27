using namespace std;

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <assert.h>

#define MAXN 200005

int BIT[MAXN];

void upd(int x,int v) {
	if(!~x) return;
	x++;
	while(x < MAXN) {
		BIT[x] += v;
		x += x & -x;
	}
	return;
}

int qry(int x) {
	int res = 0;
	x++;
	while(x) {
		res += BIT[x];
		x -= x & -x;
	}
	return res;
}

int N;
long long H,M,K,T,h[MAXN],m[MAXN];
vector<long long> v;
set<long long> s;

long long tot(long long a,long long b) {
	return a * M + b;
}

int find(long long x) {
	return lower_bound(v.begin(),v.end(),x) - v.begin();
}

void addRange(long long a,long long b) {
	if(find(b + 1) != v.size()) upd(find(b + 1),-1);
	upd(find(a),1);
	return;
}

void addRange(long long x) {
	if(x + K - 1 >= T) {
		addRange(x + 1,T);
		addRange(0,x + K - 1 - T);
	}else{
		addRange(x + 1,x + K - 1);
	}
	return;
}

bool contains(long long x,long long v) {
	return (x - K < v && v < x) || (x - K < v - T && v - T < x);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> H >> M >> K;
	T = M / 2;

	for(int i = 0;i < N;++i) {
		cin >> h[i] >> m[i];
		long long cur = m[i] % T;
		s.insert(cur);
		s.insert((cur + K) % T);
	}
	for(int x : s) v.push_back(x);
	for(int i = 0;i < N;++i) {
		addRange(m[i] % T);
	}
	
	int best = N + 1;
	int record = -1;
	for(int i = 0;i < v.size();++i) {
		int cur = qry(i);
		if(cur < best) {
			best = cur;
			record = v[i];
		}
	}
	cout << best << " " << record << endl;
	for(int i = 0;i < N;++i) {
		if(contains(record,m[i] % T)) {
			cout << (i + 1) << " ";
		}
	}
	cout << endl;
	return 0;
}