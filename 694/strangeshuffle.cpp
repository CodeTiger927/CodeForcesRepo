using namespace std;

#include <iostream>
#include <math.h>

long long ask(int x) {
	cout << "? " << x << endl;
	long long res;
	cin >> res;
	return res;
}

void answer(int x) {
	cout << "! " << x << endl;
	return; 
}

int N;
long long K;

int main() {
	cin >> N >> K;
	int s = sqrt(N);
	for(int i = 0;i < s;++i) {
		ask(1);
	}
	int cur = 0;
	for(int j = 1;j <= s;++j) {
		for(int i = j;i <= N;i += s) {
			if(ask(i) > K) {
				cur = i;
				break;
			}
		}
		if(cur) break;
	}
	for(int i = 18;i >= 0;--i) {
		int nxt = (cur - (1 << i)) % N;
		if(nxt <= 0) nxt += N;
		long long x = ask(nxt);
		if(x > K) cur = nxt;
	}
	cur--;
	if(cur <= 0) cur += N;
	answer(cur);
	return 0;
}