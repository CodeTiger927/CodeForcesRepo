using namespace std;

#include <iostream>
#include <random>
#include <chrono>

int main() {
	std::srand ( unsigned (std::chrono::system_clock::now().time_since_epoch().count() ) );
	int N = 10;
	cout << N << endl;
	for(int i = 0;i < N;++i) {
		cout << (rand() % 10) + 1 << " \n"[i == N - 1];
	}
	return 0;
}