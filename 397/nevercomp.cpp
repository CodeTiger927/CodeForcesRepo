using namespace std;

#include <iostream>

int N;

int main() {
	cin >> N;
	if(N & 1) {
		cout << "contest" << endl;
	}else{
		cout << "home" << endl;
	}
	return 0;
}