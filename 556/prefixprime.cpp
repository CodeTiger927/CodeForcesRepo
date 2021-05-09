using namespace std;

#include <iostream>
#include <vector>
#include <cstring>

#define MAXN 400005

int N,cnt1,cnt2;

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		if(cur == 1) {
			cnt1++;
		}else{
			cnt2++;
		}
	}
	if(cnt1 == 0) {
		for(int i = 0;i < cnt2;++i) {
			cout << "2 ";
		}
		cout << endl;
		return 0;
	}else if(cnt2 == 0) {
		for(int i = 0;i < cnt1;++i) {
			cout << "1 ";
		}
		cout << endl;
		return 0;
	}
	cout << "2 1 ";
	for(int i = 0;i < cnt2 - 1;++i) {
		cout << "2 ";
	}
	for(int i = 0;i < cnt1 - 1;++i) {
		cout << "1 ";
	}
	cout << endl;
	return 0;
}