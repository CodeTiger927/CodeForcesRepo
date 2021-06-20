using namespace std;

#include <iostream>

#define MAXN 100005

int N;
pair<bool,bool> c[MAXN];

bool chk(long long s,long long e) {
	if(e == s) return 0;
	if(e == s + 1) return 1;
	if(e & 1) {
		if(s & 1) return 0;
		return 1;
	}
	if(s <= e / 4) {
		return chk(s,e / 4);
	}
	if(s > (e / 4) * 2) return (e - s) & 1;
	return 1;
}

bool lck(long long s,long long e) {
	if(s * 2 > e) return 1;
	long long w = e / 2 + 3;
	while(w * 2 > e) w--;
	return chk(s,w);
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		long long a,b;
		cin >> a >> b;
		c[i] = {chk(a,b),lck(a,b)};
	}

	bool f = 1;
	bool s = 0;
	for(int i = 0;i < N;++i) {
		if(!(f ^ s)) break;
		if(s) {
			c[i].first ^= 1;
			c[i].second ^= 1;
		}
		f = c[i].second;
		s = c[i].first;
	}
	cout << s << " " << f << endl;
	return 0;
}