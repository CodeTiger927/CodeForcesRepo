using namespace std;

#include <iostream>
#include <chrono>
#include <random>
#include <set>

int N = 6;
int arr[500005];
set<int> ss;

int main() {
	std::srand ( unsigned (std::chrono::system_clock::now().time_since_epoch().count() ) );
	cout << N << endl;
	for(int i = 0;i < N;++i) {
		arr[i] = (rand() % N + 1);
		cout << arr[i] << " \n"[i == N - 1];
		ss.insert(arr[i]);
	}
	for(int i = 0;i < N;++i) {
		cout << (rand() % 21) - 10 << " \n"[i == N - 1];
	}
	int M = min(rand() % N + 1,(int)ss.size());
	set<int> s;
	while(s.size() < M) s.insert(arr[rand() % N]);
	cout << M << endl;
	for(auto itr = s.begin();itr != s.end();++itr) {
		cout << *itr << " \n"[next(itr) == s.end()];
	}
}