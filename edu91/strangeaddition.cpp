using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 500005
#define MOD 998244353

struct matrix {
	long long A[2][2];
	matrix() {A[0][0] = A[1][1] = 1;A[0][1] = A[1][0] = 0;}
	matrix operator*(const matrix& o) {
		matrix m;
		m.A[0][0] = m.A[1][1] = 0;
		for(int i = 0;i < 2;++i) {
			for(int k = 0;k < 2;++k) {
				for(int j = 0;j < 2;++j) {
					m.A[i][k] = (m.A[i][k] + A[i][j] * o.A[j][k]) % MOD;
				}
			}
		}
		return m;
	}
	void print() {
		cout << A[0][0] << " " << A[0][1] << endl;
		cout << A[1][0] << " " << A[1][1] << endl;
	}
};

int N,M,s[MAXN];
matrix st[1048576];
string str;

void upd(int x,pair<long long,long long> v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p].A[0][0] = v.first;
		st[p].A[0][1] = 1;
		st[p].A[1][0] = v.second;
		st[p].A[1][1] = 0;
		return;
	}
	int m = (l + r) >> 1;
	upd(x,v,l,m,2 * p + 1);
	upd(x,v,m + 1,r,2 * p + 2);
	st[p] = st[2 * p + 1] * st[2 * p + 2];
	return;
}

pair<long long,long long> find(int i) {
	if(s[i] != 1) return {s[i] + 1,0};
	return {s[i] + 1,19 - 10 * s[i] - s[i - 1]};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> str;
	for(int i = 0;i < N;++i) {
		s[i] = str[N - 1 - i] - '0';
	}
	for(int i = 1;i < N;++i) {
		upd(i,find(i),0,N - 1,0);
	}
	matrix init;
	init.A[1][0] = init.A[1][1] = 0;
	init.A[0][1] = 1;
	init.A[0][0] = s[0] + 1;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;
		if(a == (N - 1)) {
			init.A[0][0] = b + 1;
			s[0] = b;
			if(N > 1) upd(1,find(1),0,N - 1,0);
		}else{
			s[N - 1 - a] = b;
			upd(N - 1 - a,find(N - 1 - a),0,N - 1,0);
			if(a != 0) upd(N - a,find(N - a),0,N - 1,0);
		}
		matrix res = init * st[0];
		cout << res.A[0][0] << "\n";
	}
	return 0;
}