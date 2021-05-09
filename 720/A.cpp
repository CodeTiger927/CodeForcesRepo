using namespace std;

#include <iostream>

long long A,B;

void solve() {
	cin >> A >> B;
	if(B == 1) {
		cout << "NO" << endl;
		return;
	}
	if(B == 2) {
		cout << "YES" << endl;
		cout << A << " " << (3 * A) << " " << (2 * A * B) << endl;
		return;
	}
	cout << "YES" << endl;
	cout << A << " " << ((B - 1) * A) << " " << (A * B) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}