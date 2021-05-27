using namespace std;

#include <iostream>
#include <algorithm>

pair<long long,int> A[3];

int main() {
	for(int i = 0;i < 3;++i) {
		cin >> A[i].first;
		A[i].second = i;
	}
	sort(A,A + 3);
	cout << "First" << endl;
	for(long long v = 2 * A[2].first - A[0].first - A[1].first;;) {
		int x;
		cout << v << endl;
		cin >> x;
		if(!(x--)) return 0;
		if(x == A[0].second) {
			A[0].first += v;
			v = A[2].first - A[1].first;
		}else if(x == A[1].second) {
			A[1].first += v;
			v = A[2].first - A[0].first;
		}else{
			A[2].first += v;
			v = 2 * A[2].first - A[0].first - A[1].first;
		}
	}
	return 0;
}