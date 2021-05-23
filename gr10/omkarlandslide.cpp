using namespace std;

#include <iostream>

int N;
long long sum;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		long long x;
		cin >> x;
		sum += x;
	}
	long long leftover = sum - 1ll * N * (N - 1) / 2;
	long long start = leftover / N;
	long long equal = leftover % N;
	for(int i = 0;i < equal;++i) {
		cout << start + i + 1 << " ";
	}
	for(int i = equal;i < N;++i) {
		cout << start + i << " ";
	}
	cout << endl;
	return 0;
}