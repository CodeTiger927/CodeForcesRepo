using namespace std;

#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#define MAXN 2050

int N,ans[MAXN],cnt,z[11][2];

int ask(int a,int b) {
	cout << "? " << a << " " << b << endl;
	int res;
	cin >> res;
	return res;
}

int magic(int a) {
	int res = (1 << 11) - 1;
	for(int i = 0;i < 11;++i) {
		if(a == z[i][0]) {
			res &= ask(a,z[i][1]);
		}else{
			res &= ask(a,z[i][0]);
		}
	}
	return res;
}

int main() {
	std::srand(unsigned (std::chrono::system_clock::now().time_since_epoch().count()));
	cin >> N;
	cnt = 11;
	while(cnt) {
		int a = rand() % N + 1;
		int b = rand() % N + 1;
		if(a == b) continue;
		int res = ask(a,b);
		for(int i = 0;i < 11;++i) {
			if(!(res & (1 << i)) && !z[i][0]) {
				z[i][0] = a;
				z[i][1] = b;
				cnt--;
			}
		}
	}
	int cur = 1;
	int curV = magic(cur);
	for(int i = 2;i <= N;++i) {
		if(ask(cur,i) == curV) {
			cur = i;
			curV = magic(cur);
		}
		if(curV == 0) break;
	}
	for(int i = 1;i <= N;++i) {
		if(i == cur) {
			ans[i] = 0;
		}else{
			ans[i] = ask(cur,i);
		}
	}
	cout << "!";
	for(int i = 1;i <= N;++i) cout << " " << ans[i];
	cout << endl;
	return 0;
}