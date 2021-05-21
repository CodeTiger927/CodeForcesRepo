using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 300005

int N,x[MAXN],y[MAXN],lx,rx,ly,ry,lz,rz,a,b,c,d,e,f;

void calc(int x) {
	a = lx + x;
	b = rx - x;
	c = ly + x;
	d = ry - x;
	e = lz + x;
	f = rz - x;
	return;
}

bool check() {
	return (b > a || d > c || f > e || b - c > e || a - d < f);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	rx = ry = rz = -1e6;
	lx = ly = lz = 1e6;
	for(int i = 0;i < N;++i) {
		string s;
		cin >> s;
		for(int j = 0;j < s.length();++j) {
			if(s[j] == 'N') {
				x[i]++;
			}else{
				y[i]++;
			}
		}
		lx = min(lx,x[i]);
		ly = min(ly,y[i]);
		lz = min(lz,x[i] - y[i]);
		rx = max(rx,x[i]);
		ry = max(ry,y[i]);
		rz = max(rz,x[i] - y[i]);

	}
	int l = 0;
	int r = 1e6;
	while(l < r){
		int m = (l + r) >> 1;
		calc(m);
		if(check()) {
			l = m + 1;
		}else{
			r = m;
		}
	}
	calc(l);
	int px = a - max(0,a - c - e);
	int py = c - max(0,f + c - a);

	cout << l << endl;
	for(int i = 0;i < px;++i) {
		cout << 'N';
	}
	for(int i = 0;i < py;++i) {
		cout << 'B';
	}
	cout << endl;
	return 0;
}