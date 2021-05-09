using namespace std;

#include <iostream>

int N;
int arr[100005];
bool asked[100005];

int ask(int a) {
	cout << "? " << a << endl;
	fflush(stdout);
	int res;
	cin >> res;
	return res;
}

void answer(int a) {
	cout << "! " << a << endl;
	fflush(stdout);
	return;
}

int askPair(int a) {
	return ask(a) - ask(a + N / 2);
}

int main() {
	cin >> N;
	if(N & 2) {
		answer(-1);
		return 0;
	}
	int l = 1;
	int r = 1 + N / 2;
	arr[l] = askPair(1);
	arr[r] = -arr[l];
	if(arr[l] == 0) {
		answer(l);
		return 0;
	}
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(asked[m]) {
			answer(-1);
			return 0;
		}
		asked[m] = true;
		arr[m] = askPair(m);
		if(arr[m] == 0) {
			answer(m);
			return 0;
		}
		if(abs(arr[m]) / arr[m] == abs(arr[l]) / arr[l]) {
			l = m;
		}else{
			r = m;
		}
	}
	answer(-1);
	return 0;
}