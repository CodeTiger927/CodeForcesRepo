using namespace std;

#include <iostream>
#include <cmath>
#include <vector>
#include <array>

#define MAXN 1005

int N,M;

bool ask(bool t,int a,int b) {
	if(t) {
		cout << "? " << M << " " << a << " " << 1 << " " << 1 << " " << 1 << " " << (b + 1) << endl;
	}else{
		cout << "? " << a << " " << M << " " << 1 << " " << 1 << " " << (b + 1) << " " << 1 << endl;
	}
	bool res;
	cin >> res;
	return res;
}

long long solve(bool t = false) {
	if(t) swap(N,M);
	vector<int> v;
	int cur = N;
	for(int i = 2;i * i <= cur;++i) {
		if(cur % i == 0) {
			v.push_back(i);
			while(cur % i == 0) {
				cur /= i;
			}
		}
	}
	if(cur != 1) v.push_back(cur);
	cur = N;
	long long res = 1;
	for(int i : v) {
		int j;
		for(j = 1;cur % i == 0;cur /= i,++j) {
			int width = cur / i;
			int z = N / width;
			if(z > 2) {
				if(!ask(t,width * ((z - 1) / 2),width * ((z - 1) / 2))) break;
				if(!ask(t,width * ((z - 1) / 2),width * ((z + 1) / 2))) break;
			}else{
				if(z >= 2 && !ask(t,width * (z / 2),width * (z / 2))) break;
			}
		}
		res *= j;
	}
	return res;
}

int main() {
	cin >> N >> M;
	int ans = solve() * solve(true);
	cout << "! " << ans << endl;
	return 0;
}