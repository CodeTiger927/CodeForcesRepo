using namespace std;

#include <iostream>
#include <random>
#include <chrono>

int main() {
	std::srand ( unsigned (std::chrono::system_clock::now().time_since_epoch().count() ) );
	int N = 8;
	int Q = 50;
	cout << N << " " << Q << endl;
	for(int i = 0;i < N;++i) {
		cout << (rand() % 10) + 1 << " \n"[i == N - 1];
	}
	for(int i = 0;i < N;++i) {
		cout << (rand() % 10) + 1 << " \n"[i == N - 1];
	}
	for(int i = 0;i < Q;++i) {
		int a = (rand() % N) + 1;
		int b = (rand() % N) + 1;
		if(a > b) swap(a,b);
		cout << a << " " << b << endl;
	}
	return 0;
}