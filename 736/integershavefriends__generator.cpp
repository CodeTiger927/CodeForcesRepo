using namespace std;

#include <iostream>
#include <chrono>
#include <time.h>

void gen() {
	int N = 100;
	cout << N << endl;
	for(int i = 0;i < N;++i) {
		cout << (rand() % 10) << " \n"[i == N - 1];
	}
	return;
}

int main() {
	std::srand ( unsigned (std::chrono::system_clock::now().time_since_epoch().count() ) );
	int T = 10;
	cout << T << endl;
	while(T--) gen();
}