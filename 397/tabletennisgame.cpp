using namespace std;

#include <iostream>

long long A,B,C;

int main() {
	cin >> A >> B >> C;
	if((B < A && C % A != 0) || (C < A && B % A != 0)) {
		cout << -1 << endl;
		return 0;
	}
	long long ans = (B / A) + (C / A);
	if(ans == 0) {
		cout << -1 << endl;
	}else{
		cout << ans << endl;
	}
	return 0;
}