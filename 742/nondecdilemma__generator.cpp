using namespace std;

#include <iostream>
#include <chrono>
#include <time.h>

void gen() {
	int N = 10;
	int M = 10;
	cout << N << " " << M << endl;
	for(int i = 0;i < N;++i) {
		cout << (rand() % 10 + 1) << " \n"[i == N - 1];
	}
	for(int i = 0;i < M;++i) {
		if(rand() & 1) {
			cout << 1 << " " << (rand() % N + 1) << " " << (rand() % 5 + 1) << endl;
		}else{
			int a = (rand() % N + 1);
			int b = (rand() % N + 1);
			if(a > b) swap(a,b);
			cout << 2 << " " << a << " " << b << endl;
		}
	}
	return;
}

int main() {
	std::srand ( unsigned (std::chrono::system_clock::now().time_since_epoch().count() ) );
	int T = 1;
	// cout << T << endl;
	while(T--) gen();
}