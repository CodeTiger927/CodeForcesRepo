using namespace std;

#include <iostream>
#include <cstring>

string str;
int nxt;

int main() {
	cin >> str;
	for(int i = 0;i < str.size();++i) {
		if(str[i] - 'a' > nxt) {
			cout << "NO" << endl;
			return 0;
		}
		if(str[i] - 'a' == nxt) nxt++;
	}
	cout << "YES" << endl;
	return 0;
}