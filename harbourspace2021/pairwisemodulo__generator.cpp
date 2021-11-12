using namespace std;

#include <iostream>
#include <random>
#include <chrono>

using namespace chrono;

int main() {
	mt19937 rng(high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<long long unsigned> distribution(0,3e5);
	int N = 10;
	cout << N << endl;
	for(int i = 0;i < N;++i) {
		cout << distribution(rng) + 1 << " ";
	}
	cout << endl;
}