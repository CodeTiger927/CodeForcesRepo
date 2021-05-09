using namespace std;

#include <iostream>

int N,y[27] = {10010,11020,20011,21012,11011,21021,22022,12021,11011,12012,10120,11130,20121,21122,11121,21131,22132,12131,11121,12122,10221,11231,12113,20222,21223,11222};

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		int cur = 0;
		for(int j = 0;j < 5;++j) {
			int c;
			cin >> c;
			cur = (cur * 10) + c;
		}
		for(int j = 0;j < 26;++j) {
			if(cur == y[j]) {
				cout << (char)('a' + j);
				break;
			}
		}
	}
	cout << endl;
	return 0;
}